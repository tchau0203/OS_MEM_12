#include <iostream>
#include "segment.h"         
void inputSegmentTable();     

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
            case 3: /* in bảng */ break;
            case 0: std::cout << "Thoat.\n"; break;
            default: std::cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
    return 0;
}