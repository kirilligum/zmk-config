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

Press `Q+W` with the left hand or `Y+'` with the right hand from Base, Nav, or
Num to enter Mouse. Either combo exits. Mouse provides matching one-handed
3x5+3 controls on both halves, with shared Pointer, Scroll, speed, modifier, and
button-lock state.

![Mouse Pointer mode](mouse-pointer.svg)

The same keys in [Scroll mode](mouse-scroll.svg) scroll instead of moving the
pointer.

### Keys

| Left hand | Right hand | SVG | Action |
| --- | --- | --- | --- |
| `B` / `G` | `J` / `M` | `⇞` / `⇟` | Page up / page down |
| `W` / `P` | `L` / `Y` | `PTab` / `NTab` | Previous / next tab |
| `F` `R` `S` `T` | `U` `N` `E` `I` | `↑` `←` `↓` `→` | Move or scroll up / left / down / right |
| `A` / `Z` | `O` / `?` | `🐇` / `🐢` | Hold for 4x / 1/4x movement or scroll speed |
| `Q` / `V` | `'` / `K` | `⌃🔒` / `⇧🔒` | Toggle-held Ctrl / Shift |
| `D` / `C` / `X` | `H` / `,` / `.` | `⧉` / `✂` / `📋` | Copy / cut / paste |
| Left thumbs | Right thumbs | `L● M● R●` / `R● M● L●` | Left / middle / right click, mirrored by hand |

In Scroll mode, `F R S T` or `U N E I` scroll up, left, down, and right. The
speed keys apply the same 4x and 1/4x scaling to pointer movement and scrolling.

Ctrl and Shift are true toggles: they do not time out and remain held until the
same key is pressed again. Mouse-button locks behave the same way, but selecting
a different button lock transfers the hold, and exiting Mouse releases a locked
mouse button. Exiting Mouse does not release Ctrl or Shift, so toggle those off
before leaving the layer. Pointer/Scroll mode and mouse-button lock state are
shared: a mode or lock selected with one hand applies to both halves and can be
toggled or transferred from either hand.

### Combos

| Left hand | Right hand | SVG | Action |
| --- | --- | --- | --- |
| `Q+W` | `Y+'` | `🖱` | Enter or exit Mouse |
| `A+Z` | `O+?` | `🖱↕` | Switch Pointer / Scroll mode |
| `W+F` / `F+P` / `W+P` | `L+U` / `U+Y` / `L+Y` | `×` / `＋` / `↶` | Close / open / reopen browser tab |
| `W+R` / `P+T` | `L+N` / `Y+I` | `PWin` / `NWin` | Previous / next window |
| `B+G` | `J+M` | `🕘` | Clipboard history |
| `G+V` | `M+K` | `📸` | Screen snip |
| `D+C` / `D+X` / `C+X` | `H+,` / `H+.` / `,+.` | `R🔒` / `M🔒` / `L🔒` | Toggle-held right / middle / left mouse button |

The existing Base/Nav/Num combos remain unchanged; the table above lists the
combos active on Mouse and its Scroll/button-lock sublayers.
Browser-tab shortcuts use Ctrl, window switching uses Alt+Tab, and clipboard
history/screen snip use the Windows shortcuts `Win+V` and `Win+Shift+S`.

### Design rationale

- Both halves provide the same functions, so either hand can remain on the
  keyboard while the other operates another device.
- `F R S T` and `U N E I` keep directions spatially oriented on their half.
  Switching to Scroll changes the behavior, not the direction map; `B G` and
  `J M` likewise provide page up/down.
- `W P` and `L Y` switch tabs directly. Together with `F` or `U`, each top-row
  cluster owns close, new, and reopen-tab actions, keeping browser navigation
  local.
- `A Z` and `O ?` are the fast and precise speed holds. Chording either pair
  toggles Pointer/Scroll mode, making the mode switch mnemonic without consuming
  another key.
- Copy, cut, and paste are single keys because they are common and reversible.
  Persistent mouse-button holds use deliberate two-key combos on the same three
  keys, reducing accidental locked clicks.
- Mouse clicks mirror across the thumbs so the fingers can continue steering.
  Toggle-held Ctrl and Shift support selection and modified clicking without
  requiring an awkward simultaneous hold.

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
