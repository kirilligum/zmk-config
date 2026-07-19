/*
 * Copyright (c) 2026 Kirill Igum
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT kirill_behavior_cancelable_text

#include <stddef.h>
#include <stdint.h>

#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include <drivers/behavior.h>
#include <dt-bindings/zmk/keys.h>
#include <zmk/behavior.h>
#include <zmk/events/keycode_state_changed.h>

LOG_MODULE_REGISTER(zmk_cancelable_text, CONFIG_ZMK_LOG_LEVEL);

struct cancelable_text_config {
    const char *text;
    uint32_t wait_ms;
    uint32_t tap_ms;
};

struct cancelable_text_runner {
    struct k_work_delayable work;
    const struct device *device;
    size_t index;
    uint32_t keycode;
    bool active;
    bool key_pressed;
};

static struct cancelable_text_runner runner;
K_MUTEX_DEFINE(runner_mutex);

static uint32_t ascii_to_keycode(char character) {
    if (character >= 'a' && character <= 'z') {
        return A + (character - 'a');
    }

    if (character >= 'A' && character <= 'Z') {
        return LS((A + (character - 'A')));
    }

    if (character >= '1' && character <= '9') {
        return N1 + (character - '1');
    }

    switch (character) {
    case '0':
        return N0;
    case ' ':
        return SPACE;
    case '\n':
        return RET;
    case '!':
        return LS(N1);
    case '"':
        return LS(SQT);
    case '#':
        return LS(N3);
    case '$':
        return LS(N4);
    case '%':
        return LS(N5);
    case '&':
        return LS(N7);
    case '\'':
        return SQT;
    case '(':
        return LS(N9);
    case ')':
        return LS(N0);
    case '*':
        return LS(N8);
    case '+':
        return LS(EQUAL);
    case ',':
        return COMMA;
    case '-':
        return MINUS;
    case '.':
        return DOT;
    case '/':
        return FSLH;
    case ':':
        return LS(SEMICOLON);
    case ';':
        return SEMICOLON;
    case '<':
        return LS(COMMA);
    case '=':
        return EQUAL;
    case '>':
        return LS(DOT);
    case '?':
        return LS(FSLH);
    case '@':
        return LS(N2);
    case '[':
        return LBKT;
    case '\\':
        return BSLH;
    case ']':
        return RBKT;
    case '^':
        return LS(N6);
    case '_':
        return LS(MINUS);
    case '`':
        return GRAVE;
    case '{':
        return LS(LBKT);
    case '|':
        return LS(BSLH);
    case '}':
        return LS(RBKT);
    case '~':
        return LS(GRAVE);
    default:
        return 0;
    }
}

static void release_current_key(void) {
    if (!runner.key_pressed) {
        return;
    }

    raise_zmk_keycode_state_changed_from_encoded(runner.keycode, false, k_uptime_get());
    runner.key_pressed = false;
}

static void stop_runner(void) {
    runner.active = false;
    k_work_cancel_delayable(&runner.work);
    release_current_key();
    runner.device = NULL;
    runner.index = 0;
}

static void cancelable_text_work_handler(struct k_work *work) {
    ARG_UNUSED(work);

    k_mutex_lock(&runner_mutex, K_FOREVER);

    if (!runner.active || runner.device == NULL) {
        k_mutex_unlock(&runner_mutex);
        return;
    }

    const struct cancelable_text_config *config = runner.device->config;

    if (runner.key_pressed) {
        release_current_key();
        runner.index++;

        if (config->text[runner.index] == '\0') {
            runner.active = false;
            runner.device = NULL;
            runner.index = 0;
        } else {
            k_work_schedule(&runner.work, K_MSEC(config->wait_ms));
        }

        k_mutex_unlock(&runner_mutex);
        return;
    }

    while (config->text[runner.index] != '\0') {
        runner.keycode = ascii_to_keycode(config->text[runner.index]);

        if (runner.keycode != 0) {
            break;
        }

        LOG_WRN("Skipping unsupported character 0x%02x", config->text[runner.index]);
        runner.index++;
    }

    if (config->text[runner.index] == '\0') {
        runner.active = false;
        runner.device = NULL;
        runner.index = 0;
        k_mutex_unlock(&runner_mutex);
        return;
    }

    raise_zmk_keycode_state_changed_from_encoded(runner.keycode, true, k_uptime_get());
    runner.key_pressed = true;
    k_work_schedule(&runner.work, K_MSEC(config->tap_ms));

    k_mutex_unlock(&runner_mutex);
}

static int on_cancelable_text_pressed(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
    ARG_UNUSED(event);

    const struct device *device = zmk_behavior_get_binding(binding->behavior_dev);

    k_mutex_lock(&runner_mutex, K_FOREVER);

    if (runner.active) {
        stop_runner();
        k_mutex_unlock(&runner_mutex);
        return ZMK_BEHAVIOR_OPAQUE;
    }

    runner.device = device;
    runner.index = 0;
    runner.keycode = 0;
    runner.key_pressed = false;
    runner.active = true;
    k_work_schedule(&runner.work, K_NO_WAIT);

    k_mutex_unlock(&runner_mutex);
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_cancelable_text_released(struct zmk_behavior_binding *binding,
                                       struct zmk_behavior_binding_event event) {
    ARG_UNUSED(binding);
    ARG_UNUSED(event);
    return ZMK_BEHAVIOR_OPAQUE;
}

static int cancelable_text_init(const struct device *device) {
    ARG_UNUSED(device);
    static bool initialized;

    if (!initialized) {
        k_work_init_delayable(&runner.work, cancelable_text_work_handler);
        initialized = true;
    }

    return 0;
}

static const struct behavior_driver_api cancelable_text_driver_api = {
    .binding_pressed = on_cancelable_text_pressed,
    .binding_released = on_cancelable_text_released,
};

#define CANCELABLE_TEXT_INST(n)                                                                    \
    static const struct cancelable_text_config cancelable_text_config_##n = {                      \
        .text = DT_INST_PROP(n, text),                                                             \
        .wait_ms = DT_INST_PROP(n, wait_ms),                                                       \
        .tap_ms = DT_INST_PROP(n, tap_ms),                                                         \
    };                                                                                             \
    BEHAVIOR_DT_INST_DEFINE(n, cancelable_text_init, NULL, NULL, &cancelable_text_config_##n,      \
                            POST_KERNEL, CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,                      \
                            &cancelable_text_driver_api);

DT_INST_FOREACH_STATUS_OKAY(CANCELABLE_TEXT_INST)
