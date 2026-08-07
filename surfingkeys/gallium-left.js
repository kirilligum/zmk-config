// Gallium-left Surfingkeys profile for use while Mouse Right is active.
// Paste this entire file into the Surfingkeys settings editor.

// Preserve the default hint priority by row: home, top, then bottom.
api.Hints.setCharacters("nrtsgbldcvxqmwz");

// Backspace is the command leader in Surfingkeys Normal mode. These aliases do
// not change Insert mode, so Backspace and Gallium typing remain ordinary in
// text fields.

// Link and tab navigation.
api.map(
  "<Backspace>b",
  "gf",
  null,
  "#1Gallium: open hinted link in a background tab",
);
api.map("<Backspace>l", "T", null, "#3Gallium: choose a tab");
api.map("<Backspace>c", "f", null, "#1Gallium: open a hinted link");
api.map(
  "<Backspace>n",
  "af",
  null,
  "#1Gallium: open hinted link in an active new tab",
);

// Scrolling. D/R/T/S matches the Mouse Left up/left/down/right geometry;
// V/G matches its page-up/page-down geometry.
api.map("<Backspace>d", "k", null, "#2Gallium: scroll up");
api.map("<Backspace>r", "h", null, "#2Gallium: scroll left");
api.map("<Backspace>t", "j", null, "#2Gallium: scroll down");
api.map("<Backspace>s", "l", null, "#2Gallium: scroll right");
api.map("<Backspace>v", "e", null, "#2Gallium: scroll half page up");
api.map("<Backspace>g", "d", null, "#2Gallium: scroll half page down");

// Page and tab history.
api.map("<Backspace>x", "S", null, "#4Gallium: go back in page history");
api.map("<Backspace>z", "D", null, "#4Gallium: go forward in page history");
api.map("<Backspace>m", "X", null, "#3Gallium: restore closed tab");

// Search the current page. n/N remains Surfingkeys' next/previous match after
// the search completes.
api.map("<Backspace>q", "/", null, "#9Gallium: find in current page");
