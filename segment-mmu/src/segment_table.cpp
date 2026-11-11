#include "segment.h"

#include <iostream>
#include <limits>
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

long long endExclusive(const Segment& segment) {
    return static_cast<long long>(segment.base) + segment.limit;
}

bool overlaps(const Segment& a, const Segment& b) {
    // Empty segments occupy no memory; adjacent half-open ranges do not overlap.
    return a.limit > 0 && b.limit > 0 &&
           a.base < endExclusive(b) && b.base < endExclusive(a);
}

bool readRange(const SegmentTable& table, Segment& segment) {
    for (;;) {
        if (!readNonNegativeInt("  Base: ", segment.base) ||
            !readNonNegativeInt("  Limit: ", segment.limit)) {
            return false;
        }

        // The MMU returns int addresses; the last valid byte must fit in int.
        if (segment.limit > 0 &&
            endExclusive(segment) - 1 > std::numeric_limits<int>::max()) {
            std::cout << "Loi: dia chi cuoi vuot gioi han kieu int. "
                         "Hay nhap lai base va limit.\n";
            continue;
        }

        bool conflict = false;
        for (const Segment& existing : table) {
            if (overlaps(segment, existing)) {
                std::cout << "Loi: vung nho chong len doan '" << existing.name
                          << "'. Hay nhap lai base va limit.\n";
                conflict = true;
                break;
            }
        }
        if (!conflict) {
            return true;
        }
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
        if (!readRange(table, segment) || !readName(segment.name)) {
            return {};
        }
        table.push_back(segment);
    }
    return table;
}
