#include "segment.h"
#include <cassert>
#include <iostream>

/**
 * ============================================================================
 * Phân công: Người 5 phụ trách viết bộ kiểm thử tự động (Unit Tests)
 * ============================================================================
 */

void test_valid_translation() {
    SegmentTable table;
    table.addSegment(0, 219, 600, "Segment 0");
    table.addSegment(2, 90, 100, "Segment 2");

    MMU mmu(&table);

    // Case 1: Dịch hợp lệ segment 0, offset 100 -> physical = 219 + 100 = 319
    auto res1 = mmu.translate(0, 100);
    assert(res1.success == true);
    assert(res1.physical_addr == 319);

    // Case 2: Dịch hợp lệ segment 2, offset 0 -> physical = 90 + 0 = 90
    auto res2 = mmu.translate(2, 0);
    assert(res2.success == true);
    assert(res2.physical_addr == 90);

    // Case 3: Dịch hợp lệ ở biên cuối (limit - 1): segment 2, offset 99 -> 90 + 99 = 189
    auto res3 = mmu.translate(2, 99);
    assert(res3.success == true);
    assert(res3.physical_addr == 189);

    std::cout << "[PASS] test_valid_translation thanh cong!\n";
}

void test_limit_violation() {
    SegmentTable table;
    table.addSegment(1, 2300, 14, "Segment 1");

    MMU mmu(&table);

    // Case 1: Offset = Limit (14 >= 14) -> Phải báo lỗi Limit Violation
    auto res1 = mmu.translate(1, 14);
    assert(res1.success == false);

    // Case 2: Offset > Limit (100 > 14) -> Phải báo lỗi Limit Violation
    auto res2 = mmu.translate(1, 100);
    assert(res2.success == false);

    std::cout << "[PASS] test_limit_violation thanh cong!\n";
}

void test_non_existent_segment() {
    SegmentTable table;
    table.addSegment(0, 1000, 500);

    MMU mmu(&table);

    // Segment 5 không tồn tại -> Segmentation fault
    auto res = mmu.translate(5, 50);
    assert(res.success == false);

    std::cout << "[PASS] test_non_existent_segment thanh cong!\n";
}

void test_update_segment() {
    SegmentTable table;
    table.addSegment(1, 100, 200, "Old");
    table.addSegment(1, 500, 300, "Updated");

    MMU mmu(&table);
    auto res = mmu.translate(1, 50);
    assert(res.success == true);
    assert(res.physical_addr == 550);

    std::cout << "[PASS] test_update_segment thanh cong!\n";
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "         CHAY CAC TEST CASE MMU            \n";
    std::cout << "===========================================\n";

    test_valid_translation();
    test_limit_violation();
    test_non_existent_segment();
    test_update_segment();

    std::cout << "\n>>> TAT CA CAC TEST DA VUOT QUA THANH CONG! <<<\n";
    return 0;
}
