# Gallium-left Surfingkeys profile

[`gallium-left.js`](gallium-left.js) is the canonical Surfingkeys settings
block for navigating with the left Gallium half while Mouse Right controls the
pointer. It changes Surfingkeys only; it does not require a firmware change.

## Install

1. In Surfingkeys Normal mode, press `yj` and save the copied settings as a
   rollback snapshot.
2. Press `;e` to open the Surfingkeys settings editor.
3. Add the complete contents of [`gallium-left.js`](gallium-left.js). If the
   editor contains generated example settings that you do not use, replace
   them with this file; if it contains intentional custom settings, append
   this file instead.
4. Run `:w` in the settings editor to save.
5. Open an ordinary web page and press `?`. Confirm that the help contains the
   `Gallium:` mappings before testing with Mouse Right.

Surfingkeys documents `;e` / `:w` as its settings edit/save path and `api.map`
as the Normal-mode alias API:

- <https://github.com/brookhong/Surfingkeys#edit-settings>
- <https://github.com/brookhong/Surfingkeys/blob/master/docs/API.md#map>

## Usage

Enter Mouse Right with `Y+,` on Gallium. The right half becomes the pointer;
the transparent left half stays on Gallium. Tap the outer-left Backspace thumb,
then tap one of these keys:

```text
background link   choose tab   scroll up    click link    page up
       B               L           D             C           V

active-new link   scroll left  scroll down  scroll right  page down
       N               R           T             S           G

history back      find page    restore tab       -        history forward
       X               Q           M             W           Z
```

The executable mapping contract is:

| Input | Action | Surfingkeys source mapping |
| --- | --- | --- |
| `Bspc B` | Open hinted link in a background tab | `gf` |
| `Bspc L` | Choose a tab | `T` |
| `Bspc D` | Scroll up | `k` |
| `Bspc C` | Open a hinted link | `f` |
| `Bspc V` | Scroll half a page up | `e` |
| `Bspc N` | Open hinted link in an active new tab | `af` |
| `Bspc R` | Scroll left | `h` |
| `Bspc T` | Scroll down | `j` |
| `Bspc S` | Scroll right | `l` |
| `Bspc G` | Scroll half a page down | `d` |
| `Bspc X` | Go back in page history | `S` |
| `Bspc Q` | Find in the current page | `/` |
| `Bspc M` | Restore the last closed tab | `X` |
| `Bspc Z` | Go forward in page history | `D` |

`W` intentionally has no leader action. Plain Gallium `w` retains
Surfingkeys' existing Switch Frames command. Other useful unmodified left-half
commands include `b` for bookmarks, `t` for URL/history search, `v` for Visual
mode, `n` for the next search match, `r` for reload, `x` for close tab, `q` for
image/button hints, and `m` for marks.

## Hint alphabet

The profile uses:

```text
nrtsg bldcv xqmwz
```

This is the complete Gallium left half ordered like Surfingkeys' default hint
alphabet: home row first, then top row, then bottom row. Every displayed hint
can therefore be entered without leaving the left keyboard.

The hint alphabet is deliberately Gallium-specific. If QWERTY becomes the
regular browsing base, revise the profile rather than adding a second runtime
path.

## Behavioral boundaries

- The Backspace leader is active only in Surfingkeys Normal mode. In Insert
  mode, Backspace and every letter continue to type normally.
- The profile adds aliases instead of remapping all 15 letters, so existing
  single-letter and multi-letter Surfingkeys commands remain available.
- The profile does not change Visual-mode cursor bindings. Add Visual-mode
  aliases only if actual use shows they are needed.
- Surfingkeys can be disabled or placed in PassThrough mode on sites that own
  the same keystrokes.

## Smoke test

Run this on a normal page with several links and enough content to scroll:

1. With Mouse Right off, confirm `Bspc C` displays only labels composed from
   `nrtsgbldcvxqmwz`; activate one label.
2. Confirm `Bspc D/T` scroll up/down and `Bspc V/G` page up/down.
3. Confirm `Bspc L` opens the tab chooser and its hint labels remain left-hand
   typeable.
4. Confirm `Bspc Q` opens find, typing works normally in the find field, and
   `n` advances to the next match.
5. Enter Mouse Right, repeat steps 1-4, and use the right half for pointer and
   clicks throughout.
6. Click a text field while Mouse Right remains active. Confirm Gallium letters
   and Backspace work normally and no leader command fires.
7. Exit Mouse Right and confirm the selected alpha base has not changed.

If any step fails, restore the `yj` snapshot before changing mappings. Do not
change the ZMK Mouse layer to compensate for a Surfingkeys-mode or alias issue.
