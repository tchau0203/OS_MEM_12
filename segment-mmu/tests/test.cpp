#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "segment.h"
using namespace std;
int main() {
    SegmentTable table = {
        {1000, 100, "Code"},
        {2000, 200, "Data"},
        {3000, 50, "Stack"}
    };
    
    ifstream file("tests/cases.txt");
    if (!file.is_open()) {
        cerr << "Khong the mo file tests/cases.txt\n";
        return 1;
    }
    int segment, offset;
    int expectedStatus, expectedPhysical;
    int total = 0;
    int passed = 0;
    int failed = 0;
    string line;
    cout << "========== SEGMENTATION TEST ==========\n\n";

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;
        }
        stringstream ss(line);

        if (!(ss >> segment >> offset
                 >> expectedStatus >> expectedPhysical)) {
            continue;
        }
        total++;

        LogicalAddress addr = {segment, offset};
        TranslateResult result = translate(table, addr);

        bool correct = (result.ok == (expectedStatus == 1));
        if (expectedStatus == 1) {
            correct = correct &&
                      (result.physical == expectedPhysical);
        }

        cout << "TC" << total << ": ";
        if (correct) {
            cout << "[PASS]";
            passed++;
        }
        else {
            cout << "[FAIL]";
            failed++;
        }
        cout << " Segment = " << segment
             << ", Offset = " << offset;
        if (result.ok) {
            cout << ", Physical = " << result.physical;
        }
        else {
            cout << ", Error = " << result.error;
        }
        cout << "\n";
    }
    file.close();

    cout << "\n========== TEST SUMMARY ==========\n";
    cout << "Tổng số test case: " << total << "\n";
    cout << "Thành công: " << passed << "\n";
    cout << "Thất bại: " << failed << "\n";
    if (failed == 0 && total > 0) {
        cout << "\nTất cả test cases đều passed!\n";
        return 0;
    }
    cout << "\nCó một số test case failed!\n";
    return 1;
}
