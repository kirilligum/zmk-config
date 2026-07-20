# Keymap graphic

This directory contains the reproducible sources for the keymap SVGs:

- `keymap.yaml` is the parsed 36-key keymap-drawer model.
- `mouse-layer.yaml` is the focused right-hand Mouse layer model, including
  Pointer and Scroll modes and their layer-specific combos.
- `mouse-layout.json` defines its 3x5 grid and three-key right-hand thumb fan.
- `config.yaml` contains the ZMK parser mappings and light-only SVG theme.

## Prompt keys

Hold the Enter thumb to activate the Fn layer, then press:

- `B` for Abstract
- `G` for Reason
- `V` for Plan

The prompts type without sending Enter. While a prompt is typing, press any
prompt key again to stop it immediately. The outer left and right thumb keys
are Backspace and Right Arrow, respectively.

Other Fn-layer shortcuts include:

- `'` for screen brightness up
- `O` for screen brightness down
- `?` for the external-display switcher (`GUI+P`, or `Win+P` on Windows)

Regenerate the SVG with the pinned keymap-drawer version:

```sh
uvx --from keymap-drawer==0.23.0 keymap \
  -c draw/config.yaml draw draw/keymap.yaml -o keymap.svg
```

Generate the focused 3x5+3 Mouse layer diagrams with:

```sh
uvx --from keymap-drawer==0.23.0 keymap \
  draw draw/mouse-layer.yaml -s Pointer -o mouse-pointer.svg

uvx --from keymap-drawer==0.23.0 keymap \
  draw draw/mouse-layer.yaml -s Scroll -o mouse-scroll.svg
```

`LOCK` means the key or mouse button remains held until its toggle is pressed
again. Selecting another mouse-button lock transfers the hold; exiting Mouse
releases it. `P/S` switches the directional keys between Pointer and Scroll
mode; `4x` and `1/4x` are held speed modifiers in either mode.

The focused diagrams intentionally use keymap-drawer's default visual style;
`config.yaml` remains specific to the full `keymap.svg` diagram.

Reparsing `config/corne.keymap` requires an initialized ZMK west workspace so
the `zmk-helpers` includes referenced by `config.yaml` are available. The
checked-in `keymap.yaml` lets the graphic be redrawn without that workspace.
