# Quản lý sản phẩm bằng cây nhị phân tìm kiếm (BST)

## Giới thiệu

Chương trình cài đặt cây nhị phân tìm kiếm (Binary Search Tree - BST) bằng C++ để quản lý danh sách sản phẩm.
Mỗi node trong cây lưu trữ thông tin một sản phẩm và hai con trỏ đến node con trái, node con phải.

**Cây BST được tổ chức theo mã sản phẩm:**

* Mã sản phẩm nhỏ hơn mã tại node hiện tại: đi sang cây con trái.

* Mã sản phẩm lớn hơn mã tại node hiện tại: đi sang cây con phải.

* Mã sản phẩm đã tồn tại: không cho phép chèn thêm sản phẩm trùng mã.

Chương trình hỗ trợ thêm, tìm kiếm, xóa sản phẩm, in danh sách theo mã tăng dần, đếm số node, tính chiều cao cây và nạp dữ liệu mẫu.

## Cấu trúc dữ liệu

```
struct Product {
    int maSP;
    char tenSP[50];
    int soLuong;
    double donGia;
};

struct Node {
    Product data;
    Node* left;
    Node* right;
};

Node* root = NULL;

```

**Trong đó:**

* `maSP`: Mã sản phẩm.

* `tenSP`: Tên sản phẩm.

* `soLuong`: Số lượng sản phẩm.

* `donGia`: Đơn giá sản phẩm.

* `data`: Thông tin sản phẩm được lưu tại node.

* `left`: Con trỏ đến node con trái.

* `right`: Con trỏ đến node con phải.

* `root`: Con trỏ đến node gốc của cây.

* `NULL`: Biểu thị cây rỗng hoặc không có node con.

## Quy tắc tổ chức cây

Cây được sắp xếp theo mã sản phẩm. Ví dụ, sau khi nạp 7 sản phẩm mẫu, cây có cấu trúc:

```
          50
        /    \
      30      70
     /  \    /  \
    20  40  60  80

```

**Trong đó:**

* Node 50 là node gốc.

* Node 30 và 70 lần lượt là con trái và con phải của node 50.

* Node 20 và 40 thuộc cây con trái.

* Node 60 và 80 thuộc cây con phải.

* Các node 20, 40, 60, 80 là node lá.

Cấu trúc cây được hình thành bằng cách lần lượt chèn các sản phẩm theo thứ tự trong mảng dữ liệu mẫu.

## Các chức năng

### Khởi tạo cây và tạo node

Hàm `taoNode()` cấp phát bộ nhớ động để tạo một node mới.

* **Chức năng thực hiện:**

  * Cấp phát bộ nhớ bằng `new(nothrow)`.

  * Kiểm tra việc cấp phát bộ nhớ.

  * Sao chép thông tin sản phẩm vào node.

  * Khởi tạo hai con trỏ `left` và `right` bằng `NULL`.

  * Trả về con trỏ đến node vừa tạo.

  * Nếu không đủ bộ nhớ, chương trình thông báo lỗi và trả về `NULL`.

### 1. Thêm sản phẩm

Hàm chính: `chen()`. Cho phép thêm một sản phẩm mới vào cây BST.

* **Chương trình thực hiện:**

  * Nhập mã sản phẩm, tên sản phẩm, số lượng và đơn giá.

  * Kiểm tra tính hợp lệ của dữ liệu bằng hàm `duLieuHopLe()`.

  * So sánh mã sản phẩm với mã tại node hiện tại.

  * Nếu mã nhỏ hơn, tiếp tục chèn vào cây con trái.

  * Nếu mã lớn hơn, tiếp tục chèn vào cây con phải.

  * Nếu gặp vị trí `NULL`, tạo node mới và chèn vào cây.

  * Nếu mã đã tồn tại, thông báo không cho phép chèn trùng.

* **Các điều kiện kiểm tra:**

  * Mã sản phẩm phải là số nguyên dương.

  * Tên sản phẩm không được để trống.

  * Số lượng không được âm.

  * Đơn giá không được âm.

### 2. Tìm kiếm sản phẩm

Hàm chính: `timKiem()`. Cho phép tìm sản phẩm dựa trên mã sản phẩm.

* **Nguyên lý hoạt động:**

  * Nếu cây rỗng, trả về `NULL`.

  * Nếu mã sản phẩm cần tìm bằng mã tại node hiện tại, trả về node đó.

  * Nếu mã cần tìm nhỏ hơn mã tại node hiện tại, tìm trong cây con trái.

  * Nếu mã cần tìm lớn hơn mã tại node hiện tại, tìm trong cây con phải.

  * Nếu không tìm thấy, trả về `NULL`.

  * Nếu tìm thấy, chương trình hiển thị thông tin sản phẩm gồm mã, tên, số lượng và đơn giá.

  * Nếu không tìm thấy, chương trình thông báo: `Khong tim thay san pham!`

### 3. Xóa sản phẩm

Hàm chính: `xoa()`. Cho phép xóa một sản phẩm khỏi cây dựa trên mã sản phẩm. Chương trình sử dụng đệ quy để tìm node cần xóa. Khi tìm thấy, thực hiện một trong ba trường hợp:

* **Trường hợp 1:** Node cần xóa là node lá

  * Giải phóng bộ nhớ của node.

  * Gán con trỏ tại vị trí đó bằng `NULL`.

* **Trường hợp 2:** Node chỉ có một con

  * Nếu chỉ có con phải, đưa cây con phải lên thay thế node cần xóa.

  * Nếu chỉ có con trái, đưa cây con trái lên thay thế node cần xóa.

  * Giải phóng bộ nhớ của node cũ.

* **Trường hợp 3:** Node có hai con

  * Sử dụng hàm `timMin()` để tìm node có mã nhỏ nhất trong cây con phải.

  * Sao chép toàn bộ thông tin sản phẩm của node tìm được vào node cần xóa.

  * Gọi đệ quy để xóa node kế tiếp trung thứ tự tại vị trí cũ.

Nếu mã sản phẩm không tồn tại, chương trình thông báo không tìm thấy sản phẩm trước khi thực hiện xóa.

### 4. In danh sách sản phẩm theo mã tăng dần

Hàm chính: `duyetLNR()`. Sử dụng phép duyệt trung thứ tự (LNR - Left, Node, Right).

* **Thứ tự thực hiện:**

  * Duyệt cây con trái.

  * In thông tin node hiện tại.

  * Duyệt cây con phải.

Do cây được tổ chức theo mã sản phẩm, phép duyệt LNR giúp hiển thị danh sách sản phẩm theo mã tăng dần. Hàm `inTieuDe()` in tiêu đề các cột. Hàm `inSanPham()` hiển thị thông tin từng sản phẩm (`Ma SP | Ten san pham | So luong | Don gia`).

### 5. Đếm số node và tính chiều cao cây

* Hàm **`demNode()`:** Sử dụng đệ quy để đếm tổng số node trong cây.

  * Công thức: `So node = 1 + So node trai + So node phai`

* **Hàm `chieuCao()`:** Sử dụng đệ quy để tính chiều cao cây theo số mức.

  * Công thức: `Chieu cao = 1 + max(Chieu cao trai, Chieu cao phai)`

  * Kết quả cây mẫu 7 node: `So nut trong cay: 7 | Chieu cao cay: 3`

### 6. Nạp 7 sản phẩm mẫu

Hàm chính: `taoDuLieuMau()`. Cho phép nạp nhanh 7 sản phẩm mẫu để kiểm thử chương trình:

| Mã SP | Tên sản phẩm | Số lượng | Đơn giá | 
| ----- | ----- | ----- | ----- | 
| 50 | But bi | 120 | 5000 | 
| 30 | Vo o ly | 80 | 12000 | 
| 70 | Bia ho so | 35 | 15000 | 
| 20 | Thuoc ke | 40 | 8000 | 
| 40 | Tay | 65 | 4000 | 
| 60 | So tay | 25 | 25000 | 
| 80 | But chi | 110 | 3000 | 

### 7. Giải phóng bộ nhớ

Hàm chính: \`giai