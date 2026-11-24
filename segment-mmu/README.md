# Segmentation and Logical Address Translation

## 1. Giới thiệu

Dự án được thực hiện nhằm tìm hiểu cơ chế quản lý bộ nhớ Segmentation (phân đoạn) trong hệ điều hành và quá trình chuyển đổi địa chỉ logic (Logical Address) sang địa chỉ vật lý (Physical Address).

Trong cơ chế Segmentation, bộ nhớ của một chương trình được chia thành nhiều phân đoạn (Segment) có kích thước khác nhau. Mỗi phân đoạn được quản lý thông qua bảng phân đoạn (Segment Table).

Chương trình mô phỏng quá trình:
- Quản lý thông tin các phân đoạn.
- Nhập và kiểm tra dữ liệu trong bảng phân đoạn.
- Tiếp nhận địa chỉ logic từ người dùng.
- Kiểm tra tính hợp lệ của địa chỉ.
- Chuyển đổi địa chỉ logic thành địa chỉ vật lý.
- Xử lý các trường hợp địa chỉ không hợp lệ.

## 2. Chức năng chính

- **Quản lý bảng phân đoạn:** Lưu trữ thông tin về các phân đoạn trong bộ nhớ.
- **Kiểm tra dữ liệu:** Kiểm tra tính hợp lệ của thông tin phân đoạn.
- **Dịch địa chỉ:** Chuyển đổi địa chỉ logic gồm số hiệu phân đoạn (Segment Number) và độ dời (Offset) thành địa chỉ vật lý.
- **Bảo vệ bộ nhớ:** Kiểm tra giới hạn phân đoạn (Limit) để phát hiện địa chỉ truy cập vượt phạm vi cho phép.
- **Giao diện chương trình:** Cung cấp menu để người dùng tương tác và thực hiện các chức năng.

## 3. Cấu trúc thư mục

```text
segment-mmu/
│
├── docs/
│   ├── bao-cao-nguoi-2.md
│   └── theory.md
│
├── include/
│   └── segment.h
│
├── src/
│   ├── main.cpp
│   ├── mmu.cpp
│   └── segment_table.cpp
│
├── tests/
│   ├── cases.txt
│   └── test.cpp
├── CMakeLists.txt
├── README.md
└── .gitignore
```

### Vai trò các thành phần

| Thành phần | Chức năng |
|---|---|
| `docs/` | Chứa tài liệu và lý thuyết của dự án. |
| `include/segment.h` | Khai báo các cấu trúc dữ liệu và thành phần liên quan đến Segmentation. |
| `src/main.cpp` | Chứa hàm main và menu điều khiển chương trình. |
| `src/mmu.cpp` | Thực hiện quá trình dịch địa chỉ logic sang địa chỉ vật lý. |
| `src/segment_table.cpp` | Quản lý và kiểm tra bảng phân đoạn. |
| `tests/test_main.cpp` | Chứa các trường hợp kiểm thử chương trình. |
| `CMakeLists.txt` | Cấu hình quá trình biên dịch bằng CMake. |

## 4. Công nghệ sử dụng

- Ngôn ngữ lập trình: C++
- Trình biên dịch: GCC (g++)
- Công cụ quản lý build: CMake
- Môi trường phát triển: Visual Studio Code
- Quản lý mã nguồn: Git và GitHub

## 5. Hướng dẫn biên dịch và chạy chương trình

### Yêu cầu

Cài đặt các công cụ sau:
- GCC hoặc trình biên dịch C++ tương thích.
- CMake.
- Git (nếu tải project từ GitHub).

### Bước 1: Clone repository

```bash
git clone <repository-url>
```

### Bước 2: Di chuyển vào thư mục dự án

```bash
cd segment-mmu
```

### Bước 3: Tạo thư mục build

```bash
cmake -S . -B build
```

### Bước 4: Biên dịch chương trình

```bash
cmake --build build
```

### Bước 5: Chạy chương trình

Đường dẫn file thực thi phụ thuộc vào hệ điều hành và cấu hình CMake.

Ví dụ trên Windows:

```bash
.\build\Debug\<ten-chuong-trinh>.exe
```

Ví dụ trên Linux:

```bash
./build/<ten-chuong-trinh>
```

Lưu ý: Tên chương trình thực thi cần được thay bằng tên target được khai báo trong `CMakeLists.txt`.

## 6. Kiểm thử (Testing)

Dự án sử dụng các test case để kiểm tra tính chính xác của quá trình quản lý phân đoạn và dịch địa chỉ.

Các trường hợp kiểm thử dự kiến bao gồm:

| Trường hợp kiểm thử | Kết quả mong đợi |
|---|---|
| Địa chỉ logic hợp lệ | Dịch thành công sang địa chỉ vật lý. |
| Segment không tồn tại | Từ chối, báo lỗi Segment không tồn tại . |
| Offset bằng hoặc vượt Limit | Từ chối, báo lỗi vượt giới hạn. |
| Segment Number âm | Từ chối, báo lỗi chỉ số Segment không hợp lệ. |
| Offset âm | Từ chối, báo lỗi Offset âm. |
| Dữ liệu bảng phân đoạn không hợp lệ | Thông báo lỗi hoặc từ chối dữ liệu. |

Các test case được thực hiện nhằm đối chiếu kết quả chương trình với kết quả tính toán lý thuyết.

## 7. Phân công công việc

| Thành viên | Nhiệm vụ |
|---|---|
| Minh | Khai báo cấu trúc dữ liệu trong `include/segment.h` và viết tài liệu lý thuyết trong `docs/theory.md`. |
| Hoàng | Xây dựng chức năng nhập bảng phân đoạn và kiểm tra dữ liệu trong `src/segment_table.cpp`. |
| Tuấn | Xây dựng và hoàn thiện chức năng dịch địa chỉ logic sang địa chỉ vật lý trong `src/mmu.cpp`. |
| Châu | Xây dựng menu chương trình trong `src/main.cpp` và quản lý repository, Pull Request trên GitHub. |
| Sơn | Xây dựng test case, kiểm thử chương trình và viết tài liệu `README.md`. |