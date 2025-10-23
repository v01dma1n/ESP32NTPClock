#ifndef I_FONT_H
#define I_FONT_H
#include <cstdint>

// Define the generic 7-segment mask: 0b(dot)gfedcba
#define GENERIC_SEG_A 0b00000001
#define GENERIC_SEG_B 0b00000010
#define GENERIC_SEG_C 0b00000100
#define GENERIC_SEG_D 0b00001000
#define GENERIC_SEG_E 0b00010000
#define GENERIC_SEG_F 0b00100000
#define GENERIC_SEG_G 0b01000000
#define GENERIC_SEG_DOT 0b10000000

class IFont {
public:
    virtual ~IFont() {}
    
    /**
     * @brief Gets the generic 8-bit segment mask for a character.
     * @param c The ASCII character.
     * @return An 8-bit mask (0b(dot)gfedcba).
     */
    virtual uint8_t getSegmentMask(char c) const = 0;
};

#endif // I_FONT_H