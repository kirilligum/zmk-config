# Corne ZMK config

Personal 36-key Corne firmware for `nice_nano@2.0.0`, with separate builds for
the left and right halves. The configuration pins ZMK and its modules in
[`config/west.yml`](config/west.yml); GitHub Actions builds the targets declared
in [`build.yaml`](build.yaml).

## Keymap

![Full Corne keymap](keymap.svg)

The outer thumbs are Backspace on the left and Right Arrow on the right. Hold
Space for Nav, Enter for Fn, and Smart for Num. Fn and Num together activate
Sys.

## Mouse layer

Press `Y+'` together from Base, Nav, or Num to enter Mouse. Press the same combo
to exit. Mouse is a right-hand 3x5+3 layout with Pointer and Scroll modes.

![Mouse Pointer mode](mouse-pointer.svg)

The same keys in [Scroll mode](mouse-scroll.svg) scroll instead of moving the
pointer.

### Keys

| Key | SVG | Action |
| --- | --- | --- |
| `J` / `M` | `⇞` / `⇟` | Page up / page down |
| `L` / `Y` | `PTab` / `NTab` | Previous tab / next tab |
| `U` `N` `E` `I` | `↑` `←` `↓` `→` | Move or scroll up / left / down / right |
| `O` / `?` | `🐇` / `🐢` | Hold for 4x / 1/4x movement or scroll speed |
| `'` / `K` | `⌃🔒` / `⇧🔒` | Toggle-held Ctrl / Shift |
| `H` / `,` / `.` | `⧉` / `✂` / `📋` | Copy / cut / paste |
| Right thumbs | `R●` / `M●` / `L●` | Right / middle / left click |

In Scroll mode, `U N E I` scroll up, left, down, and right. `O` and `?` apply
the same 4x and 1/4x scaling to both pointer movement and scrolling.

Ctrl and Shift are true toggles: they do not time out and remain held until the
same key is pressed again. Mouse-button locks behave the same way, but selecting
a different button lock transfers the hold, and exiting Mouse releases a locked
mouse button. Exiting Mouse does not release Ctrl or Shift, so toggle those off
before leaving the layer.

### Combos

| Combo | SVG | Action |
| --- | --- | --- |
| `Y+'` | `🖱` | Enter or exit Mouse |
| `O+?` | `🖱↕` | Switch Pointer / Scroll mode |
| `L+U` / `U+Y` / `L+Y` | `×` / `＋` / `↶` | Close / open / reopen browser tab |
| `L+N` / `Y+I` | `PWin` / `NWin` | Previous / next window |
| `J+M` | `🕘` | Clipboard history |
| `M+K` | `📸` | Screen snip |
| `H+,` / `H+.` / `,+.` | `R🔒` / `M🔒` / `L🔒` | Toggle-held right / middle / left mouse button |

The existing right-hand Base/Nav/Num combos remain unchanged; the table above
lists the combos active on Mouse and its Scroll/button-lock sublayers.
Browser-tab shortcuts use Ctrl, window switching uses Alt+Tab, and clipboard
history/screen snip use the Windows shortcuts `Win+V` and `Win+Shift+S`.

### Design rationale

- Everything is on the right half, so the left hand can remain off the keyboard
  or operate another device.
- `U N E I` reuse the Nav layer's directional positions. Switching to Scroll
  changes the behavior, not the direction map, and `J M` likewise retain Nav's
  page-up/page-down positions.
- `L` and `Y` switch tabs directly. Together with `U`, the same top-row cluster
  owns close, new, and reopen-tab actions, keeping browser navigation local.
- `O` and `?` are the fast and precise speed holds. Chording those two endpoints
  toggles Pointer/Scroll mode, making the mode switch mnemonic without consuming
  another key.
- Copy, cut, and paste are single keys because they are common and reversible.
  Persistent mouse-button holds use deliberate two-key combos on the same three
  keys, reducing accidental locked clicks.
- Right, middle, and left click live on the thumbs so the fingers can continue
  steering. Toggle-held Ctrl and Shift support selection and modified clicking
  without requiring an awkward simultaneous hold.

## Prompt shortcuts

Hold the Enter thumb for Fn, then press:

- `B` for Abstract
- `G` for Reason
- `V` for Plan

The prompt macros type without sending Enter. Press a prompt key again while it
is typing to cancel it.

## Build

The repository's GitHub Actions workflow builds both halves from `build.yaml`.
For a local west workspace, initialize the pinned manifest first:

```sh
west init -l config
west update
west zephyr-export
```

Then build each target from the workspace root:

```sh
west build -s zmk/app -d build-left -b 'nice_nano@2.0.0//zmk' -- \
  -DSHIELD=corne_left -DZMK_CONFIG="$PWD/config"

west build -s zmk/app -d build-right -b 'nice_nano@2.0.0//zmk' -- \
  -DSHIELD=corne_right -DZMK_CONFIG="$PWD/config"
```

## Diagrams

The checked-in SVGs are generated with keymap-drawer 0.23.0. See
[`draw/README.md`](draw/README.md) for the source files, legend, and exact
regeneration commands.
