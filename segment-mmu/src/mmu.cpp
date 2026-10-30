#include "segment.h"

TranslateResult translate(const SegmentTable& table, LogicalAddress addr) {
    TranslateResult kq;
    kq.ok = false;
    kq.physical = -1;

    int s = addr.segment;
    int d = addr.offset;

    kq.ok = true;
    kq.physical = table[s].base + d;
    return kq;
}
