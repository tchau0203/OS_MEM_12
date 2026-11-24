#include <iostream>
#include "segment.h"         

SegmentTable table;

void inputSegmentTable() {
    table = loadSegmentTable();
    std::cout << "\n>> Da cap nhat bang phan doan!\n";
}

int translateAddress() {
    if (table.empty()) {
        std::cout << "\n[!] Bang phan doan dang rong. Hay nhap bang phan doan truoc.\n";
        return -1;
    }
    LogicalAddress addr;
    std::cout << "Nhap so hieu doan (s): ";
    std::cin >> addr.segment;
    std::cout << "Nhap do doi (d): ";
    std::cin >> addr.offset;

    TranslateResult res = translate(table, addr);
    if (res.ok) {
        std::cout << ">> Dia chi vat ly: " << res.physical << "\n";
        return res.physical;
    } else {
        std::cout << ">> Loi: " << res.error << "\n";
        return -1;
    }
}

void printMenu() {
    std::cout << "\n====== SEGMENT MMU SIMULATOR ======\n";
    std::cout << "1. Nhap bang phan doan\n";
    std::cout << "2. Dich dia chi logic -> vat ly\n";
    std::cout << "3. Xem bang phan doan hien tai\n";
    std::cout << "0. Thoat\n";
    std::cout << "Chon: ";
}

int main() {
    int choice;
    do {
        printMenu();
        std::cin >> choice;
        switch (choice) {
            case 1: inputSegmentTable(); break;
            case 2: translateAddress();  break;
            case 3: printSegmentTable(table); break;
            case 0: std::cout << "Thoat.\n"; break;
            default: std::cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
    return 0;
}