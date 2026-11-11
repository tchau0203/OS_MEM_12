#include "segment.h"

#include <iostream>
#include <sstream>

namespace {

bool readNonNegativeInt(const char* prompt, int& value, bool skipLeadingSpace = false) {
    std::string line;
    for (;;) {
        std::cout << prompt;
        if (skipLeadingSpace) {
            std::cin >> std::ws;
            skipLeadingSpace = false;
        }
        if (!std::getline(std::cin, line)) {
            return false;
        }

        std::istringstream input(line);
        int parsed = 0;
        if ((input >> parsed) && parsed >= 0 && (input >> std::ws).eof()) {
            value = parsed;
            return true;
        }
        std::cout << "Loi: hay nhap mot so nguyen khong am hop le.\n";
    }
}

bool readName(std::string& name) {
    for (;;) {
        std::cout << "  Ten doan: ";
        if (!std::getline(std::cin, name)) {
            return false;
        }
        const auto first = name.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            name = name.substr(first, name.find_last_not_of(" \t\r\n") - first + 1);
            return true;
        }
        std::cout << "Loi: ten doan khong duoc de trong.\n";
    }
}

} // namespace

SegmentTable loadSegmentTable() {
    // The menu may have read its selection with operator>>, leaving a newline.
    int count = 0;
    if (!readNonNegativeInt("Nhap so doan: ", count, true)) {
        return {};
    }

    SegmentTable table;
    for (int index = 0; index < count; ++index) {
        Segment segment{};
        std::cout << "Doan " << index << ":\n";
        if (!readNonNegativeInt("  Base: ", segment.base) ||
            !readNonNegativeInt("  Limit: ", segment.limit) ||
            !readName(segment.name)) {
            return {};
        }
        table.push_back(segment);
    }
    return table;
}
