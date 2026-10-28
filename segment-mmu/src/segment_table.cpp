#include "segment.h"
#include <iomanip>
#include <iostream>

/**
 * ============================================================================
 * Phân công: Người 2 phụ trách cài đặt Segment Table (Bảng phân đoạn)
 * ============================================================================
 */

void SegmentTable::addSegment(int segment_id, uint32_t base, uint32_t limit, const std::string& name) {
    // Nếu segment_id đã tồn tại, cập nhật lại thông tin
    for (auto& entry : entries) {
        if (entry.segment_id == segment_id) {
            entry.base = base;
            entry.limit = limit;
            entry.valid = true;
            if (!name.empty()) {
                entry.name = name;
            }
            return;
        }
    }
    // Nếu chưa tồn tại, thêm mới
    entries.emplace_back(segment_id, base, limit, true, name);
}

std::optional<SegmentEntry> SegmentTable::getSegment(int segment_id) const {
    for (const auto& entry : entries) {
        if (entry.segment_id == segment_id) {
            return entry;
        }
    }
    return std::nullopt;
}

bool SegmentTable::isValidSegment(int segment_id) const {
    for (const auto& entry : entries) {
        if (entry.segment_id == segment_id) {
            return entry.valid;
        }
    }
    return false;
}

const std::vector<SegmentEntry>& SegmentTable::getAllSegments() const {
    return entries;
}

void SegmentTable::displayTable() const {
    std::cout << "\n+------------+----------------------+------------+------------+---------+\n";
    std::cout << "| Segment ID | Ten phan doan        | Base (Hex) | Limit (Dec)| Trang thai|\n";
    std::cout << "+------------+----------------------+------------+------------+---------+\n";

    if (entries.empty()) {
        std::cout << "|                         Bang phan doan trong!                         |\n";
        std::cout << "+------------+----------------------+------------+------------+---------+\n";
        return;
    }

    for (const auto& entry : entries) {
        std::cout << "| " << std::setw(10) << entry.segment_id
                  << " | " << std::setw(20) << std::left << (entry.name.empty() ? "(Khong ten)" : entry.name) << std::right
                  << " | 0x" << std::setw(8) << std::setfill('0') << std::hex << entry.base << std::dec << std::setfill(' ')
                  << " | " << std::setw(10) << entry.limit
                  << " | " << std::setw(7) << (entry.valid ? "Valid" : "Invalid")
                  << " |\n";
    }
    std::cout << "+------------+----------------------+------------+------------+---------+\n";
}

void SegmentTable::clear() {
    entries.clear();
}
