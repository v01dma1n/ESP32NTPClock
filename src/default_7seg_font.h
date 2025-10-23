#ifndef DEFAULT_7SEG_FONT_H
#define DEFAULT_7SEG_FONT_H

#include "i_font.h"

class Default7SegFont : public IFont {
public:
    Default7SegFont() {}
    virtual uint8_t getSegmentMask(char c) const override;
private:
    static const uint8_t FONT_MAP[];
};
#endif // DEFAULT_7SEG_FONT_H