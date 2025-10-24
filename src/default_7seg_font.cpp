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
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F, // 0 
    GENERIC_SEG_B | GENERIC_SEG_C,                                    // 1
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_G | GENERIC_SEG_E | GENERIC_SEG_D, // 2 
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_G | GENERIC_SEG_C | GENERIC_SEG_D, // 3 
    GENERIC_SEG_F | GENERIC_SEG_G | GENERIC_SEG_B | GENERIC_SEG_C,    // 4 
    GENERIC_SEG_A | GENERIC_SEG_F | GENERIC_SEG_G | GENERIC_SEG_C | GENERIC_SEG_D, // 5 
    GENERIC_SEG_A | GENERIC_SEG_F | GENERIC_SEG_E | GENERIC_SEG_D | GENERIC_SEG_C | GENERIC_SEG_G, // 6 
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C,                    // 7 
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // 8 
    GENERIC_SEG_A | GENERIC_SEG_F | GENERIC_SEG_G | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D, // 9 
    0, 0, 0, 0, 0,                                                    // : ; < = >
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_G | GENERIC_SEG_E,    // ? 
    0,                                                                // @
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // A 
    GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // B (lowercase b) 
    GENERIC_SEG_A | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F,    // C 
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_G, // D (lowercase d) 
    GENERIC_SEG_A | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // E 
    GENERIC_SEG_A | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G,    // F 
    GENERIC_SEG_A | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F, // G 
    GENERIC_SEG_B |GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G,    // H 
    GENERIC_SEG_E | GENERIC_SEG_F,                                    // I 
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E,    // J 
    GENERIC_SEG_B | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G,    // K
    GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F,                    // L 
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_F, // M (N-like) 
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_F,                    // N
     GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F,  // O 
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G, // P 
    GENERIC_SEG_A | GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_F | GENERIC_SEG_G, // Q 
    GENERIC_SEG_E | GENERIC_SEG_G,                                    // R (lowercase r) 
    GENERIC_SEG_A | GENERIC_SEG_F | GENERIC_SEG_G | GENERIC_SEG_C | GENERIC_SEG_D, // S 
    GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F | GENERIC_SEG_G,    // T (lowercase t) 
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E | GENERIC_SEG_F, // U 
    GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E,                    // V 
    GENERIC_SEG_A | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_E,    // W 
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_E | GENERIC_SEG_F,    // X 
    GENERIC_SEG_B | GENERIC_SEG_C | GENERIC_SEG_D | GENERIC_SEG_F | GENERIC_SEG_G, // Y 
    0                                                                 // Z
};

uint8_t Default7SegFont::getSegmentMask(char ascii_char) const {
    char c = toupper(ascii_char);
    if (c >= ' ' && c <= 'Z') {
        return FONT_MAP[c - ' '];
    }
    return 0; // Unknown char
}