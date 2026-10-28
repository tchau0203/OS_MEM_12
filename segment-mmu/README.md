# Mô Phỏng Phân Đoạn Bộ Nhớ & MMU (Memory Segmentation & MMU Simulation)

Dự án mô phỏng cơ chế quản lý bộ nhớ theo kỹ thuật **Phân đoạn (Segmentation)** và quá trình dịch địa chỉ logic sang địa chỉ vật lý của bộ vi xử lý thông qua **MMU (Memory Management Unit)**.

---

## 👥 Bảng Phân Công Nhiệm Vụ

| Thành viên | Nhiệm vụ chính | Tệp phụ trách |
|:---|:---|:---|
| **Người 1** | Thiết kế cấu trúc dữ liệu, giao diện & Tài liệu lý thuyết | `include/segment.h`, `docs/theory.md` |
| **Người 2** | Cài đặt Bảng phân đoạn (Segment Table) | `src/segment_table.cpp` |
| **Người 3** | Cài đặt bộ xử lý chuyển đổi địa chỉ MMU | `src/mmu.cpp` |
| **BẠN** | Giao diện điều khiển CLI chính & Cấu hình Build CMake | `src/main.cpp`, `CMakeLists.txt` |
| **Người 5** | Bộ kiểm thử tự động & Tài liệu hướng dẫn | `tests/test_main.cpp`, `README.md` |

---

## 📁 Cấu Trúc Thư Mục Dự Án

```text
segment-mmu/
├── include/
│   └── segment.h          ← Người 1: Khai báo cấu trúc Segment, SegmentTable, MMU
├── src/
│   ├── main.cpp           ← BẠN: Giao diện CLI mô phỏng tương tác
│   ├── segment_table.cpp  ← Người 2: Cài đặt các hàm quản lý bảng phân đoạn
│   └── mmu.cpp            ← Người 3: Cài đặt logic dịch địa chỉ và bắt lỗi Trap
├── tests/
│   └── test_main.cpp      ← Người 5: Các ca kiểm thử Unit Test tự động
├── docs/
│   └── theory.md          ← Người 1: Tài liệu lý thuyết về cơ chế phân đoạn & MMU
├── README.md              ← Người 5: Tài liệu tổng quan và hướng dẫn chạy
└── CMakeLists.txt         ← BẠN: File cấu hình biên dịch bằng CMake
```

---

## 🚀 Hướng Dẫn Cài Đặt & Biên Dịch

### Cách 1: Sử Dụng CMake (Khuyên dùng)

1. Mở terminal tại thư mục `segment-mmu`:
   ```bash
   cd segment-mmu
   ```

2. Tạo thư mục build và cấu hình:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```

3. Biên dịch chương trình:
   - Trên Linux/macOS:
     ```bash
     make
     ```
   - Trên Windows (MinGW / GCC):
     ```bash
     cmake --build .
     ```

4. Chạy chương trình chính:
   ```bash
   # Trên Windows
   ./segment_mmu.exe
   # Trên Linux/macOS
   ./segment_mmu
   ```

5. Chạy bộ kiểm thử tự động:
   ```bash
   # Trên Windows
   ./test_mmu.exe
   # Trên Linux/macOS
   ./test_mmu
   ```

---

### Cách 2: Biên Dịch Trực Tiếp Bằng G++ (Không dùng CMake)

Nếu không cài đặt CMake, bạn có thể biên dịch trực tiếp bằng `g++` (yêu cầu C++17 trở lên):

- **Biên dịch và chạy chương trình chính:**
  ```bash
  g++ -std=c++17 -Iinclude src/main.cpp src/segment_table.cpp src/mmu.cpp -o segment_mmu
  ./segment_mmu
  ```

- **Biên dịch và chạy bộ kiểm thử:**
  ```bash
  g++ -std=c++17 -Iinclude tests/test_main.cpp src/segment_table.cpp src/mmu.cpp -o test_mmu
  ./test_mmu
  ```

---

## 💡 Ví Dụ Thực Thi

Khi chạy chương trình, bạn có thể chọn nạp dữ liệu mẫu và thử chuyển đổi:
- **Địa chỉ logic hợp lệ:** $\langle s=0, d=100 \rangle$ $\rightarrow$ Địa chỉ vật lý: $219 + 100 = 319$.
- **Địa chỉ vi phạm giới hạn:** $\langle s=1, d=20 \rangle$ $\rightarrow$ Báo lỗi: `Trap/Limit Violation: Offset d = 20 vuot qua gioi han Limit = 14`.
