# Keymap graphic

This directory contains the reproducible sources for the keymap SVGs:

- `keymap.yaml` is the parsed 36-key keymap-drawer model.
- `mouse-layer.yaml` is the focused Mouse Left/Mouse Right model, including
  Pointer and Scroll modes and the active-hand-only combos.
- `mouse-layout.json` defines the two 3x5 grids and mirrored three-key thumb
  fans.
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

Generate the focused bilateral 3x5+3 Mouse layer diagrams with:

```sh
uvx --from keymap-drawer==0.23.0 keymap \
  draw draw/mouse-layer.yaml -s "Left Pointer" "Right Pointer" -o mouse-pointer.svg

uvx --from keymap-drawer==0.23.0 keymap \
  draw draw/mouse-layer.yaml -s "Left Scroll" "Right Scroll" -o mouse-scroll.svg
```

`1×/H/2×` means tap for one-shot, hold for momentary, and double-tap for a
persistent modifier lock. `NWin / Alt 2s` is the timed Alt+Tab switcher. `P/S`
switches the active hand's directional keys between Pointer and Scroll; `4×`
and `¼×` are held speed modifiers in either mode. Transparent keys show the
inactive hand, which remains on Base.

`L Lock` on `X` or `.` holds left click without a timeout until the active LMB
thumb or Mouse exit releases it. Exiting Mouse also releases every mouse button
plus Ctrl, Shift, and Alt, clears the selected hand's sublayers, and returns its
next entry to Pointer mode.

Mouse diagram legend: `PgUp`/`PgDn` are page movement; `PTab` is previous tab;
`NWin` is next window; `Clip` is clipboard history; `Snip` is screen snip; and
`L●`/`M●`/`R●` mirror the three direct mouse-button thumbs between hands.

The focused diagrams intentionally use keymap-drawer's default visual style;
`config.yaml` remains specific to the full `keymap.svg` diagram.

Reparsing `config/corne.keymap` requires an initialized ZMK west workspace so
the `zmk-helpers` includes referenced by `config.yaml` are available. The
checked-in `keymap.yaml` lets the graphic be redrawn without that workspace.
