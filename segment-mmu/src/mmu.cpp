#include "segment.h"

TranslateResult translate(const SegmentTable& table, LogicalAddress addr) {
    TranslateResult kq;
    kq.ok = false;
    kq.physical = -1;

    int s = addr.segment;
    int d = addr.offset;

    if (table.empty()) {
        kq.error = "Loi: bang phan doan rong";
        return kq;
    }

    if (s < 0 || s >= (int)table.size()) {
    kq.error = "Loi: doan " + std::to_string(s) +
               " khong ton tai";
    return kq;
    }

    return kq;
}

