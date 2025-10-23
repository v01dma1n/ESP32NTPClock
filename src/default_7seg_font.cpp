#include "default_7seg_font.h"
#include <cctype> // for toupper

// This is the VFD_FONT_MAP from , translated to generic 8-bit masks.
const uint8_t Default7SegFont::FONT_MAP[] = {
    0,                                                                // ' ' (space)
    0,                                                                // !
    GENERIC_SEG_F | GENERIC_SEG_B,                                    // "
    0, 0, 0, 0,                                                       // # $ % &
    GENERIC_SEG_A,                                                    // '
    0, 0, 0, 0, 0,                                                    // ( ) * + ,
    GENERIC_SEG_G,                                                    // -
    0,                                                                // . (handled by dot boolean)
    0,                                                                // /
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F, // 0 [cite: 85]
    GENERIC_SEG_B | GENERIC_SEG_C,                                    // 1
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_G | GENERIC_SEG_E | GENERIC_SEG_D, // 2 [cite: 86]
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_G | GENERIC_SEG_C | GENERIC_SEG_D, // 3 [cite: 87]
    GENERIC_SEG_F | GENERIC_SEG_G | GENERIC_SEG_B | GENERIC_SEG_C,    // 4 [cite: 88]
    GENERIC_SEG_A | GENERIC_SEG_F | GENERIC_SEG_G | GENERIC_SEG_C | GENERIC_SEG_D, // 5 [cite: 89]
    GENERIC_SEG_A | GENERIC_SEG_F | GENERIC_SEG_E | GENERIC_SEG_D | GENERIC_SEG_C | GENERIC_SEG_G, // 6 [cite: 90]
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C,                    // 7 [cite: 91]
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // 8 [cite: 92]
    GENERIC_SEG_A | GENERIC_SEG_F | GENERIC_SEG_G | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D, // 9 [cite: 93]
    0, 0, 0, 0, 0,                                                    // : ; < = >
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_G | GENERIC_SEG_E,    // ? [cite: 98]
    0,                                                                // @
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // A [cite: 100]
    GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // B (lowercase b) [cite: 101]
    GENERIC_SEG_A | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F,    // C [cite: 102]
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_G, // D (lowercase d) [cite: 103]
    GENERIC_SEG_A | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // E [cite: 104]
    GENERIC_SEG_A | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G,    // F [cite: 105]
    GENERIC_SEG_A | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F, // G [cite: 106]
    GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G,    // H (lowercase h) [cite: 107]
    GENERIC_SEG_E | GENERIC_SEG_F,                                    // I [cite: 108]
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E,    // J [cite: 109]
    0,                                                                // K
    GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F,                    // L [cite: 110]
    GENERIC_SEG_A | GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_G,    // M (n-like) [cite: 111]
    GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_G,                    // N (lowercase n) [cite: 112]
    GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_G,    // O (lowercase o) [cite: 113]
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // P [cite: 114]
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_F | GENERIC_SEG_G, // Q [cite: 115]
    GENERIC_SEG_E | GENERIC_SEG_G,                                    // R (lowercase r) [cite: 116]
    GENERIC_SEG_A | GENERIC_SEG_F | GENERIC_SEG_G | GENERIC_SEG_C | GENERIC_SEG_D, // S [cite: 117]
    GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G,    // T (lowercase t) [cite: 118]
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F, // U (lowercase u) [cite: 119]
    GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E,                    // V [cite: 120]
    GENERIC_SEG_A | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E,    // W [cite: 121]
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_F,    // X [cite: 122]
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_F | GENERIC_SEG_G, // Y [cite: 123]
    0                                                                 // Z
};

uint8_t Default7SegFont::getSegmentMask(char ascii_char) const {
    char c = toupper(ascii_char);
    if (c >= ' ' && c <= 'Z') {
        return FONT_MAP[c - ' '];
    }
    return 0; // Unknown char
}