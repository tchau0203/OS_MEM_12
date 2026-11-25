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
// khởi tạo bảng phân đoạn + mở tệp test
    ifstream file("tests/cases.txt");
    if (!file.is_open()) {
        cerr << "Khong the mo file tests/cases.txt\n";
        return 1;
    }
// khai báo các biến    
    int segment, offset;
    int expectedStatus, expectedPhysical;
    int total = 0;
    int passed = 0;
    int failed = 0;
    string line;
    cout << "========== SEGMENTATION TEST ==========\n\n";
// đọc tệp và lọc dữ liệu
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
// dịch địa chỉ rồi đối chiếu kết quả
        LogicalAddress addr = {segment, offset};
        TranslateResult result = translate(table, addr);

        bool correct = (result.ok == (expectedStatus == 1));
        if (expectedStatus == 1) {
            correct = correct &&
                      (result.physical == expectedPhysical); 
        }
// in kq của từng case
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
    cout << "Total test cases: " << total << "\n";
    cout << "Passed: " << passed << "\n";
    cout << "Failed: " << failed << "\n";
    if (failed == 0 && total > 0) {
        cout << "\nAll test cases passed!\n";
        return 0;
    }
    cout << "\nThere are some failed test cases!\n";
    return 1;
}
