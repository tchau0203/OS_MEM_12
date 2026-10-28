#include "segment.h"
#include <iostream>
#include <iomanip>
#include <limits>

/**
 * ============================================================================
 * Phan cong: BAN phu trach giao dien chinh va luong chay chuong trinh (Main CLI)
 * ============================================================================
 */

void loadSampleData(SegmentTable& table) {
    table.clear();
    // Bang mau kinh dien trong giao trinh He Dieu Hanh
    table.addSegment(0, 219, 600, "Phan doan 0 (Subroutine)");
    table.addSegment(1, 2300, 14, "Phan doan 1 (Square root)");
    table.addSegment(2, 90, 100, "Phan doan 2 (Main program)");
    table.addSegment(3, 1327, 580, "Phan doan 3 (Stack)");
    table.addSegment(4, 1952, 96, "Phan doan 4 (Data/Symbol)");
    std::cout << ">> Da nap du lieu mau thanh cong!\n";
}

void printMenu() {
    std::cout << "\n============================================\n";
    std::cout << "   MO PHONG PHAN DOAN BO NHO (SEGMENT MMU)  \n";
    std::cout << "============================================\n";
    std::cout << "1. Xem bang phan doan (Segment Table)\n";
    std::cout << "2. Dich dia chi logic <s, d> sang dia chi vat ly\n";
    std::cout << "3. Them / Cap nhat phan doan moi\n";
    std::cout << "4. Nap du lieu mau (Sample Data)\n";
    std::cout << "5. Xoa toan bo bang phan doan\n";
    std::cout << "0. Thoat chuong trinh\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "Lua chon cua ban: ";
}

int main() {
    SegmentTable table;
    MMU mmu(&table);

    // Mac dinh nap du lieu mau de tien chay thu nghiem
    loadSampleData(table);

    int choice = -1;
    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << ">> Lua chon khong hop le! Vui long nhap so.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "\n>> Tam biet! Ket thuc chuong trinh.\n";
            break;
        }

        switch (choice) {
            case 1: {
                table.displayTable();
                break;
            }
            case 2: {
                int seg_id;
                uint32_t offset;
                std::cout << "\n--- CHUYEN DOI DIA CHI LOGIC --- \n";
                std::cout << "Nhap Segment ID (s): ";
                std::cin >> seg_id;
                std::cout << "Nhap Offset (d): ";
                std::cin >> offset;

                TranslationResult result = mmu.translate(seg_id, offset);
                std::cout << "\n[KET QUA MMU]:\n";
                if (result.success) {
                    std::cout << "  - Trang thai: HOP LE (VALID)\n";
                    std::cout << "  - Dia chi logic: <s=" << seg_id << ", d=" << offset << ">\n";
                    std::cout << "  - Dia chi vat ly (Dec): " << result.physical_addr << "\n";
                    std::cout << "  - Dia chi vat ly (Hex): 0x" << std::hex << std::uppercase 
                              << result.physical_addr << std::dec << "\n";
                } else {
                    std::cout << "  - Trang thai: BI LOI (FAULT / TRAP)\n";
                    std::cout << "  - Thong bao: " << result.error_msg << "\n";
                }
                break;
            }
            case 3: {
                int seg_id;
                uint32_t base, limit;
                std::string name;
                std::cout << "\n--- THEM / CAP NHAT PHAN DOAN ---\n";
                std::cout << "Nhap Segment ID: ";
                std::cin >> seg_id;
                std::cout << "Nhap Base address (Decimal): ";
                std::cin >> base;
                std::cout << "Nhap Limit (Decimal): ";
                std::cin >> limit;
                std::cin.ignore();
                std::cout << "Nhap ten phan doan (vi du: Code, Data, Stack...): ";
                std::getline(std::cin, name);

                table.addSegment(seg_id, base, limit, name);
                std::cout << ">> Da luu thong tin phan doan s = " << seg_id << "!\n";
                break;
            }
            case 4: {
                loadSampleData(table);
                table.displayTable();
                break;
            }
            case 5: {
                table.clear();
                std::cout << ">> Da xoa toan bo bang phan doan!\n";
                break;
            }
            default:
                std::cout << ">> Lua chon khong hop le! Vui long chon tu 0 den 5.\n";
                break;
        }
    }

    return 0;
}