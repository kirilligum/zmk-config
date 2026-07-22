# Gallium Colstag Breaking Migration Plan

Status: implemented, published on `gallium`, and CI-validated; physical
certification and merge remain

Target branch: `gallium`

Target hardware: 36-key Corne, `nice_nano@2.0.0`, left and right shields

Canonical layout source: Gallium Colstag as published at
`https://github.com/GalileoBlues/Gallium`

Pinned reference inspected for this plan: `21a8a7bb64a80acd67e06b5209e30559688121fe`

## Implementation record — 2026-07-22

- Installed the exact Gallium Colstag Base matrix and four-key punctuation
  contract in `config/base.keymap`.
- Preserved all accepted Urob-derived combo positions and behavior except the
  approved Mouse entry/exit moves to `B+C` and `Y+,`.
- Removed the unused `bs_del` and `copy_cut` behaviors; no compatibility layer,
  legacy typing layer, or fallback path was added.
- Updated `README.md`, both curated diagram YAML files, `draw/README.md`, and all
  three checked-in SVGs. The focused Mouse diagrams and full browser-rendered
  keymap were visually inspected.
- `git diff --check`, the real keymap-drawer parse, and the static 43-node combo
  inventory pass.
- Clean local builds produced both firmware files:
  - left: 530,944 bytes, SHA-256
    `74f429f6883c2ea68dce4a1d7efc1222f088a516b9dac383302586206b3b854c`;
  - right: 385,024 bytes, SHA-256
    `cd6db0cc0ad02fbfa6bb51ae2fc57b8c1e59b53438f6d5ce249e50b0133ae63d`.
- Combo-collision profiling is intentionally non-blocking and tracked in
  [issue #2](https://github.com/kirilligum/zmk-config/issues/2). Revisit it only
  if real-world use shows repeatable accidental activations.
- Migration commit `13afa3a` is pushed to `origin/gallium` and handed off in
  [draft PR #3](https://github.com/kirilligum/zmk-config/pull/3). Both the push
  and pull-request workflows passed; their `firmware` artifacts were downloaded
  and verified to contain the 530,944-byte left UF2 and 385,024-byte right UF2.

## Objective

Replace the current Colemak-DH-derived typing layout with one canonical Gallium
Colstag layout while retaining the keyboard's useful interaction system:

- home-row modifiers;
- Smart Num and Magic Shift;
- Nav, Fn, Num, Sys, and bilateral Mouse layers;
- leader sequences;
- cancelable prompt keys;
- editing, symbol, leader, and mouse combos;
- pointer, scroll, speed, modifier-lock, window-switching, and click-lock mouse
  behaviors.

This is an intentional breaking change. The finished firmware must contain no
Colemak layer, no toggle back to the old layout, no compatibility aliases, and
no stale Colemak labels in documentation or generated artifacts. Generic
internal names such as `DEF` and `Base` remain because they describe the
default layer's role, not its alphabet. Git history remains the emergency
recovery mechanism; it is not exposed as a runtime fallback.

## Non-negotiable finished state

1. Layer 0 remains the sole `DEF`/`Base` typing layer and contains only the
   matrix specified below.
2. There is no Colemak/Colemak-DH layer, layer toggle, conditional path, or
   documented alternative.
3. The letter matrix is exact Gallium Colstag. Its four prose-punctuation keys
   are comma, apostrophe, period, and question mark; Shift produces semicolon,
   double quote, colon, and exclamation mark respectively.
4. Existing positional layers and mouse behavior remain functionally intact.
5. `Y+O` and `O+U` remain direct Backspace/Delete combos, matching Urob's
   adjacent top-row editing pattern. The dedicated Backspace thumb and Nav
   Delete remain additional access paths.
6. Parentheses keep Urob's two-key HRM-aware positions. Their tap, shifted tap,
   and exact two-modifier hold behaviors are specified and physically tested.
7. The only combo-position changes are the explicitly approved bilateral Mouse
   chords (`B+C`, `Y+,`) and their Mouse exit counterparts. Tab remains at
   Urob's physical `LM3+LM2` position, which is `R+T` on Gallium; every other
   combo position also remains fixed.
8. Both firmware halves compile locally against the pinned west workspace and
   in the repository's existing GitHub Actions workflow.
9. Both checked-in YAML diagram sources and all three SVGs are updated with the
   repository's existing keymap-drawer 0.23.0 workflow and visually inspected.
10. Both physical halves are flashed and the complete on-device certification
    matrix passes before the change is merged to `main`.
11. The final commit, PR, main-branch build, and branch cleanup are completed;
    there is no post-merge cleanup phase.

## Canonical Base matrix

### Physical position map

| Position | Tap | Hold/secondary behavior |
| --- | --- | --- |
| `LT4 LT3 LT2 LT1 LT0` | `B L D C V` | plain letters |
| `RT0 RT1 RT2 RT3 RT4` | `J Y O U ,` | comma shifts to `;` |
| `LM4 LM3 LM2 LM1 LM0` | `N R T S G` | `N/R/T/S` hold `Gui/Alt/Shift/Ctrl`; `G` plain |
| `RM0 RM1 RM2 RM3 RM4` | `P H A E I` | `P` plain; `H/A/E/I` hold `Ctrl/Shift/Alt/Gui` |
| `LB4 LB3 LB2 LB1 LB0` | `X Q M W Z` | plain letters |
| `RB0 RB1 RB2 RB3 RB4` | `K F ' . ?` | punctuation shifts to `" : !` |

Rendered as the intended 3x10 matrix:

```text
B L D C V   J Y O U ,
N R T S G   P H A E I
X Q M W Z   K F ' . ?
```

The host input source remains standard US/QWERTY. Gallium is emitted by the
firmware; enabling an operating-system Gallium remap would double-remap it and
is explicitly unsupported.

### Thumb contract

Thumb behavior stays positional and unchanged:

| Physical thumb | Behavior |
| --- | --- |
| Outer left | Backspace |
| Left home | tap Space; hold Nav; shifted tap emits `. ` and sticky Shift |
| Left inner | tap Enter; hold Fn |
| Right inner | tap Num Word; double-tap sticky Num; hold Num |
| Right home | tap Repeat/sticky Shift; shifted tap Caps Word; hold Shift |
| Outer right | Right Arrow |

`Fn + Num` continues to activate Sys. Nav's Cancel continues to terminate Caps
Word and automatic layers.

## Canonical punctuation and symbol access

Gallium's pinned XKB definition assigns comma/less-than, apostrophe/double
quote, semicolon/colon, and period/greater-than to its four 3x10 punctuation
positions; it also leaves slash/question-mark on `AC11`, an additional desktop
key outside that 3x10. This compact Corne deliberately uses the Urob-style
shifted punctuation behaviors while replacing direct semicolon with direct
question mark: comma, apostrophe, period, and question mark shift to semicolon,
double quote, colon, and exclamation mark. Use exactly these finished paths:

| Output | Final input |
| --- | --- |
| `,` / `;` / `<` | `comma_morph` / Shift+comma / Ctrl+Shift+comma on `RT4` |
| `'` / `"` | apostrophe / Shift+apostrophe on `RB2` |
| `.` / `:` / `>` | `dot_morph` / Shift+period / Ctrl+Shift+period on `RB3` |
| `?` / `!` | `qexcl` / Shift+`qexcl` on `RB4` |
| `/` | `A+'` vertical combo |
| `[` / `{` | `F+'` combo / Shift plus the same combo |
| `]` / `}` | `'+.` combo / Shift plus the same combo |
| `(` / `<` | `H+A` combo / external Shift plus the same combo |
| `)` / `>` | `A+E` combo / external Shift plus the same combo |
| number-row symbols | existing vertical symbol combos or Shift+Num digit |

Retain Urob's complete behavior: `comma_inner_morph` and `dot_inner_morph` for
Ctrl+Shift angle brackets, `lpar_lt` and `rpar_gt` for shifted parenthesis
combos, and the direct Nav-only `<`, `>`, `{`, and `}` combos. These are
intentional layer-local access paths, not migration compatibility behavior.

## Layer contract

### Base (`DEF`)

- Install the exact matrix and hold behaviors above.
- Keep Smart, Magic, Sentence Space, Enter/Fn, Backspace, and Right Arrow as
  specified; do not add another base layer.
- Keep the generic internal identifier `DEF` and rendered name `Base`; do not
  add a redundant `GALLIUM` alias or rename-only churn.

### Nav

Keep every action at its current physical position: Close, previous/next
window, sticky modifiers, page movement, navigation/editing hold-taps, Enter,
Insert, Tab, Cancel, Backspace, and Right Arrow. The inactive hand remains on
Base.

### Fn

Keep every action at its current physical position. Gallium changes the access
legends as follows:

- `V` = Abstract prompt (`LT0`)
- `G` = Reason prompt (`LM0`)
- `Z` = Plan prompt (`LB0`)
- `,` = brightness up (`RT4`)
- `I` = brightness down (`RM4`)
- `?` = display switcher (`RB4`)
- `K/F/'` = Pin Application / Pin Window / Desktop Manager (`RB0/RB1/RB2`)

Function keys, media keys, desktop navigation, prompt output, prompt
cancellation, and all direct host shortcuts remain unchanged.

### Num and Sys

Keep the numeric keypad geometry, home-row modifier holds, wireless profile
selection, bootloader, and reset positions unchanged. Do not create a Gallium
specific numeric variant.

### Mouse layers

Keep all 13 layer indices, the `DEF` return target, and all pointer behavior.
Only Base-facing legends change. The finished active-hand maps are:

| Action | Left-hand Base key | Right-hand Base key |
| --- | --- | --- |
| Ctrl gesture | `B` | `,` |
| timed Alt+Tab | `L` | `U` |
| up | `D` | `O` |
| Escape | `C` | `Y` |
| page up | `V` | `J` |
| 4x speed | `N` | `I` |
| left/down/right | `R/T/S` | `H/A/E` |
| page down | `G` | `P` |
| 1/4x speed | `X` | `?` |
| left-click lock | `Q` | `.` |
| Paste | `M` | `'` |
| Copy | `W` | `F` |
| Shift gesture | `Z` | `K` |

The inactive hand remains transparent to Base. Pointer/scroll geometry,
speed scaling, mirrored mouse-button thumbs, timed Alt release, modifier locks,
LMB lock, and exit cleanup remain unchanged.

## Complete finished key inventory

The following is the complete user-visible key contract. Each 10-key row is
ordered `LT4..LT0 | RT0..RT4`, `LM4..LM0 | RM0..RM4`, or
`LB4..LB0 | RB0..RB4`. The thumb row is left outer/home/inner, then right
inner/home/outer. `·` means transparent, so the next active layer supplies the
key. `tap/hold` describes a hold-tap.

### Base

```text
B        L        D          C        V       | J       Y          O          U        , / ;
N/Gui    R/Alt    T/Shift    S/Ctrl   G       | P       H/Ctrl     A/Shift    E/Alt    I/Gui
X        Q        M          W        Z       | K       F          ' / "      . / :    ? / !
Bspc     Space/Nav  Enter/Fn                  | Smart/Num  Magic/Shift  Right
```

Ctrl+Shift+comma/period produce `<`/`>`. Smart taps Num Word, double-taps
sticky Num, and holds momentary Num. Magic taps Repeat or sticky Shift, shifted
tap activates Caps Word, and hold is Shift. Shifted Space emits `. ` followed
by sticky Shift.

### Nav

```text
Close    ·        PrevWin      NextWin      · | PgUp   Bspc/word-bspc  Up/doc-home  Del/word-del  ·
sGui     sAlt     sShift       sCtrl        · | PgDn   Left/home        Down/doc-end Right/end     Enter
·        ·        ·            ·            · | Insert Tab              ·            ·             ·
Bspc     ·        ·                           | ·      Cancel           Right
```

The four left home modifiers are sticky. `Cancel` stops Caps Word and automatic
layers. The Nav-only combo variants provide direct `<`, `>`, `{`, and `}`.

### Fn

```text
F12      F7       F8          F9          Abstract | ·       Prev      Vol+       Next      Bright+
F11/Gui  F4/Alt   F5/Shift    F6/Ctrl     Reason   | ·       PDesk/Ctrl Vol-/Shift NDesk/Alt Bright-
F10      F1       F2          F3          Plan     | PinApp  PinWin     Alt+`      ·         Displays
Bspc     ·        ·                                  | Mute    Play/Pause  Right
```

The three prompt keys type cancelable text without Enter. `Displays` is
Gui+P. `PinApp`, `PinWin`, and desktop switching retain their current host
shortcuts.

### Num

```text
·        7        8          9        · | · · · · ·
0/Gui    4/Alt    5/Shift    6/Ctrl   · | · · · · ·
·        1        2          3        · | · · · · ·
Bspc     ·        ·                     | · · Right
```

### Sys (`Fn+Num`)

```text
BT1      BT2      BT3      BT4      BT Clear | · · · · ·
·        ·        ·        ·        Boot     | Boot · · · ·
·        ·        ·        ·        Reset    | Reset · · · ·
Bspc     ·        ·                            | · · Right
```

### Mouse Left Pointer

```text
Ctrl*    AltTab2s MouseUp    Esc      PgUp | · · · · ·
4x       MouseL   MouseDn    MouseR   PgDn | · · · · ·
1/4x     LMBLock  Paste      Copy     Shift* | · · · · ·
RClick   MClick   LClick                         | · · ·
```

### Mouse Right Pointer

```text
· · · · · | PgUp   Esc      MouseUp    AltTab2s Ctrl*
· · · · · | PgDn   MouseL   MouseDn    MouseR   4x
· · · · · | Shift* Copy     Paste      LMBLock  1/4x
· · ·                         | LClick  MClick   RClick
```

`Ctrl*` and `Shift*` mean tap one-shot, hold momentary, double-tap lock.

### Mouse Scroll overlays

The selected hand's Scroll layer replaces only its four pointer directions:

```text
Mouse Left Scroll
· · ScrollUp · · | · · · · ·
· ScrollLeft ScrollDown ScrollRight · | · · · · ·
· · · · · | · · · · ·
· · · | · · ·

Mouse Right Scroll
· · · · · | · · ScrollUp · ·
· · · · · | · ScrollLeft ScrollDown ScrollRight ·
· · · · · | · · · · ·
· · · | · · ·
```

### Mouse processor and lock overlays

Mouse Fast and Mouse Precision have 36 transparent keys. Holding the 4x key
activates Mouse Fast's `4/1` pointer and scroll scaler; holding the 1/4x key
activates Mouse Precision's `1/4` scaler. They work over Pointer and Scroll.

The selected hand's Lock overlay is also transparent except for two keys:

| Lock state | Disabled key | LMB-release key |
| --- | --- | --- |
| Mouse Left Lock | `LB3` (`Q`, the LMB-lock key) | left inner thumb |
| Mouse Right Lock | `RB3` (`.`, the LMB-lock key) | right inner thumb |

`Ctrl*` and `Shift*` mean tap one-shot, hold momentary, and double-tap lock.
The inactive hand remains on Base in every Mouse state.

## Complete combo specification

The finished tree contains exactly 43 combo nodes: 19 fast editing/control
nodes (including layer-local symbol variants), 16 vertical-symbol nodes, and
8 Mouse-only nodes. The tables below enumerate every node; implementation must
fail review if the firmware contains an unlisted combo or omits a listed one.

### Timing policy

Keep the proven timing constants unchanged during the layout cutover so layout
and timing are not confounded:

- fast horizontal/deliberate combos: 18 ms term, 150 ms prior idle;
- vertical symbol combos: 30 ms term, 50 ms prior idle;
- mouse-layer combos: 30 ms term, no prior-idle requirement.

Any timing correction discovered during physical certification is made and
re-certified before merge. No timing follow-up is deferred after release.

### Base/Nav/Num editing and control combos

| Action | Positions | Base labels | Active layers | Hold result when applicable |
| --- | --- | --- | --- | --- |
| Escape | `LT3 LT2` | `L+D` | Base, Nav, Num | n/a |
| Mouse Left | `LT4 LT1` | `B+C` | Base, Nav, Num | n/a |
| Mouse Right | `RT1 RT4` | `Y+,` | Base, Nav, Num | n/a |
| Tab | `LM3 LM2` | `R+T` | Base, Nav, Num | left Alt+left Shift |
| Leader | `LM2 LM1` | `T+S` | Base, Nav, Num | left Shift+left Ctrl |
| Shift+Leader | `LM3 LM2 LM1` | `R+T+S` | Base, Nav, Num | left Alt+left Shift+left Ctrl |
| Cut | `LB3 LB1` | `Q+W` | Base, Nav, Num | n/a |
| Copy | `LB3 LB2` | `Q+M` | Base, Nav, Num | n/a |
| Paste | `LB2 LB1` | `M+W` | Base, Nav, Num | n/a |
| Backspace | `RT1 RT2` | `Y+O` | Base, Nav, Num | n/a |
| Delete | `RT2 RT3` | `O+U` | Base, Nav, Num | n/a |
| Left parenthesis / less-than | `RM1 RM2` | `H+A` | Base and Num / Nav | left Ctrl+right Shift on Base/Num |
| Right parenthesis / greater-than | `RM2 RM3` | `A+E` | Base and Num / Nav | right Shift+left Alt on Base/Num |
| Left bracket | `RB1 RB2` | `F+'` | Base, Num | n/a |
| Right bracket | `RB2 RB3` | `'+.` | Base, Num | n/a |
| Left brace | `RB1 RB2` | `F+'` | Nav | n/a |
| Right brace | `RB2 RB3` | `'+.` | Nav | n/a |

Backspace/Delete deliberately remain at Urob's adjacent top-row positions, now
labelled `Y+O` and `O+U`. Their 18 ms term and 150 ms prior-idle guard remain
unchanged. Certification must prove deliberate edits and ordinary `yo`, `ou`,
and `you` rolls in both editable and empty fields.

Tab, Leader, Shift+Leader, clipboard, parenthesis, bracket, Backspace/Delete,
and every vertical-symbol combo retain their pre-migration physical positions,
layer scopes, timings, bindings, and hold arguments. Only Mouse entry and exit
use the approved new positions above.

The parenthesis combos retain `lpar_lt` and `rpar_gt`: tap `H+A`/`A+E` for
parentheses and apply external Shift for angle brackets. Nav retains its direct
angle-bracket and brace variants at the same physical positions.

The HRM-aware combo wrapper turns each combo into a tap/hold decision. The hold
argument is the union of the modifiers on the constituent home-row keys, with
modifier sides preserved:

- `H+A`: `H` is left Ctrl and `A` is right Shift, so the existing
  `RS(LCTRL)` binding remains exact.
- `A+E`: `A` is right Shift and `E` is left Alt, so the existing `RS(LALT)`
  binding remains exact.

The migration does not preemptively add a third key. The 18 ms combo term and
150 ms prior-idle guard remain responsible for distinguishing deliberate
chords from `ha` and `ae` rolls. Physical certification proves both the symbol
taps and the two-modifier hold reports.

### Vertical symbol combos

Keep their physical columns and outputs unchanged; their Base labels become:

| Output | Positions | Base labels |
| --- | --- | --- |
| `@` | `LT3 LM3` | `L+R` |
| `#` | `LT2 LM2` | `D+T` |
| `$` | `LT1 LM1` | `C+S` |
| `%` | `LT0 LM0` | `V+G` |
| grave | `LM3 LB3` | `R+Q` |
| backslash | `LM2 LB2` | `T+M` |
| `=` | `LM1 LB1` | `S+W` |
| `~` | `LM0 LB0` | `G+Z` |
| `^` | `RT0 RM0` | `J+P` |
| `+` | `RT1 RM1` | `Y+H` |
| `*` | `RT2 RM2` | `O+A` |
| `&` | `RT3 RM3` | `U+E` |
| `_` | `RM0 RB0` | `P+K` |
| `-` | `RM1 RB1` | `H+F` |
| `/` | `RM2 RB2` | `A+'` |
| `\|` | `RM3 RB3` | `E+.` |

All remain active on Base, Nav, and Num.

### Mouse-only combos

Keep identifiers, outputs, active layers, and timing unchanged. Clipboard,
snip, and Pointer/Scroll positions remain fixed; only the two exit positions
move with the approved entry chords.

| Action | Left-hand chord | Right-hand chord | Active layers |
| --- | --- | --- | --- |
| clipboard history | `V+G` | `J+P` | selected hand's Pointer/Scroll/Lock layers |
| screen snip | `G+Z` | `P+K` | selected hand's Pointer/Scroll/Lock layers |
| Pointer/Scroll | `N+X` | `I+?` | selected hand's Pointer/Scroll/Lock layers |
| exit and cleanup | `B+C` | `Y+,` | selected hand's Pointer/Scroll/Lock layers |

No mouse combo may contain a direction key. This preserves immediate pointer
and scroll response.

### Explicit combo-remap rule

Do not infer further remaps from corpus frequency. The approved exceptions are
exactly:

- Mouse Left: `LT4+LT3` to `LT4+LT1`, producing `B+C`;
- Mouse Right: `RT3+RT4` to `RT1+RT4`, producing `Y+,`;
- Mouse exits move to the same positions as their corresponding entry chords.

Every other combo position stays fixed. In particular, Tab remains
`LM3+LM2`: Urob labels it `R+S`, while Gallium labels the same switches `R+T`.
Its tap remains Tab and its held HRM aggregate remains Alt+Shift. Exercise
`bc`, `y,`, `rt`, `ts`, `ha`, `ae`, `yo`, and `ou` during physical
certification.

## Complete leader-sequence specification

Leader is entered with `T+S`; Shift+Leader is entered with `R+T+S`. Left or
right Shift is ignored while matching the following sequences, so Shift+Leader
selects the shifted Unicode form without changing the recognized letters.

| Sequence | Leader output/action | Shift+Leader output |
| --- | --- | --- |
| `A` | `ä` | `Ä` |
| `O` | `ö` | `Ö` |
| `U` | `ü` | `Ü` |
| `S` | `ß` | `ẞ` |
| `E A` | `α` | `Α` |
| `E B` | `β` | `Β` |
| `E G` | `γ` | `Γ` |
| `E D` | `δ` | `Δ` |
| `E E` | `ε` | `Ε` |
| `E Z` | `ζ` | `Ζ` |
| `E H` | `η` | `Η` |
| `E V` | `θ` | `Θ` |
| `E I` | `ι` | `Ι` |
| `E K` | `κ` | `Κ` |
| `E L` | `λ` | `Λ` |
| `E M` | `μ` | `Μ` |
| `E N` | `ν` | `Ν` |
| `E X` | `ξ` | `Ξ` |
| `E O` | `ο` | `Ο` |
| `E P` | `π` | `Π` |
| `E R` | `ρ` | `Ρ` |
| `E S` | `σ` | `Σ` |
| `E T` | `τ` | `Τ` |
| `E U` | `υ` | `Υ` |
| `E F` | `ϕ` | `Φ` |
| `E C` | `χ` | `Χ` |
| `E Y` | `ψ` | `Ψ` |
| `E W` | `ω` | `Ω` |
| `U S B` | select USB output when wireless support is compiled | not a shifted-text sequence |
| `B L E` | select BLE output when wireless support is compiled | not a shifted-text sequence |
| `R E S E T` | reset the board | not a shifted-text sequence |
| `B O O T` | enter the bootloader | not a shifted-text sequence |

These 32 bindings and outputs are identical to pinned Urob; only the Gallium
letters used to type the sequences occupy different physical keys.

## Exact differences from pinned Urob

This comparison is against Urob commit
`908e50817bd23b3209cd04a2c7cc3685b043fb61`, not a moving branch. “Same
position” means the physical Corne switch is unchanged even when the Gallium
legend on that switch differs.

### Base keys and thumbs

| Physical row | Pinned Urob | Finished product |
| --- | --- | --- |
| Top | `Q W F P B \| J L U Y '` | `B L D C V \| J Y O U ,` |
| Home | `A/Gui R/Alt S/Shift T/Ctrl G \| M N/Ctrl E/Shift I/Alt O/Gui` | `N/Gui R/Alt T/Shift S/Ctrl G \| P H/Ctrl A/Shift E/Alt I/Gui` |
| Bottom | `Z X C D V \| K H , . ?` | `X Q M W Z \| K F ' . ?` |
| Main thumbs | `Space/Nav Enter/Fn \| Smart/Num Magic/Shift` | same four behaviors |
| Outer thumbs | none in Urob's 34-key base macro | `Backspace \| Right Arrow`, retained from this repo's 36-key hardware contract |

The HRM modifier order and sides stay Urob's `Gui Alt Shift Ctrl | Ctrl Shift
Alt Gui`; only the letters under those holds change. Urob places apostrophe on
`RT4` and comma on `RB2`; the target swaps those prose keys so Gallium keeps
comma at `RT4` and apostrophe at `RB2`. Period and question mark remain on
`RB3/RB4`. The target retains Urob's useful Shift behavior, yielding
comma/semicolon, apostrophe/double quote, period/colon, and question
mark/exclamation mark.

### Layers and behavior engine

| Area | Pinned Urob | Finished product |
| --- | --- | --- |
| Layer count | 6: Base, Nav, Fn, Num, Sys, Mouse | 13: Base, Nav, Fn, Num, Sys, Fast, Precision, Left Pointer/Scroll/Lock, Right Pointer/Scroll/Lock |
| Nav | 34-key Urob map | same 30-key interior actions plus outer Backspace/Right; transparent positions resolve to Gallium Base |
| Num | 34-key Urob keypad | same 30-key interior keypad/HRMs plus outer Backspace/Right |
| Sys | 34-key Urob wireless/reset map | same 30-key interior actions plus outer Backspace/Right |
| Fn | function/media/desktop map | same map plus Abstract/Reason/Plan prompts at `LT0/LM0/LB0`, brightness at `RT4/RM4`, Displays at `RB4`, and outer Backspace/Right |
| Mouse entry | one `F+P` `smart_mouse` tri-state/toggle | direct `B+C` to Mouse Left and `Y+,` to Mouse Right |
| Mouse hand | one right-hand pointer/scroll layout | mirrored, selectable left- or right-hand pointer layout; inactive hand falls through to Gallium Base |
| Mouse modes | pointer and scroll mixed on one layer | explicit Pointer/Scroll toggle plus per-hand LMB-lock overlays |
| Mouse speed | Nav gives 3x pointer/2x scroll; Fn gives 1/2x | dedicated 4x and 1/4x processor layers for pointer and scroll |
| Mouse extras | page movement, pointer, scroll, three clicks | adds Escape, Copy/Paste, clipboard history, screen snip, Ctrl/Shift one-shot/hold/lock, timed Alt+Tab, LMB lock, and exit cleanup |
| Leader | German, Greek, transport, reset, boot sequences | identical sequence set and bindings |
| Prompts | absent | three cancelable no-Enter text prompts |
| Unused helpers | defines `bs_del` and `copy_cut` | deletes both because no finished key or combo binds them |
| Core timing/typing behaviors | Smart Num, Magic Shift, Sentence Space, HRMs, Nav hold-taps | retained without timing changes |

For clarity, pinned Urob's entire Mouse key surface is:

```text
· · · · · | · PgUp PointerUp PgDn ·
· · · · · | ScrollLeft PointerLeft PointerDown PointerRight ScrollRight
· · · · · | · LClick MClick RClick ·
· ·       | ScrollUp ScrollDown
```

The target's complete replacement surfaces are the Mouse Left/Right Pointer,
Scroll, processor, and lock inventories above; there is no retained Urob Mouse
layer or fallback toggle.

### Horizontal and editing combo comparison

| Action | Pinned Urob chord | Finished chord | Physical change | Output/hold difference |
| --- | --- | --- | --- | --- |
| Escape | `W+F` | `L+D` | none: `LT3+LT2` | none |
| Mouse | `F+P` | Mouse Left `B+C`; Mouse Right `Y+,` | replaced by `LT4+LT1` and `RT1+RT4` | smart toggle replaced by explicit hand entry |
| Tab | `R+S` | `R+T` | none: `LM3+LM2` | none; tap stays Tab and hold stays Alt+Shift |
| Leader | `S+T` | `T+S` | none: `LM2+LM1` | none; held modifiers remain Shift+Ctrl |
| Shift+Leader | `R+S+T` | `R+T+S` | none: `LM3+LM2+LM1` | none; held modifiers remain Alt+Shift+Ctrl |
| Cut | `X+D` | `Q+W` | none: `LB3+LB1` | none |
| Copy | `X+C` | `Q+M` | none: `LB3+LB2` | none |
| Paste | `C+D` | `M+W` | none: `LB2+LB1` | none |
| Backspace | `L+U` | `Y+O` | none: `RT1+RT2` | none |
| Delete | `U+Y` | `O+U` | none: `RT2+RT3` | none |
| Left parenthesis/Nav `<` | `N+E` | `H+A` | none: `RM1+RM2` | none; Base/Num hold remains Ctrl+Shift |
| Right parenthesis/Nav `>` | `E+I` | `A+E` | none: `RM2+RM3` | none; Base/Num hold remains Shift+Alt |
| Left bracket/Nav brace | `H+,` | `F+'` | none: `RB1+RB2` | none |
| Right bracket/Nav brace | `,+.` | `'+.` | none: `RB2+RB3` | none |

Thus Tab, Backspace/Delete, parentheses, brackets, Leader, Shift+Leader,
clipboard, and Escape stay at Urob's physical positions. Urob calls Tab `R+S`
because `LM3+LM2` carries those letters there; Gallium calls the same physical
chord `R+T`. Preserving the positions also preserves Tab's Alt+Shift hold and
its overlap with `T+S` Leader and three-key `R+T+S` Shift+Leader.

### Vertical symbol combo comparison

All 16 outputs, physical positions, layers, terms, and prior-idle values remain
Urob's. Only the Base legends change:

| Output | Pinned Urob chord | Finished chord | Positions |
| --- | --- | --- | --- |
| `@` | `W+R` | `L+R` | `LT3+LM3` |
| `#` | `F+S` | `D+T` | `LT2+LM2` |
| `$` | `P+T` | `C+S` | `LT1+LM1` |
| `%` | `B+G` | `V+G` | `LT0+LM0` |
| grave | `R+X` | `R+Q` | `LM3+LB3` |
| backslash | `S+C` | `T+M` | `LM2+LB2` |
| `=` | `T+D` | `S+W` | `LM1+LB1` |
| `~` | `G+V` | `G+Z` | `LM0+LB0` |
| `^` | `J+M` | `J+P` | `RT0+RM0` |
| `+` | `L+N` | `Y+H` | `RT1+RM1` |
| `*` | `U+E` | `O+A` | `RT2+RM2` |
| `&` | `Y+I` | `U+E` | `RT3+RM3` |
| `_` | `M+K` | `P+K` | `RM0+RB0` |
| `-` | `N+H` | `H+F` | `RM1+RB1` |
| `/` | `E+,` | `A+'` | `RM2+RB2` |
| `\|` | `I+.` | `E+.` | `RM3+RB3` |

### Combos added beyond pinned Urob

Pinned Urob has no Mouse-only combo nodes. The target retains this repo's eight
bilateral nodes: clipboard history, screen snip, Pointer/Scroll toggle, and
exit/cleanup for each hand. Their finished chords are exactly the eight entries
in the Mouse-only combo table above. No other combo is added.

## External ideas reviewed and final disposition

References inspected for this finished design:

- Gallium at `21a8a7bb64a80acd67e06b5209e30559688121fe`;
- Urob ZMK config at `908e50817bd23b3209cd04a2c7cc3685b043fb61`;
- Anachron ZMK config at `53e3e05685370dd37e38c788fa3066c70963e547`.

Adopt the following ideas:

- Urob/Anachron's direct comma, apostrophe, period, and question-mark prose
  keys, with intuitive Shift outputs `; " : !`;
- Urob's established parenthesis/bracket combos and their intentional Nav-layer
  angle-bracket/brace variants;
- the repository's existing keymap-drawer 0.23.0 source-and-render workflow;
- the existing project's Urob-derived Smart/Magic/Sentence/HRM behavior and
  bilateral one-handed Mouse design.

Explicitly do not import the following into the finished product:

- Anachron's thumb-plus-key acceleration system: it expands to almost one
  hundred combos and its published configuration requires a custom ZMK fork
  with multiple unmerged features. This project stays on its pinned upstream
  module graph.
- Anachron's fixed-order vertical same-finger-bigram macros: they discard the
  user's key order and add alpha-combo ambiguity exactly while Gallium muscle
  memory is being learned. Gallium's documented difficult pairs remain ordinary
  letters and may be alt-fingered by the typist; firmware does not rewrite them.
- another symbol layer, another base layer, tap-dance punctuation, or any combo
  position change beyond the approved bilateral Mouse entry/exit chords.
  Urob's remaining physical combo topology is the complete contract.

These are final scope decisions, not a deferred feature list.

## Required removals

Delete rather than retain or deprecate all of the following:

- the Colemak-DH-derived matrix and every stale row/legend derived from it;
- the direct semicolon on `RB3` and direct period on `RB4` from the stock
  Gallium punctuation positions; the final positions are `.` and `?`;
- unused `bs_del` and `copy_cut` behaviors;
- old prompt shortcut labels `B/G/V`;
- old mouse labels and instructions such as `Q+W`, `Y+'`, `F R S T`, and
  `U N E I`;
- any local or remote `gallium` topic branch after the certified change is on
  `main`.

Do not change or remove the prompt engine, leader module, mouse engine, ZMK
module pins, Bluetooth tuning, hardware targets, or GitHub Actions workflow.
Dependency upgrades and new testing/generation infrastructure are outside this
atomic cutover.

## File-by-file implementation map

### Firmware source

1. `config/base.keymap`
   - install the exact Gallium matrix and HRMs;
   - keep `DEF` and `Base`;
   - retain Urob's nested comma/dot morphs, `qexcl`, `lpar_lt`, and `rpar_gt`;
   - remove all behaviors listed in Required removals;
   - keep Smart, Magic, Sentence, Nav, Fn, Num, Sys, and Mouse behavior code.
2. `config/combos.dtsi`
   - move Mouse Left entry/exit to `LT4 LT1` and Mouse Right entry/exit to
     `RT1 RT4`;
   - retain Tab exactly as `LM3 LM2` with `&hml LS(LALT)TAB`, producing
     `R+T` on Gallium with its existing Alt+Shift hold;
   - retain `bspc`, `del`, and every other combo's identifier, positions, layer
     list, binding, timeout, prior-idle value, and HRM hold argument.

### Documentation and diagram sources

3. `draw/keymap.yaml`
   - update the Base matrix, HRM legends, Fn access legends, Mouse-facing
     labels, and all combo labels from the finished firmware;
   - keep the curated Base/Nav/Fn/Num/Sys/Mouse Left/Mouse Right/Combos
     presentation structure and hidden Nav symbol variants;
   - compare it position-by-position with a fresh keymap-drawer parse of
     `config/corne.keymap`; do not blindly replace the curated diagram source
     with the parser's 13-layer raw output.
4. `draw/mouse-layer.yaml`
   - update every Base corner legend for Gallium on all four Pointer/Scroll
     panels;
   - move the left exit dendron from `[0, 1]` to `[0, 3]` and the right exit
     dendron from `[8, 9]` to `[6, 9]`, matching `B+C` and `Y+,`;
   - retain clipboard, snip, Pointer/Scroll, direction, speed, modifier, click,
     and transparent-hand geometry.
5. `README.md`
   - identify the firmware as Gallium Colstag;
   - show the exact 3x10 matrix and US-host-layout requirement;
   - document retained `Y+O` Backspace and `O+U` Delete combos and their
     accidental-trigger guards;
   - replace every prompt, Fn, mouse, combo, and punctuation access label;
   - document the canonical shifted-symbol paths and `R+T` Tab;
   - retain build and diagram regeneration instructions.
6. `draw/README.md`
   - mirror the finished prompt/Fn/mouse labels;
   - retain the existing parse/draw commands and explain that the YAML files are
     checked-in diagram sources reviewed against firmware.
7. `keymap.svg`, `mouse-pointer.svg`, and `mouse-scroll.svg`
   - regenerate with keymap-drawer 0.23.0;
   - never hand-edit SVG output.
8. `plans/gallium-colstag-breaking-migration-plan.md`
   - keep as the durable breaking-migration record;
   - at final handoff change status to complete and record the commit, PR,
     build results, firmware artifact, flashed halves, and certification result.
     Do not leave unchecked or ambiguous follow-up items.

### Files intentionally untouched

- `build.yaml`
- `.github/workflows/build.yml`
- `CMakeLists.txt`
- `Kconfig`
- `config/corne.keymap`
- `config/corne.conf`
- `config/mouse.dtsi`
- `config/leader.dtsi`
- `config/prompts.dtsi`
- `config/west.yml`
- `draw/config.yaml`
- `src/behaviors/behavior_cancelable_text.c`
- `dts/bindings/**`
- `zephyr/module.yml`
- `firebase-debug.log` and every unrelated pre-existing worktree change

## Execution sequence and gates

### Phase 0: protect scope and establish the baseline

1. Fetch origin and confirm `gallium` is based on the then-current `origin/main`.
2. Record `git status --short`, current commit, and unrelated changes. Do not
   stage, edit, revert, or commit `firebase-debug.log` or other unrelated files.
3. Confirm the last `main` Build ZMK firmware run passes and exposes one
   non-expired `firmware` artifact containing both shields.
4. Save the pre-change commit SHA as the emergency Git-only recovery point; do
   not add a firmware layer, config flag, tag selector, or checked-in legacy
   artifact.

Exit gate: branch is current, baseline CI is green, and the exact allowed file
set is recorded.

### Phase 1: perform the atomic firmware cutover

1. Update layer 0, HRMs, and punctuation while retaining `DEF`, `Base`, and the
   Mouse return target.
2. Apply the complete combo specification, removals, and explicit mouse combo
   entry/exit positions.
3. Remove dead/legacy behaviors in the same patch.
4. Search the firmware tree for removed identifiers and reject any remaining
   definition or reference.
5. Review the whole effective keymap by physical position, not merely the diff.

Exit gate: firmware has one Base typing layer containing the exact Gallium
matrix, compiles syntactically through the preprocessor/parser path, and
contains none of the Required removals.

### Phase 2: update documentation and diagrams

1. From `/home/kirill/p/zmk-config/.zmk`, parse the finished
   `config/corne.keymap` with keymap-drawer 0.23.0 and `draw/config.yaml`.
   Compare the raw 13-layer result with the curated diagram sources; do not
   check the raw parse in or overwrite presentation annotations blindly.
2. Update `draw/keymap.yaml` and `draw/mouse-layer.yaml` from the exact firmware
   positions and the file map above.
3. Update `README.md` and `draw/README.md` from those same positions.
4. Regenerate the existing artifacts from the repository root:

   ```sh
   uvx --from keymap-drawer==0.23.0 keymap \
     -c draw/config.yaml draw draw/keymap.yaml -o keymap.svg

   uvx --from keymap-drawer==0.23.0 keymap \
     draw draw/mouse-layer.yaml \
     -s "Left Pointer" "Right Pointer" -o mouse-pointer.svg

   uvx --from keymap-drawer==0.23.0 keymap \
     draw draw/mouse-layer.yaml \
     -s "Left Scroll" "Right Scroll" -o mouse-scroll.svg
   ```

5. Inspect all three SVGs visually at full resolution and verify:

   - exact Gallium matrix and HRM holds;
   - prompt positions `V/G/Z`;
   - the four direct punctuation keys and their shifted legends;
   - visible Backspace/Delete combo dendrons at `Y+O` and `O+U`;
   - two-key parenthesis dendrons at Urob's original positions;
   - Base-facing Mouse labels and mirrored thumbs;
   - no overlaps, clipped legends, stale labels, or unexplained combo lines.

Exit gate: all diagrams are correct, legible, and reproducible.

### Phase 3: static and local build verification

1. Run `git diff --check`.
2. Use fixed-string searches for every removed identifier and stale phrase.
   Expected result is zero matches outside this plan's historical description.
3. Verify the Gallium cutover structurally:
   - `DEF`/`Base` is the sole typing layer at index 0;
   - the exact 30-key sequence matches the canonical matrix;
   - all 26 letters occur exactly once on Base;
   - direct comma, apostrophe, period, and question mark occupy the specified
     keys and their shifted forms are `; " : !`;
   - home-row holds are exactly `Gui Alt Shift Ctrl` / `Ctrl Shift Alt Gui`.
4. Verify combo uniqueness per active layer and ensure no combo includes a Mouse
   direction position on Mouse layers. Compare all 43 nodes with the complete
   combo specification and confirm that only `mouse_left`, `mouse`,
   `mouse_left_exit`, and `mouse_exit` changed positions.
5. Compare the fresh keymap-drawer parse with the curated YAML for every
   selected layer and combo. Presentation-only grouping, annotations, and
   hidden Nav variants are allowed; key positions and outputs may not differ.
6. Build both halves from the existing manifest-pinned workspace:

   ```sh
   cd /home/kirill/p/zmk-config/.zmk

   ./.venv/bin/west build -p always -s zmk/app \
     -d build-gallium-left -b 'nice_nano@2.0.0//zmk' -- \
     -DSHIELD=corne_left \
     -DZMK_CONFIG=/home/kirill/p/zmk-config-gallium/config \
     -DZMK_EXTRA_MODULES=/home/kirill/p/zmk-config-gallium

   ./.venv/bin/west build -p always -s zmk/app \
     -d build-gallium-right -b 'nice_nano@2.0.0//zmk' -- \
     -DSHIELD=corne_right \
     -DZMK_CONFIG=/home/kirill/p/zmk-config-gallium/config \
     -DZMK_EXTRA_MODULES=/home/kirill/p/zmk-config-gallium
   ```

7. Confirm both commands exit 0 and produce non-empty UF2 files.
8. Confirm build logs contain no devicetree, duplicate-node, behavior-cell,
   Kconfig, or deprecated-binding warning introduced by this change.

Exit gate: all static assertions and diagram comparisons pass, and both local
UF2 files are produced without new warnings.

### Phase 4: branch CI and artifact inspection

1. Review `git diff --stat` and `git diff`; confirm only allowed files changed.
2. Create one atomic breaking commit:

   `feat!: migrate Corne keymap to Gallium Colstag`

3. Push `gallium` and open a PR with:
   - the exact matrix;
   - breaking changes, moved combos, retained combos, and removed dead
     behaviors;
   - preserved behaviors;
   - static, diagram-parse, SVG inspection, and local-build results;
   - the physical certification checklist below.
4. Wait for the existing Build ZMK firmware workflow to complete successfully.
5. Download the `firmware` artifact and inspect the archive. It must contain one
   non-empty UF2 for `corne_left` and one for `corne_right`, both built from the
   PR head SHA.

Exit gate: PR tree is atomic, CI is green, and both deployable artifacts exist.

### Phase 5: flash and physical certification

1. Put the left half into the nice!nano bootloader and copy only the left UF2.
2. Wait for reboot and confirm it reconnects.
3. Put the right half into the bootloader and copy only the right UF2.
4. Power-cycle both halves and reconnect over the normal production transport.
5. Keep the host input source on standard US/QWERTY.
6. Execute every test in the certification matrix. Record pass/fail against the
   PR SHA and host/transport used.
7. If any test fails, repair it on `gallium`, rebuild both halves, reflash both
   halves, and rerun the entire matrix—not only the failed row.

Exit gate: every test passes on the physical split with artifacts from the
current PR head.

### Phase 6: merge, main verification, and cleanup

1. Confirm the PR tree has not changed since physical certification.
2. Merge the breaking commit to `main` without adding unrelated changes.
3. Wait for the `main` Build ZMK firmware workflow; confirm both shield jobs and
   artifact merge succeed.
4. Inspect the `main` firmware artifact and confirm both UF2 files exist.
5. Confirm the merged tree contains the same keymap/config/docs content that was
   physically certified.
6. Because this is a linked worktree and `firebase-debug.log` is a pre-existing
   user modification, preserve that file and the worktree: detach this
   worktree at the certified merged `origin/main` SHA, then delete the remote
   and local `gallium` branch. Do not force-remove the worktree or user change.
7. Confirm `origin/main` ships only Gallium. Do not alter unrelated branches.
   Confirm the worktree has no assistant-created leftovers, temporary outputs,
   old firmware archives, or stale generated files; the recorded pre-existing
   `firebase-debug.log` change may remain.

Exit gate: Gallium-only firmware is on `main`, CI is green, hardware is running
the certified tree, topic branches are removed, and cleanup is complete.

## Physical certification matrix

Every row is mandatory; there is no “follow up after using it for a while” gate.

### Gallium typing and punctuation

- Tap all 30 positions in physical order and compare with the canonical matrix.
- Type all lowercase letters and all uppercase letters.
- Verify the four direct pairs `, ;`, `' "`, `. :`, and `? !` with and without
  Shift.
- Verify `<` and `>` with Ctrl+Shift+comma/period.
- Verify `/ [ { ] } ( )` using the documented combo paths.
- Verify every vertical symbol combo: `@ # $ % grave backslash = ~ ^ + * & _ - / |`.
- Confirm the operating system is not applying another Gallium remap.

### Home-row modifiers and rapid typing

- Tap `N R T S H A E I` individually and in natural words.
- Hold every HRM and chord it with an opposite-hand letter.
- Verify same-hand rolls do not leak modifiers.
- After at least two seconds idle, repeatedly type:
  - `you your young out house have hand state start world right`;
  - `blue black try true art question minimum queue`;
  - `have hand happy aerial aesthetic` as explicit parenthesis near misses;
  - `bc abc art part start sort court yo ou you` as Mouse, Tab, Leader,
    Backspace, and Delete near misses;
  - punctuation-bearing samples `No,`, `why,`, `y,`, quoted text, and `a/b`.
- Confirm no word emits Escape, Tab, Leader, Mouse entry, parentheses, or an
  editing shortcut accidentally.
- Confirm no duplicate letters appear during ordinary taps or long holds.

### Control and editing combos

- Verify `L+D` Escape, `R+T` Tab, `T+S` Leader, and `R+T+S` Shift+Leader.
- Hold `R+T` with an opposite-hand letter and verify left Alt+left Shift;
  release it in both orders and confirm no stuck modifier.
- Verify `Q+W`, `Q+M`, and `M+W` perform Cut, Copy, and Paste.
- Tap `H+A` and `A+E` for `(` and `)`; add external Shift for `<` and `>`.
- Hold `H+A` with an opposite-hand letter and verify left Ctrl+right Shift;
  hold `A+E` and verify right Shift+left Alt. Release each chord in both orders
  and confirm no stuck modifier.
- Verify rolled/sequential `H+A` and `A+E` still type letters outside the combo
  timing window, including immediately after a long idle.
- On Nav, verify the same positions produce direct `<`, `>`, `{`, and `}` as
  in Urob.
- Verify `F+'` and `'+.` produce brackets, and Shift produces braces.
- Verify deliberate `Y+O` Backspace and `O+U` Delete in non-empty and empty
  fields; then verify normal `yo`, `ou`, and `you` rolls do not misfire.
- Verify all 28 German/Greek sequences through both Leader and Shift+Leader,
  plus USB/BLE, reset, and bootloader leader sequences;
  execute reset/bootloader only in a disposable test context and return the
  board to normal operation afterward.

### Layers and thumbs

- Space tap, Sentence shifted tap, and Nav hold.
- Enter tap and Fn hold.
- Smart Num Word, sticky Num double-tap, and momentary Num hold.
- Magic repeat, sticky Shift, Caps Word, held Shift, and Nav Cancel.
- Fn+Num conditional Sys activation.
- All Nav arrows, line/document jumps, deletion actions, page movement,
  window switching, Insert, Tab, Enter, and Cancel.
- Fn prompt positions `V/G/Z`, prompt output, mid-output cancellation, all
  function/media/desktop/display shortcuts.
- Num digits and modifier holds.
- Sys Bluetooth selectors, clear, bootloader, and reset on the intended half.

### Bilateral mouse

Test Mouse Left and Mouse Right independently:

- enter with `B+C` and `Y+,` respectively;
- confirm only the selected hand becomes Mouse and the other stays on Base;
- move up/left/down/right and scroll in all four directions;
- hold 4x and 1/4x in both Pointer and Scroll modes;
- use left/middle/right click on mirrored thumbs;
- one-shot, hold, lock, and unlock Ctrl and Shift;
- Copy/Paste and shifted terminal Copy/Paste;
- clipboard history and screen snip combos;
- timed forward and reverse Alt+Tab, including two-second timeout;
- page up/down and Escape;
- LMB lock, release through LMB, and release through Mouse exit;
- Pointer/Scroll toggle and return-to-Pointer behavior on re-entry;
- exit cleanup releases mouse buttons, Ctrl, Shift, and Alt;
- no direction key waits for a combo timeout.

Repeat the complete mouse section once over USB and once over BLE.

## Definition of done

The migration is finished only when all of the following are true:

- [x] `DEF`/`Base` is the sole typing layer and matches the exact Gallium
      Colstag matrix plus the four-key punctuation contract.
- [x] No runtime or documented Colemak path exists.
- [x] Dead behaviors and stale labels are removed; Urob's Backspace/Delete,
      parenthesis, and Nav symbol variants remain.
- [x] Only the Mouse entry/exit nodes use the explicitly approved new
      positions; Tab and every other combo preserve their pre-migration
      positions and behavior.
- [x] Static comparison proves all 43 combo nodes match the finished inventory.
- [ ] Smart, Magic, Nav, Fn, Num, Sys, leader, prompts, and both Mouse hands pass.
- [x] YAML and README files match firmware; all SVGs are regenerated with the
      existing documented keymap-drawer commands and pass visual inspection.
- [x] Static checks and both local firmware builds pass without new warnings.
- [x] PR CI passes and contains both UF2 artifacts.
- [ ] Both physical halves are flashed from the certified PR tree.
- [ ] Every physical certification test passes over required transports.
- [ ] The certified tree is merged to `main` and main CI/artifacts pass.
- [ ] The `gallium` branch and all migration-only temporary files are removed.
- [ ] The final handoff reports commit/PR, main CI URL, artifact names, flashed
      halves, certification evidence, and a direct `done` verdict.
