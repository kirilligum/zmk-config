# Keymap graphic

This directory contains the reproducible source for [`../keymap.svg`](../keymap.svg):

- `keymap.yaml` is the parsed 36-key keymap-drawer model.
- `config.yaml` contains the ZMK parser mappings and light-only SVG theme.

## Prompt keys

Hold the Enter thumb to activate the Fn layer, then press:

- `B` for Abstract
- `G` for Reason
- `V` for Plan

The prompts type without sending Enter. While a prompt is typing, press any
prompt key again to stop it immediately. The outer left and right thumb keys
are Backspace and Tab, respectively.

Other Fn-layer shortcuts include:

- `'` for screen brightness up
- `O` for screen brightness down
- `?` for the external-display switcher (`GUI+P`, or `Win+P` on Windows)

Regenerate the SVG with the pinned keymap-drawer version:

```sh
uvx --from keymap-drawer==0.23.0 keymap \
  -c draw/config.yaml draw draw/keymap.yaml -o keymap.svg
```

Reparsing `config/corne.keymap` requires an initialized ZMK west workspace so
the `zmk-helpers` includes referenced by `config.yaml` are available. The
checked-in `keymap.yaml` lets the graphic be redrawn without that workspace.
