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
        kq.error = "Loi: doan " + std::to_string(s) + " khong ton tai";
        return kq;
    }

    if (d < 0) {
        kq.error = "Loi: do doi am";
        return kq;
    }

    if (d >= table[s].limit) {
        kq.error = "Segmentation fault: do doi " + std::to_string(d) +
                   " vuot qua limit " + std::to_string(table[s].limit);
        return kq;
    }

    kq.ok = true;
    kq.physical = table[s].base + d;
    return kq;
}
