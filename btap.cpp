#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Cau truc luu tro thong tin mot san pham
struct SanPham {
    int maSP;
    string tenSP;
    int soLuong;
    double donGia;
};

// Cau truc nut trong Cay Nhi Phan Tim Kiem (BST)
struct Nut {
    SanPham duLieu;
    Nut* trai;
    Nut* phai;

    Nut(SanPham sp) : duLieu(sp), trai(nullptr), phai(nullptr) {}
};

// Lop Quan ly Cay Nhi Phan Tim Kiem
class CayNhiPhanTimKiem {
private:
    Nut* goc;

    // Tao nut moi
    Nut* taoNutMoi(SanPham sp) {
        return new Nut(sp);
    }

    // Chen nut vao cay (de quy)
    Nut* chenNut(Nut* nut, SanPham sp, bool &daThem) {
        if (nut == nullptr) {
            daThem = true;
            return taoNutMoi(sp);
        }

        if (sp.maSP < nut->duLieu.maSP) {
            nut->trai = chenNut(nut->trai, sp, daThem);
        } else if (sp.maSP > nut->duLieu.maSP) {
            nut->phai = chenNut(nut->phai, sp, daThem);
        } else {
            daThem = false; // Ma san pham da ton tai
        }

        return nut;
    }

    // Tim nut co gia tri nho nhat o cay con phai (Inorder Successor)
    Nut* timNutNhoNhat(Nut* nut) {
        Nut* hienTai = nut;
        while (hienTai && hienTai->trai != nullptr) {
            hienTai = hienTai->trai;
        }
        return hienTai;
    }

    // Xoa nut khoi cay (de quy - xu ly 3 truong hop)
    Nut* xoaNut(Nut* nut, int maSP, bool &daXoa) {
        if (nut == nullptr) {
            daXoa = false;
            return nullptr;
        }

        if (maSP < nut->duLieu.maSP) {
            nut->trai = xoaNut(nut->trai, maSP, daXoa);
        } else if (maSP > nut->duLieu.maSP) {
            nut->phai = xoaNut(nut->phai, maSP, daXoa);
        } else {
            // Da tim thay nut can xoa
            daXoa = true;

            // Truong hop 1: Nut la hoac chi co con phai
            if (nut->trai == nullptr) {
                Nut* tam = nut->phai;
                delete nut;
                return tam;
            }
            // Truong hop 2: Chi co con trai
            else if (nut->phai == nullptr) {
                Nut* tam = nut->trai;
                delete nut;
                return tam;
            }

            // Truong hop 3: Nut co 2 con
            Nut* tam = timNutNhoNhat(nut->phai);
            nut->duLieu = tam->duLieu;
            nut->phai = xoaNut(nut->phai, tam->duLieu.maSP, daXoa);
        }
        return nut;
    }

    // Duyet LNR in danh sach
    void duyetLNR(Nut* nut) {
        if (nut != nullptr) {
            duyetLNR(nut->trai);
            cout << "| " << setw(8) << left << nut->duLieu.maSP
                 << "| " << setw(32) << left << nut->duLieu.tenSP
                 << "| " << setw(10) << right << nut->duLieu.soLuong
                 << " | " << setw(14) << right << fixed << setprecision(0) << nut->duLieu.donGia << " |\n";
            duyetLNR(nut->phai);
        }
    }

    // Dem so nut tren cay
    int demSoNutDeQuy(Nut* nut) {
        if (nut == nullptr) return 0;
        return 1 + demSoNutDeQuy(nut->trai) + demSoNutDeQuy(nut->phai);
    }

    // Tinh chieu cao cay (tinh theo so nut tren duong dai nhat)
    int tinhChieuCaoDeQuy(Nut* nut) {
        if (nut == nullptr) return 0;
        int chieuCaoTrai = tinhChieuCaoDeQuy(nut->trai);
        int chieuCaoPhai = tinhChieuCaoDeQuy(nut->phai);
        return 1 + max(chieuCaoTrai, chieuCaoPhai);
    }

    // Giai phong toan bo cay
    void giaiPhongDeQuy(Nut* nut) {
        if (nut != nullptr) {
            giaiPhongDeQuy(nut->trai);
            giaiPhongDeQuy(nut->phai);
            delete nut;
        }
    }

public:
    CayNhiPhanTimKiem() : goc(nullptr) {}

    ~CayNhiPhanTimKiem() {
        giaiPhong();
    }

    // F1: Them mot san pham
    bool themSanPham(SanPham sp) {
        bool daThem = false;
        goc = chenNut(goc, sp, daThem);
        return daThem;
    }

    // F2: Tim kiem san pham theo maSP
    Nut* timKiemSanPham(int maSP) {
        Nut* hienTai = goc;
        while (hienTai != nullptr) {
            if (maSP == hienTai->duLieu.maSP) {
                return hienTai;
            } else if (maSP < hienTai->duLieu.maSP) {
                hienTai = hienTai->trai;
            } else {
                hienTai = hienTai->phai;
            }
        }
        return nullptr;
    }

    // F3: Xoa san pham theo maSP
    bool xoaSanPham(int maSP) {
        bool daXoa = false;
        goc = xoaNut(goc, maSP, daXoa);
        return daXoa;
    }

    // F4: In danh sach san pham theo thu tu tang dan (LNR)
    void inDanhSachSanPham() {
        if (goc == nullptr) {
            cout << "[!] Cay rong! Khong co san pham nao trong danh muc.\n";
            return;
        }
        cout << "+---------+----------------------------------+------------+----------------+\n";
        cout << "| Ma SP   | Ten san pham                     | So luong   | Don gia (VND)  |\n";
        cout << "+---------+----------------------------------+------------+----------------+\n";
        duyetLNR(goc);
        cout << "+---------+----------------------------------+------------+----------------+\n";
    }

    // F5: Thong ke so nut va chieu cao cay
    int demSoNut() {
        return demSoNutDeQuy(goc);
    }

    int tinhChieuCao() {
        return tinhChieuCaoDeQuy(goc);
    }

    // F7: Giai phong bo nho
    void giaiPhong() {
        giaiPhongDeQuy(goc);
        goc = nullptr;
    }

    // Doc du lieu tu file text (.txt)
    int docTuFile(const string& tenFile) {
        ifstream file(tenFile);
        if (!file.is_open()) {
            return -1;
        }

        string dong;
        int soLuongDaThem = 0;
        while (getline(file, dong)) {
            if (dong.empty()) continue;

            stringstream ss(dong);
            string maStr, tenSP, soLuongStr, donGiaStr;

            if (getline(ss, maStr, ',') &&
                getline(ss, tenSP, ',') &&
                getline(ss, soLuongStr, ',') &&
                getline(ss, donGiaStr, ',')) {

                try {
                    SanPham sp;
                    sp.maSP = stoi(maStr);
                    sp.tenSP = tenSP;
                    sp.soLuong = stoi(soLuongStr);
                    sp.donGia = stod(donGiaStr);

                    if (sp.maSP > 0 && sp.soLuong >= 0 && sp.donGia >= 0 && !sp.tenSP.empty()) {
                        if (themSanPham(sp)) {
                            soLuongDaThem++;
                        }
                    }
                } catch (...) {
                    continue;
                }
            }
        }
        file.close();
        return soLuongDaThem;
    }
};

// Ham xoa bo nho dem nhap lieu
void xoaBoNhoDem() {
    cin.clear();
    cin.ignore(10000, '\n');
}

int main() {
    CayNhiPhanTimKiem cay;
    int luaChon = -1;

    do {
        cout << "\n================= CHUONG TRINH QUAN LY BST (C++) =================\n";
        cout << "1. Nap du lieu tu file (.txt)\n";
        cout << "2. F1 - Them moi mot san pham\n";
        cout << "3. F2 - Tim kiem san pham theo ma (maSP)\n";
        cout << "4. F3 - Xoa san pham theo ma (maSP)\n";
        cout << "5. F4 - In danh sach san pham (Duyet LNR - Tang dan)\n";
        cout << "6. F5 - Thong ke cay (So luong nut & Chieu cao cay)\n";
        cout << "7. F7 - Giai phong bo nho cay\n";
        cout << "0. F6 - Thoat chuong trinh\n";
        cout << "------------------------------------------------------------------\n";
        cout << "Chon chuc nang (0-7): ";

        if (!(cin >> luaChon)) {
            cout << "[!] Loi nhap lieu! Vui long nhap so nguyen.\n";
            xoaBoNhoDem();
            continue;
        }

        switch (luaChon) {
            case 1: {
                string tenFile;
                cout << "Nhap ten file (mac dinh 'dulieu.txt'): ";
                xoaBoNhoDem();
                getline(cin, tenFile);
                if (tenFile.empty()) tenFile = "dulieu.txt";

                int ketQua = cay.docTuFile(tenFile);
                if (ketQua < 0) {
                    cout << "[!] Khong the mo file '" << tenFile << "'. Vui long kiem tra lai duong dan!\n";
                } else {
                    cout << "[+] Da nap thanh cong " << ketQua << " san pham tu file '" << tenFile << "'.\n";
                }
                break;
            }
            case 2: { // F1
                SanPham sp;
                cout << "\n--- THEM MOI SAN PHAM (F1) ---\n";
                cout << "Nhap ma san pham (maSP > 0): ";
                while (!(cin >> sp.maSP) || sp.maSP <= 0) {
                    cout << "[!] Ma san pham phai la so nguyen duong. Nhap lai: ";
                    xoaBoNhoDem();
                }

                cout << "Nhap ten san pham: ";
                xoaBoNhoDem();
                getline(cin, sp.tenSP);
                while (sp.tenSP.empty() || sp.tenSP.length() >= 50) {
                    cout << "[!] Ten san pham khong duoc rong va duoi 50 ky tu. Nhap lai: ";
                    getline(cin, sp.tenSP);
                }

                cout << "Nhap so luong (>= 0): ";
                while (!(cin >> sp.soLuong) || sp.soLuong < 0) {
                    cout << "[!] So luong phai la so nguyen khong am. Nhap lai: ";
                    xoaBoNhoDem();
                }

                cout << "Nhap don gia (>= 0): ";
                while (!(cin >> sp.donGia) || sp.donGia < 0) {
                    cout << "[!] Don gia phai la so khong am. Nhap lai: ";
                    xoaBoNhoDem();
                }

                if (cay.themSanPham(sp)) {
                    cout << "[+] Them san pham thanh cong!\n";
                } else {
                    cout << "[!] Ma san pham da ton tai! Khong the them nut moi.\n";
                }
                break;
            }
            case 3: { // F2
                int maSP;
                cout << "\n--- TIM KIEM SAN PHAM (F2) ---\n";
                cout << "Nhap ma san pham can tim: ";
                if (cin >> maSP) {
                    Nut* ketQua = cay.timKiemSanPham(maSP);
                    if (ketQua != nullptr) {
                        cout << "[+] DA TIM THAY SAN PHAM:\n";
                        cout << "    - Ma SP   : " << ketQua->duLieu.maSP << "\n";
                        cout << "    - Ten SP  : " << ketQua->duLieu.tenSP << "\n";
                        cout << "    - So luong: " << ketQua->duLieu.soLuong << "\n";
                        cout << "    - Don gia : " << fixed << setprecision(0) << ketQua->duLieu.donGia << " VND\n";
                    } else {
                        cout << "[-] Khong tim thay san pham co ma: " << maSP << "\n";
                    }
                } else {
                    cout << "[!] Ma san pham khong hop le.\n";
                    xoaBoNhoDem();
                }
                break;
            }
            case 4: { // F3
                int maSP;
                cout << "\n--- XOA SAN PHAM (F3) ---\n";
                cout << "Nhap ma san pham can xoa: ";
                if (cin >> maSP) {
                    if (cay.xoaSanPham(maSP)) {
                        cout << "[+] Da xoa thanh cong san pham co ma: " << maSP << "\n";
                    } else {
                        cout << "[-] Khong tim thay san pham co ma: " << maSP << "\n";
                    }
                } else {
                    cout << "[!] Ma san pham khong hop le.\n";
                    xoaBoNhoDem();
                }
                break;
            }
            case 5: { // F4
                cout << "\n--- DANH SACH SAN PHAM (DUYET LNR - TANG DAN) (F4) ---\n";
                cay.inDanhSachSanPham();
                break;
            }
            case 6: { // F5
                cout << "\n--- THONG KE CAY BST (F5) ---\n";
                cout << " - Tong so nut tren cay  : " << cay.demSoNut() << "\n";
                cout << " - Chieu cao cua cay     : " << cay.tinhChieuCao() << "\n";
                break;
            }
            case 7: { // F7
                cay.giaiPhong();
                cout << "[+] Da giai phong toan bo bo nho cay BST thanh cong!\n";
                break;
            }
            case 0: { // F6
                cay.giaiPhong();
                cout << "Cam on ban da su dung chuong trinh. Tam biet!\n";
                break;
            }
            default:
                cout << "[!] Lua chon khong hop le! Vui long chon tu 0 den 7.\n";
                break;
        }

    } while (luaChon != 0);

    return 0;
}