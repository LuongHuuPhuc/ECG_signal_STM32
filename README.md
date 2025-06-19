# *Đọc tín hiệu ECG bằng AD8232 sử dụng Timer Trigger và DMA* # 
## *1. Cách cấu hình* ##
- Timer là bộ đếm định kỳ 
- Prescaler là bộ chia tần để điều chỉnh tốc độ đếm 
- Period xác định số tick cần đếm trước khi trigger (Ví dụ để là 49 thì sau 49 tick, nó sẽ trigger 1 lần)
- TRGO (Trigger Output): Đây là tín hiệu được phát ra từ Timer khi nó được trigger
- ADC được kích hoạt bẳng TRGO -> Giúp lấy mẫu đều đặn và không phụ thuộc vào CPU 
 
## *2. Hiểu về bản chất của việc Timer Trigger* ## 
* Khoảng thời gian mà Timer Trigger chính là **chu kỳ lấy mẫu (Sample Period)** và nó cũng là **tần số lấy mẫu/tốc độ lấy mẫu (Sampling Frequency/Sampling rate)**
* Ta không nên sử dụng Delay của hệ thông như HAL_Delay() vì đây là hàm khiến cả hệ thống/chương trình bị ngừng lại và không làm gì cả, khiến cho sai lệch về thời gian thực tế 
và ảnh hưởng đến việc phân tích QRS của ECG
* Thế nên để có thể lấy mãu liên tục mà ít bị mất mẫu thì nên dùng DMA + Timer để dữ liệu có thể liên tục được cập nhật mà không cần sự can thiệp của CPU, giúp 
tăng tính đồng bộ hóa <br>

### *Vậy Timer hoạt động như thế nào ?* ###
Timer là bộ đếm, nó sẽ đếm từ 0, mỗi lần tăng 1 giá trị, gọi là 1 tick.
* Tốc độ phụ thuộc vào: *Tần số Clock Timer* và *Prescaler* 
* Timer đếm từ 0 đến giá trị ARR (AutoReload Register) - tức là Counter Period mà đã set trong CubeMX
* Khi đếm xong (đạt ARR), nó: 
  - Reset về lại 0 
  - Gây 1 sự kiện "Update Event"
  - Nếu bạn chỉnh cấu hình TRGO = Update Event -> Timer sẽ phát 1 xung trigger tại đây 
  - Chính xung này được gọi là xung Trigger Output (TRGO) -> ADC nhận được và bắt đầu lấy mẫu
