# Báo cáo Người 2: Nhập và kiểm tra bảng phân đoạn

**Đề tài:** Segmentation và địa chỉ logic · **Nhánh:** `feature/segment-table`

## Mục tiêu và phạm vi

Phần của Người 2 xây dựng bảng phân đoạn để bộ dịch địa chỉ tra cứu. Mỗi dòng có `base` là địa chỉ vật lý bắt đầu, `limit` là số byte của đoạn, và tên để người dùng nhận biết. Số hiệu đoạn là vị trí của dòng trong bảng, bắt đầu từ 0 và giữ nguyên theo thứ tự nhập.

## Cách nhập và kiểm tra

`loadSegmentTable()` yêu cầu nhập số đoạn, rồi lần lượt nhập `base`, `limit` và tên. Chương trình kiểm tra từng dòng: số phải là số nguyên không âm và nằm trong miền của `int`; tên phải có nội dung và có thể chứa khoảng trắng. Nếu sai, chương trình yêu cầu nhập lại. Khi đầu vào kết thúc giữa chừng, hàm trả về bảng rỗng thay vì giao một bảng nhập dở cho MMU.

Một đoạn chiếm khoảng `[base, base + limit)`, trong đó cận phải không thuộc đoạn. Hai đoạn có độ dài dương chồng lấn khi `base_A < end_B` và `base_B < end_A`. Chương trình kiểm tra đoạn mới với các đoạn đã nhập; nếu có giao nhau, người dùng nhập lại cặp `base` và `limit`. Hai đoạn liền kề được phép. Đoạn có `limit = 0` không chiếm byte nào và không có độ dời hợp lệ.

Để phù hợp với kiểu `int` mà hàm dịch trả về, địa chỉ cuối cùng của đoạn khác rỗng (`base + limit - 1`) phải biểu diễn được bằng `int`. Cận phải được tính bằng `long long` để phép kiểm tra không tràn số. Hàm `printSegmentTable()` in số đoạn, `base`, `limit`, cận phải không tính vào đoạn và tên.

## Minh họa và kiểm thử

| Dữ liệu hoặc thao tác | Kết quả |
| --- | --- |
| Đoạn 0: base 100, limit 20; đoạn 1: base 120, limit 10 | Chấp nhận: hai vùng [100, 120) và [120, 130) liền kề. |
| Thử thêm đoạn base 110, limit 10 | Từ chối vì vùng [110, 120) chồng lên đoạn 0. |
| Dịch (0, 19) với bảng trên | Địa chỉ vật lý 119, byte cuối của đoạn 0. |
| Dịch (0, 20) với bảng trên | Segmentation fault: độ dời bằng limit. |

Ví dụ cuối cho thấy cơ chế bảo vệ: dù địa chỉ 120 thuộc đoạn 1, truy cập qua đoạn 0 với độ dời 20 vẫn bị từ chối. Việc tạo bảng và việc kiểm tra địa chỉ là hai bước riêng: bảng hợp lệ do Người 2 cung cấp, còn hàm `translate()` của Người 3 kiểm tra số hiệu đoạn và độ dời trước khi tính `base + d`.

Đã biên dịch mô-đun nhập bảng cùng `mmu.cpp` bằng MSVC C++17 và chạy kiểm thử độc lập. Các ca kiểm tra bao gồm số âm, chữ, số vượt miền `int`, tên rỗng, chồng lấn, đoạn rỗng, dữ liệu nhập dở và hai biên của độ dời. Phần menu có thể gọi `loadSegmentTable()` để lấy bảng và `printSegmentTable(table)` để hiển thị. Quyền đọc/ghi theo đoạn thuộc phần mở rộng của MMU.
