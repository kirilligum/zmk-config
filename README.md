# Corne ZMK Gallium Colstag + QWERTY config

Personal 36-key Corne firmware with Gallium Colstag as the default alpha base
and QWERTY as an explicitly selectable second base. It has separate builds for
the left and right `nice_nano@2.0.0` halves. The configuration pins ZMK and its
modules in
[`config/west.yml`](config/west.yml); GitHub Actions builds the targets declared
in [`build.yaml`](build.yaml).

## Keymap

<img src="./overview.svg" alt="Compact Corne keymap: Base in the center, Fn at top-left, Nav at top-right, Num at bottom-left, Sys at bottom-right, with combos and the Right Pointer mouse layer below" width="100%" />

The center legends are Base. Corner legends are **Fn** at top-left, **Nav** at
top-right, **Num** at bottom-left, and **Sys** at bottom-right; the combo map is
shown separately in the second row, and the Right Pointer mouse layer is shown
in the third. The focused Mouse diagrams document both hands and Pointer/Scroll
modes. QWERTY appears in the [full layer-by-layer keymap](keymap.svg).

The Base alpha block is Gallium Colstag on a US/QWERTY host layout:

```text
B L D C V | J Y O U ,
N R T S G | P H A E I
X Q M W Z | K F ' . ?
```

The home-row holds are Gui / Alt / Shift / Ctrl on `N R T S` and the mirrored
Ctrl / Shift / Alt / Gui on `H A E I`. The four punctuation keys use these tap
and Shift outputs:

| Key | Tap | Shift | Ctrl+Shift |
| --- | --- | --- | --- |
| `,` | comma | `;` | `<` |
| `'` | apostrophe | `"` | — |
| `.` | period | `:` | `>` |
| `?` | question mark | `!` | — |

The outer thumbs are Backspace on the left and Right Arrow on the right. Hold
Space for Nav, Enter for Fn, and Smart for Num. Fn and Num together activate
Sys. Magic is repeat/sticky Shift on tap and regular Shift on hold.

### QWERTY base

QWERTY is the second-lowest layer and changes only the alpha block:

```text
Q W E R T | Y U I O P
A S D F G | H J K L '
Z X C V B | N M , . ?
```

It inherits the same thumbs and shares Nav, Fn, Num, Sys, Mouse, punctuation
behaviors, and physical combo topology with Gallium. To select the base, hold
Fn+Num for Sys and use the first two keys on the top-right row: `GAL` at the
Gallium `J` position returns to Gallium, while `QWE` at the Gallium `Y` position
selects QWERTY. Selection is explicit rather than toggled. Gallium remains the
power-on default.

### Alpha-base, Nav, and Num combos

Positions and timings follow the Urob-derived physical combo layout. Each
combo stays in the same physical position when the alpha base changes.

| Gallium | QWERTY | Base / Num | Nav |
| --- | --- | --- | --- |
| `L+D` | `W+E` | Escape | Escape |
| `B+C` | `Q+R` | Mouse Left | Mouse Left |
| `Y+,` | `U+P` | Mouse Right | Mouse Right |
| `R+T` | `S+D` | Tab; hold Alt+Shift | Tab; hold Alt+Shift |
| `T+S` | `D+F` | Leader; hold Shift+Ctrl | Leader; hold Shift+Ctrl |
| `R+T+S` | `S+D+F` | Shift+Leader; hold Alt+Shift+Ctrl | Shift+Leader; hold Alt+Shift+Ctrl |
| `Q+W` | `X+V` | Cut | Cut |
| `Q+M` | `X+C` | Copy | Copy |
| `M+W` | `C+V` | Paste | Paste |
| `Y+O` | `U+I` | Backspace | Backspace |
| `O+U` | `I+O` | Delete | Delete |
| `H+A` | `J+K` | `(`; Shift `<`; hold Ctrl+Shift | `<` |
| `A+E` | `K+L` | `)`; Shift `>`; hold Alt+Shift | `>` |
| `F+'` | `M+,` | `[` | `{` |
| `'+.` | `,+.` | `]` | `}` |

The vertical symbol combos are active on both alpha bases, Nav, and Num:

| Gallium left | QWERTY left | Output | Gallium right | QWERTY right | Output |
| --- | --- | --- | --- | --- | --- |
| `L+R` | `W+S` | `@` | `J+P` | `Y+H` | `^` |
| `D+T` | `E+D` | `#` | `Y+H` | `U+J` | `+` |
| `C+S` | `R+F` | `$` | `O+A` | `I+K` | `*` |
| `V+G` | `T+G` | `%` | `U+E` | `O+L` | `&` |
| `R+Q` | `S+X` | `` ` `` | `P+K` | `H+N` | `_` |
| `T+M` | `D+C` | `\` | `H+F` | `J+M` | `-` |
| `S+W` | `F+V` | `=` | `A+'` | `K+,` | `/` |
| `G+Z` | `G+B` | `~` | `E+.` | `L+.` | `|` |

## Mouse layer

Press `B+C` on Gallium (`Q+R` on QWERTY) from either alpha base, Nav, or Num to
enter Mouse Left. Use `Y+,` on Gallium (`U+P` on QWERTY) for Mouse Right. Only
the selected hand receives mouse bindings; the other hand remains on the
selected alpha base and is free for normal typing. The same physical combo
exits Mouse. Entry deterministically clears the other Mouse mode, so Mouse Left
and Mouse Right cannot remain active together. It also clears transient
Nav/Fn/Num/Sys state while preserving the selected alpha base.

![Mouse Pointer mode](mouse-pointer.svg)

The Pointer diagram contains both one-hand alternatives. The same keys in
[Scroll mode](mouse-scroll.svg) scroll instead of moving the pointer.

### Keys

| Left hand | Right hand | SVG | Action |
| --- | --- | --- | --- |
| `V` / `G` | `J` / `P` | `⇞` / `⇟` | Page up / page down |
| `C` | `Y` | `Esc` | Escape |
| `L` | `U` | `NWin` | Alt+Tab; keeps Alt held for two seconds |
| `D` `R` `T` `S` | `O` `H` `A` `E` | `↑` `←` `↓` `→` | Move or scroll up / left / down / right |
| `N` / `X` | `I` / `?` | `🐇` / `🐢` | Hold for 4x / 1/4x movement or scroll speed |
| `B` / `Z` | `,` / `K` | `Ctrl` / `Shift` | Tap one-shot, hold momentary, double-tap lock |
| `W` / `M` | `F` / `'` | `Copy` / `Paste` | Ctrl+C / Ctrl+V; Shift adds Ctrl+Shift |
| `Q` | `.` | `L Lock` | Hold LMB until the active LMB thumb or Mouse exit |
| Active thumbs | Active thumbs | `R● M● L●` / `L● M● R●` | Right / middle / left click, mirrored by hand |

In Scroll mode, `D R T S` or `O H A E` scroll up, left, down, and right. The
speed keys apply the same 4x and 1/4x scaling to pointer movement and scrolling.
They use Mouse-specific layers, so layer keys on the free hand cannot change
pointer speed.

Ctrl and Shift support three gestures: tap for a 900 ms one-shot modifier, hold
for a normal momentary modifier, or double-tap to lock until the next
double-tap. Shift therefore changes Copy/Paste into Ctrl+Shift+C/V. Exiting
Mouse releases Ctrl, Shift, Alt, and all mouse buttons, clears every Mouse
sublayer, returns the next entry to Pointer mode, and leaves the selected
Gallium or QWERTY base unchanged.

`L` or `U` presses Alt+Tab and keeps Alt held for two seconds after release, so
repeated taps move through the visible window switcher. Hold the active hand's
Shift key (`Z` or `K`) while tapping the window key to move backward. Any other
key or the two-second timeout releases Alt.

The LMB lock holds only left click, with no timeout. Press the active LMB thumb
or exit Mouse to release it. RMB and MMB remain ordinary thumb clicks.

### Combos

| Left hand | Right hand | SVG | Action |
| --- | --- | --- | --- |
| `B+C` | `Y+,` | `Mouse L` / `Mouse R` | Enter the selected hand or exit it |
| `N+X` | `I+?` | `P/S` | Switch Pointer / Scroll mode |
| `V+G` | `J+P` | `Clip` | Clipboard history |
| `G+Z` | `P+K` | `Snip` | Screen snip |

The table above lists the combos active on the selected Mouse hand and its
Scroll/LMB-lock sublayers. No Mouse combo contains a direction key, so pointer
and scroll movement starts without waiting for a combo timeout. Use Ctrl with
PgUp/PgDn to change tabs. Clipboard history and screen snip use the Windows
shortcuts `Win+V` and `Win+Shift+S`.

### Design rationale

- Mouse Left and Mouse Right are mirrored alternatives. Only one is active, so
  the other hand retains the selected Gallium or QWERTY base.
- `D R T S` and `O H A E` keep directions spatially oriented on their half.
  Switching to Scroll changes the behavior, not the direction map; `V G` and
  `J P` likewise provide page up/down.
- `L` and `U` provide a timed Alt+Tab session; Shift reverses it. `C` and `Y`
  provide direct Escape, while Ctrl+PgUp/PgDn handles both tab directions.
- `N X` and `I ?` are the fast and precise speed holds. Chording either pair
  toggles Pointer/Scroll mode, making the mode switch mnemonic without
  consuming another key.
- Copy and Paste use Ctrl+C/V so holding or locking Shift produces the terminal
  variants Ctrl+Shift+C/V. `Q` and `.` are the mirrored dedicated LMB-lock
  keys.
- Mouse clicks mirror across the thumbs so the fingers can continue steering.
  Tap/hold/double-tap Ctrl and Shift support both quick shortcuts and modified
  clicking without forcing one interaction style.

### Surfingkeys with the free Gallium half

The repo includes a browser-owned
[`Gallium-left Surfingkeys profile`](surfingkeys/README.md) for navigating with
the transparent left half while Mouse Right controls the pointer. It uses the
Backspace thumb as a Surfingkeys Normal-mode leader, keeps Insert-mode typing
unchanged, and requires no firmware or Mouse-layer change. The complete design
and browser acceptance sequence are in the
[`profile plan`](plans/gallium-surfingkeys-profile-plan.md).

## Prompt shortcuts

Hold the Enter thumb for Fn, then press these physical positions:

- Gallium `V` / QWERTY `T` for Abstract
- `G` in either base for Reason
- Gallium `Z` / QWERTY `B` for Plan

The prompt macros type without sending Enter. Press a prompt key again while it
is typing to cancel it.

## Switch debounce

Both halves use a 10 ms press debounce and a 20 ms release debounce, configured
globally in [`config/corne.conf`](config/corne.conf). The longer release window
suppresses contact chatter that can otherwise turn one physical tap into two or
three keypresses. These settings affect matrix scanning only; they do not change
the Space/Nav hold-tap timing or any keymap behavior.

If isolated taps still repeat after both halves are flashed, test USB versus
Bluetooth and inspect or swap the affected switches before increasing the
debounce further.

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
  -DSHIELD=corne_left -DZMK_CONFIG="$PWD/config" \
  -DZMK_EXTRA_MODULES="$PWD"

west build -s zmk/app -d build-right -b 'nice_nano@2.0.0//zmk' -- \
  -DSHIELD=corne_right -DZMK_CONFIG="$PWD/config" \
  -DZMK_EXTRA_MODULES="$PWD"
```

## Diagrams

The checked-in SVGs are generated with keymap-drawer 0.23.0. See
[`draw/README.md`](draw/README.md) for the source files, legend, and exact
regeneration commands.
