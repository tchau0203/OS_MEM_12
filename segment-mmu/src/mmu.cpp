#include "segment.h"
#include <sstream>
#include <iomanip>

/**
 * ============================================================================
 * Phân công: Người 3 phụ trách cài đặt MMU (Chuyển đổi địa chỉ Logic -> Vật lý)
 * ============================================================================
 */

void MMU::setSegmentTable(const SegmentTable* table) {
    segment_table = table;
}

TranslationResult MMU::translate(int segment_id, uint32_t offset) const {
    TranslationResult result;
    result.success = false;
    result.physical_addr = 0;

    // 1. Kiểm tra bảng phân đoạn đã được nạp vào MMU chưa
    if (!segment_table) {
        result.error_msg = "Loi MMU: Chua nap bang phan doan (Segment Table is null).";
        return result;
    }

    // 2. Tra cứu mục phân đoạn trong bảng phân đoạn
    auto segment_opt = segment_table->getSegment(segment_id);
    if (!segment_opt.has_value()) {
        std::ostringstream oss;
        oss << "Segmentation Fault: Phan doan s = " << segment_id << " khong ton tai trong bang.";
        result.error_msg = oss.str();
        return result;
    }

    const SegmentEntry& seg = segment_opt.value();

    // Kiểm tra cờ hợp lệ
    if (!seg.valid) {
        std::ostringstream oss;
        oss << "Segmentation Fault: Phan doan s = " << segment_id << " dang o trang thai Invalid.";
        result.error_msg = oss.str();
        return result;
    }

    // 3. Kiểm tra vi phạm giới hạn: offset phai nho hon limit (offset < limit)
    if (offset >= seg.limit) {
        std::ostringstream oss;
        oss << "Trap/Limit Violation: Offset d = " << offset 
            << " vuot qua gioi han Limit = " << seg.limit 
            << " cua phan doan " << segment_id << " (" << seg.name << ").";
        result.error_msg = oss.str();
        return result;
    }

    // 4. Tinh toan dia chi vat ly: Physical Address = Base + Offset
    result.physical_addr = seg.base + offset;
    result.success = true;
    result.error_msg = "";
    return result;
}

TranslationResult MMU::translate(const LogicalAddress& logical_addr) const {
    return translate(logical_addr.segment_id, logical_addr.offset);
}
