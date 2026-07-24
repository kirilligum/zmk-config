# Keymap graphic

This directory contains the reproducible sources for the keymap SVGs:

- `keymap.yaml` is the parsed 36-key keymap-drawer model.
- `generate.sh` produces the compact overview, full layer breakdown, and both
  focused Mouse diagrams from the checked-in models.
- `mouse-layer.yaml` is the focused Mouse Left/Mouse Right model, including
  Pointer and Scroll modes and the active-hand-only combos.
- `mouse-layout.json` defines the two 3x5 grids and mirrored three-key thumb
  fans.
- `config.yaml` contains the ZMK parser mappings and light-only SVG theme.

## Prompt keys

Hold the Enter thumb to activate the Fn layer, then press these positions:

- Gallium `V` / QWERTY `T` for Abstract
- `G` in either base for Reason
- Gallium `Z` / QWERTY `B` for Plan

The prompts type without sending Enter. While a prompt is typing, press any
prompt key again to stop it immediately. The outer left and right thumb keys
are Backspace and Right Arrow, respectively.

Other Fn-layer shortcuts include:

- `,` for screen brightness up
- `I` for screen brightness down
- `?` for the external-display switcher (`GUI+P`, or `Win+P` on Windows)
- `K` / `F` to pin an application / window across desktops
- `'` for the desktop manager

Regenerate every checked-in SVG from the repository root:

```sh
./draw/generate.sh
```

The script pins keymap-drawer 0.23.0 and constructs `overview.svg` by placing
the default Gallium Base in the center of each key, Fn at top-left, Nav at
top-right, Num at bottom-left, and Sys at bottom-right. Transparent, held, and
repeated Base bindings are omitted from the corners. Combos are drawn as a
separate keyboard below the compact overview, while Mouse Left and Mouse Right
remain in the focused diagrams. `keymap.svg` retains the complete
layer-by-layer breakdown, including QWERTY.

The compact overview abbreviates screen brightness as `Bri↑` / `Bri↓` so the
Fn legends fit in the key corners.

`1×/H/2×` means tap for one-shot, hold for momentary, and double-tap for a
persistent modifier lock. `NWin / Alt 2s` is the timed Alt+Tab switcher. `P/S`
switches the active hand's directional keys between Pointer and Scroll; `4×`
and `¼×` are held speed modifiers in either mode. Transparent keys show the
inactive hand, which remains on the selected Gallium or QWERTY base.

`L Lock` on `Q` or `.` holds left click without a timeout until the active LMB
thumb or Mouse exit releases it. Exiting Mouse also releases every mouse button
plus Ctrl, Shift, and Alt, clears the selected hand's sublayers, returns its
next entry to Pointer mode, and preserves the selected alpha base.

Mouse diagram legend: `PgUp`/`PgDn` are page movement; `Esc` is Escape;
`NWin` is next window; `Clip` is clipboard history; `Snip` is screen snip; and
`L●`/`M●`/`R●` mirror the three direct mouse-button thumbs between hands.
The small corner legends are the Gallium Colstag Base keys. Mouse entry/exit is
the same physical chord in either base: Gallium `B+C` / QWERTY `Q+R` on the
left, or Gallium `Y+,` / QWERTY `U+P` on the right. Pointer/Scroll mode is
`N+X` or `I+?` by the Gallium legends.

The focused diagrams intentionally use keymap-drawer's default visual style;
`config.yaml` remains specific to `overview.svg` and the full `keymap.svg`
diagram.

Reparsing `config/corne.keymap` requires an initialized ZMK west workspace so
the `zmk-helpers` includes referenced by `config.yaml` are available. The
checked-in `keymap.yaml` lets the graphic be redrawn without that workspace.
