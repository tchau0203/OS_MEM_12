#ifndef SEGMENT_H
#define SEGMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <stdexcept>
#include <cstdint>

/**
 * ============================================================================
 * Phân công: Người 1 phụ trách thiết kế cấu trúc dữ liệu và giao diện (Header)
 * ============================================================================
 */

// Cấu trúc đại diện cho một phân đoạn trong bảng phân đoạn
struct SegmentEntry {
    int segment_id;          // Mã định danh phân đoạn (Segment Number - s)
    uint32_t base;           // Địa chỉ cơ sở vật lý (Base address)
    uint32_t limit;          // Độ dài/giới hạn của phân đoạn (Limit/Length)
    bool valid;              // Cờ trạng thái hợp lệ (Valid/Invalid bit)
    std::string name;        // Tên phân đoạn (Code, Data, Stack, Heap,...)

    SegmentEntry(int id = 0, uint32_t b = 0, uint32_t lim = 0, bool v = true, const std::string& n = "")
        : segment_id(id), base(b), limit(lim), valid(v), name(n) {}
};

// Cấu trúc địa chỉ logic (Logical / Virtual Address)
struct LogicalAddress {
    int segment_id;          // Chỉ số phân đoạn (s)
    uint32_t offset;         // Độ lệch trong phân đoạn (d)
};

// Kết quả chuyển đổi địa chỉ từ MMU
struct TranslationResult {
    bool success;            // Dịch thành công hay thất bại
    uint32_t physical_addr;  // Địa chỉ vật lý sau khi chuyển đổi
    std::string error_msg;   // Thông báo lỗi nếu thất bại
};

// Lớp quản lý bảng phân đoạn (Segment Table) - Cài đặt chi tiết: Người 2
class SegmentTable {
private:
    std::vector<SegmentEntry> entries;

public:
    SegmentTable() = default;

    // Thêm hoặc cập nhật một mục trong bảng phân đoạn
    void addSegment(int segment_id, uint32_t base, uint32_t limit, const std::string& name = "");
    
    // Lấy thông tin một phân đoạn theo ID
    std::optional<SegmentEntry> getSegment(int segment_id) const;

    // Kiểm tra phân đoạn có tồn tại và hợp lệ không
    bool isValidSegment(int segment_id) const;

    // Lấy toàn bộ danh sách phân đoạn
    const std::vector<SegmentEntry>& getAllSegments() const;

    // In bảng phân đoạn ra màn hình
    void displayTable() const;

    // Xóa bảng phân đoạn
    void clear();
};

// Lớp đơn vị quản lý bộ nhớ (Memory Management Unit - MMU) - Cài đặt chi tiết: Người 3
class MMU {
private:
    const SegmentTable* segment_table;

public:
    explicit MMU(const SegmentTable* table = nullptr) : segment_table(table) {}

    // Gán bảng phân đoạn cho MMU
    void setSegmentTable(const SegmentTable* table);

    // Chuyển đổi địa chỉ logic (segment_id, offset) -> địa chỉ vật lý
    TranslationResult translate(int segment_id, uint32_t offset) const;
    TranslationResult translate(const LogicalAddress& logical_addr) const;
};

#endif // SEGMENT_H
