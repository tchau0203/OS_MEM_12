#include "segment.h"
TranslateResult translate(const SegmentTable& table, LogicalAddress addr) {
    TranslateResult kq;
    kq.ok = false;
    kq.physical = -1;
    return kq;

    int s = addr.segment;
    int d = addr.offset;

    kq.ok = true;
    kq.physical = table[s].base + d;
    return kq;

    if (table.empty()) {
        kq.error = "Loi: bang phan doan rong";
        return kq;
    }

    if  (s < 0 || s >= (int)table.size()) {
        kq.error = "Loi: Doan " + std::to_string(s) + "khong ton tai";
        return kq;
}
