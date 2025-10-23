#ifndef SEVEN_SEGMENT_MAP_H
#define SEVEN_SEGMENT_MAP_H

/**
 * @brief A struct to hold the hardware-specific bitmasks for
 * 7 segments and a dot.
 */
struct SevenSegmentBitmaskMap {
    unsigned long segA;
    unsigned long segB;
    unsigned long segC;
    unsigned long segD;
    unsigned long segE;
    unsigned long segF;
    unsigned long segG;
    unsigned long segDot;
};

#endif // SEVEN_SEGMENT_MAP_H