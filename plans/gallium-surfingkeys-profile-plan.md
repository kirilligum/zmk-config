# Gallium-left Surfingkeys profile specification and rollout plan

Status: profile authored and statically validated; browser acceptance pending

Target hardware state: Gallium selected, Mouse Right active, left half free

Executable profile: [`../surfingkeys/gallium-left.js`](../surfingkeys/gallium-left.js)

Surfingkeys reference inspected: `brookhong/Surfingkeys` `master` at
`235c607cf236c5c233efe773e3ad5ec95c654f5b`

## Decision

Own browser navigation in Surfingkeys, not in the ZMK Mouse layer. Mouse Right
must continue to affect only the right hand; its transparent left bindings
must continue to expose the selected alpha base.

The Gallium profile uses tap-then-tap `Backspace` sequences. It does not
translate the whole Gallium alphabet into QWERTY and does not replace any
existing one-key Surfingkeys mapping. The profile is one settings block and has
no firmware fallback or parallel legacy mapping.

## Inputs and outputs

### Inputs

- Gallium left matrix:
  `B L D C V / N R T S G / X Q M W Z`.
- Outer-left thumb: Backspace.
- Mouse Right contract: the left matrix and left thumbs are transparent to the
  selected alpha base.
- Existing Mouse geometry: `D R T S` is up/left/down/right and `V G` is page
  up/down.
- Surfingkeys Normal-mode source mappings: `f`, `af`, `gf`, `h/j/k/l`, `e/d`,
  `T`, `S/D`, `X`, and `/`.
- Surfingkeys Hints API: `api.Hints.setCharacters(...)`.

### Outputs

- One pasteable Surfingkeys profile at
  [`surfingkeys/gallium-left.js`](../surfingkeys/gallium-left.js).
- One setup, usage, rollback, and smoke-test guide at
  [`surfingkeys/README.md`](../surfingkeys/README.md).
- No changes to ZMK bindings, layer transitions, diagrams, or firmware.

## Required behavior

### Invariants

1. Mouse Right continues to preserve Gallium on the left half.
2. Surfingkeys owns all browser-command aliases.
3. Normal-mode aliases use `Backspace` as a tap-then-tap leader.
4. Insert mode receives unchanged Backspace and Gallium letters.
5. Existing Surfingkeys commands remain installed; the profile uses aliases,
   not `unmap`, one-key overrides, or an alphabet translation.
6. Direction and page commands reuse the Mouse Left physical geometry.
7. All hint labels use only the 15 Gallium left-half letters.
8. QWERTY-specific optimization, Visual-mode remapping, and site-specific
   mappings remain out of scope until observed use justifies them.

### Command surface

| Gallium position | Input | Required action | Upstream mapping |
| --- | --- | --- | --- |
| `LT4` | `Bspc B` | Open hinted link in background | `gf` |
| `LT3` | `Bspc L` | Choose tab | `T` |
| `LT2` | `Bspc D` | Scroll up | `k` |
| `LT1` | `Bspc C` | Open hinted link | `f` |
| `LT0` | `Bspc V` | Scroll half page up | `e` |
| `LM4` | `Bspc N` | Open hinted link in active new tab | `af` |
| `LM3` | `Bspc R` | Scroll left | `h` |
| `LM2` | `Bspc T` | Scroll down | `j` |
| `LM1` | `Bspc S` | Scroll right | `l` |
| `LM0` | `Bspc G` | Scroll half page down | `d` |
| `LB4` | `Bspc X` | Back in page history | `S` |
| `LB3` | `Bspc Q` | Find in current page | `/` |
| `LB2` | `Bspc M` | Restore closed tab | `X` |
| `LB1` | `Bspc W` | Unassigned; preserve plain `w` | none |
| `LB0` | `Bspc Z` | Forward in page history | `D` |

### Hint contract

`api.Hints.setCharacters("nrtsgbldcvxqmwz")` is exact:

| Priority | QWERTY-default physical row | Gallium output |
| --- | --- | --- |
| 1 | `A S D F G` | `N R T S G` |
| 2 | `Q W E R T` | `B L D C V` |
| 3 | `Z X C V B` | `X Q M W Z` |

The order favors the Gallium home row while keeping every hint enterable with
the free left half.

## Rollout

### Phase 1 — install

1. Copy the current Surfingkeys settings with `yj` and save the snapshot.
2. Open the settings editor with `;e`.
3. Install the exact contents of `surfingkeys/gallium-left.js`.
4. Save with `:w`.
5. Open `?` and confirm the annotated `Gallium:` aliases are present.

Exit criterion: settings save without a JavaScript error and help lists the
new aliases.

### Phase 2 — browser-only certification

Run `SK-001` through `SK-006` below before involving the Mouse layer.

Exit criterion: every alias calls the intended existing Surfingkeys action;
all hint labels are left-hand typeable; ordinary input is unchanged.

### Phase 3 — real one-handed path

Enter Mouse Right from Gallium and run `SK-007` through `SK-010` while keeping
the right hand on pointer/click controls.

Exit criterion: link, scroll, page, tab, history, restore, and find operations
work from the left half; pointer behavior and alpha-base preservation remain
unchanged.

### Phase 4 — usage review

Use the profile without further expansion for several browsing sessions. Record
only repeatable friction: an unavailable action, an uncomfortable sequence, a
site conflict, or accidental leader activation.

Exit criterion: either accept the profile unchanged or make one evidence-based
revision. Do not add a full alphabet translation or duplicate firmware path.

## Acceptance tests

| ID | Setup | Action | Expected output |
| --- | --- | --- | --- |
| `SK-001` | Normal page | `Bspc C`, then a shown hint | Current-tab link opens |
| `SK-002` | Normal page | `Bspc N/B`, then a hint | Active/background new-tab behavior matches the command |
| `SK-003` | Scrollable page | `Bspc D/R/T/S` | Page scrolls up/left/down/right |
| `SK-004` | Scrollable page | `Bspc V/G` | Page scrolls half-page up/down |
| `SK-005` | Multiple tabs and history | `Bspc L/X/Z/M` | Chooser/back/forward/restore actions are exact |
| `SK-006` | Page with repeated text | `Bspc Q`, type, Enter, `n` | Find opens and advances normally |
| `SK-007` | Gallium + Mouse Right | repeat `SK-001`–`SK-006` | All commands work from the transparent left half |
| `SK-008` | Mouse Right + text input | type Gallium and use Backspace | Text and deletion are unchanged; no Normal alias fires |
| `SK-009` | Mouse Right | move, scroll, click, copy/paste, exit | Existing right-pointer contract is unchanged |
| `SK-010` | After Mouse Right exit | type and inspect selected base | Gallium remains selected |

## Verification before declaring complete

- `node --check surfingkeys/gallium-left.js` passes.
- A mock-API evaluation records one 15-character hint alphabet and exactly 14
  unique `api.map` aliases.
- Every alias target exists in the inspected upstream Surfingkeys default
  mappings.
- `git diff --check` passes.
- `SK-001` through `SK-010` pass in the actual browser. Static checks alone do
  not complete the rollout.

## Rollback

Restore the settings snapshot captured with `yj`, or remove the complete
contents of `surfingkeys/gallium-left.js` from the settings editor and save with
`:w`. No firmware rollback or reflash is involved.
