#!/usr/bin/env bash

set -euo pipefail

repo_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
overview_yaml="$(mktemp --suffix=.yaml /tmp/zmk-overview.XXXXXX)"

cleanup() {
    rm -f -- "$overview_yaml"
}
trap cleanup EXIT

cd "$repo_root"

uvx --from keymap-drawer==0.23.0 keymap \
    -c draw/config.yaml draw draw/keymap.yaml -o keymap.svg

jq_expr='
    def extract_label:
        if type == "string" then . else .t end;

    def is_transparent:
        type == "object" and (.type == "trans" or .type == "held");

    def compact_label:
        if . == "Brightness ↑" then "Bri↑"
        elif . == "Brightness ↓" then "Bri↓"
        else .
        end;

    def overlay_label($binding; $base_label):
        if ($binding | is_transparent) then null
        else ($binding | extract_label | compact_label) as $label
        | if $label == $base_label then null else $label end
        end;

    .layers = {
        Base: [
            [.layers.Base, .layers.Nav, .layers.Fn, .layers.Num, .layers.Sys]
            | transpose[]
            | (.[0] | if type == "string" then {t: .} else . end) as $base
            | ($base | extract_label | compact_label) as $base_label
            | overlay_label(.[1]; $base_label) as $nav
            | overlay_label(.[2]; $base_label) as $fn
            | overlay_label(.[3]; $base_label) as $num
            | overlay_label(.[4]; $base_label) as $sys
            | $base
                + (if $nav == null then {} else {tr: $nav} end)
                + (if $fn == null then {} else {tl: $fn} end)
                + (if $num == null then {} else {bl: $num} end)
                + (if $sys == null then {} else {br: $sys} end)
        ],
        Combos: .layers.Combos,
        "Right Pointer": .layers["Mouse Right"]
    }
    | .combos = [.combos[] | .l = ["Combos"]]
'

uvx --from yq==3.4.3 yq -y "$jq_expr" draw/keymap.yaml > "$overview_yaml"
uvx --from keymap-drawer==0.23.0 keymap \
    -c draw/config.yaml draw "$overview_yaml" -o overview.svg

uvx --from keymap-drawer==0.23.0 keymap \
    draw draw/mouse-layer.yaml \
    -s "Left Pointer" "Right Pointer" \
    -o mouse-pointer.svg

uvx --from keymap-drawer==0.23.0 keymap \
    draw draw/mouse-layer.yaml \
    -s "Left Scroll" "Right Scroll" \
    -o mouse-scroll.svg

printf 'Generated overview.svg, keymap.svg, mouse-pointer.svg, and mouse-scroll.svg\n'
