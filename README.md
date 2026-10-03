# au_ttfparser

## About

The goal of this project is to parse files with the `.ttf` extension.

This is not intended to be a full, general-purpose parser. Only the parts needed for the `au_fontrendering` project are implemented. As such, the primary focus is on glyph data.

The aim is to expose glyph data equivalent to what FreeType provides, and, where useful, to pre-compute additional data to simplify downstream use of the glyphs.

## Roadmap

Bitmap parsing is out of scope for now.
