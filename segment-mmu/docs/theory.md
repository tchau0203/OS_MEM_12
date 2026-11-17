# Cơ sở lý thuyết: Phân đoạn bộ nhớ (Segmentation)

## 1. Phân đoạn là gì?

Phân đoạn (segmentation) là một cách quản lý bộ nhớ. Không gian địa chỉ của một tiến trình được chia thành nhiều **đoạn (segment)**, mỗi đoạn ứng với một phần có ý nghĩa đối với người lập trình, ví dụ:

- `code`: mã lệnh của chương trình
- `data`: biến toàn cục
- `stack`: ngăn xếp lời gọi hàm
- `heap`: vùng cấp phát động

Mỗi đoạn có kích thước riêng và nằm trên một vùng **liên tục** trong bộ nhớ vật lý. Các đoạn khác nhau không cần nằm sát nhau.

## 2. Địa chỉ logic

CPU tạo ra địa chỉ logic gồm hai phần:

```
<s, d>
```

- `s`: số hiệu đoạn (segment number), cho biết truy cập vào đoạn nào
- `d`: độ dời (offset), cho biết vị trí bên trong đoạn đó, tính từ đầu đoạn

Trong chương trình, địa chỉ logic được biểu diễn bằng kiểu `LogicalAddress { segment, offset }` khai báo trong `include/segment.h`.

## 3. Bảng phân đoạn

Mỗi tiến trình có một **bảng phân đoạn (segment table)**. Mỗi dòng của bảng mô tả một đoạn:

| Trường | Ý nghĩa |
|---|---|
| `base` | Địa chỉ vật lý bắt đầu của đoạn |
| `limit` | Kích thước (độ dài) của đoạn |
| `name` | Tên đoạn, giúp người dùng dễ theo dõi |

Trong chương trình, mỗi dòng là một `Segment { base, limit, name }`, và cả bảng là `SegmentTable` (`std::vector<Segment>`). Chỉ số của phần tử trong vector chính là số hiệu đoạn `s`.

## 4. Dịch địa chỉ logic sang địa chỉ vật lý

Bộ phận quản lý bộ nhớ (MMU) dịch địa chỉ `<s, d>` như sau:

1. Dùng `s` để tìm dòng tương ứng trong bảng phân đoạn.
2. So sánh `d` với `limit` của đoạn đó.
3. Nếu `0 ≤ d < limit`, địa chỉ hợp lệ và:

```
địa chỉ vật lý = base[s] + d
```

4. Nếu `d ≥ limit`, truy cập vượt ra ngoài đoạn. Phần cứng sinh ngắt (trap) và hệ điều hành báo lỗi **segmentation fault**.

Điều kiện là `d < limit` chứ không phải `d ≤ limit`: một đoạn dài `limit` byte chỉ có các vị trí từ `0` đến `limit − 1`.

## 5. Các kiểm tra trong hàm `translate()`

Hàm `translate()` trong `src/mmu.cpp` kiểm tra lần lượt các trường hợp dưới đây. Gặp lỗi ở bước nào thì dừng ngay và trả về `ok = false` kèm thông báo trong `error`.

| Bước | Điều kiện kiểm tra | Lỗi được chặn |
|---|---|---|
| 1 | Bảng phân đoạn không rỗng | Chưa nhập bảng |
| 2 | `0 ≤ s < số đoạn` | Đoạn không tồn tại |
| 3 | `d ≥ 0` | Độ dời âm |
| 4 | `d < limit[s]` | Segmentation fault |
| 5 | `base[s] + d` không vượt `INT_MAX` | Tràn số nguyên |

Qua cả 5 bước thì hàm trả về `ok = true` và `physical = base[s] + d`.

## 6. Ví dụ

Cho bảng phân đoạn:

| s | Tên | base | limit |
|---|---|---|---|
| 0 | code | 1400 | 1000 |
| 1 | stack | 6300 | 400 |
| 2 | data | 4300 | 400 |
| 3 | heap | 3200 | 1100 |
| 4 | lib | 4700 | 1000 |

**Ví dụ 1:** địa chỉ logic `<2, 53>`
- Đoạn 2 có limit = 400, và 53 < 400 nên hợp lệ.
- Địa chỉ vật lý = 4300 + 53 = **4353**.

**Ví dụ 2:** địa chỉ logic `<3, 852>`
- Đoạn 3 có limit = 1100, và 852 < 1100 nên hợp lệ.
- Địa chỉ vật lý = 3200 + 852 = **4052**.

**Ví dụ 3:** địa chỉ logic `<0, 1222>`
- Đoạn 0 có limit = 1000, mà 1222 ≥ 1000.
- Kết quả: **segmentation fault**.

**Ví dụ 4:** địa chỉ logic `<1, 400>`
- Đoạn 1 có limit = 400, mà 400 ≥ 400 (offset hợp lệ chỉ từ 0 đến 399).
- Kết quả: **segmentation fault**.

**Ví dụ 5:** địa chỉ logic `<7, 10>`
- Bảng chỉ có các đoạn từ 0 đến 4.
- Kết quả: **lỗi, đoạn 7 không tồn tại**.

## 7. Ưu điểm và nhược điểm

**Ưu điểm**
- Chia bộ nhớ theo cách người lập trình nhìn chương trình (code, data, stack…).
- Dễ bảo vệ bộ nhớ: mỗi đoạn có giới hạn riêng, truy cập vượt giới hạn sẽ bị chặn.
- Dễ chia sẻ: nhiều tiến trình có thể dùng chung một đoạn, ví dụ đoạn mã thư viện.

**Nhược điểm**
- Các đoạn có kích thước khác nhau nên dễ gây **phân mảnh ngoài (external fragmentation)**: bộ nhớ trống bị chia thành nhiều lỗ nhỏ, không đủ chỗ cho một đoạn lớn.
- Cần thêm thời gian tra bảng phân đoạn cho mỗi lần truy cập bộ nhớ.

## 8. Tài liệu tham khảo

- A. Silberschatz, P. B. Galvin, G. Gagne, *Operating System Concepts*, chương Main Memory (phần Segmentation).
