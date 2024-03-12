#ifndef QUANLYCONTACT_H
#define QUANLYCONTACT_H
#include "Contact.h"
#include <vector>
using namespace std;
class QuanLyContact {
private:
    std::vector<Contact> danhBa;
    std::string tenFile;

public:
    QuanLyContact(const std::string& _tenFile);
    void hienThiDanhBa() const;
    void themLienHe();
    void timContactTheoTen();
    void thayDoiThongTinLienHe();
    void xoaContact();
    void thongKeDanhBa();
    void saoLuuDuLieu();
    void khoiPhucDuLieu();
    void dongBoBanSao(const std::string& tenTepBackup);

private:
    // Đọc danh bạ từ file CSV
    void readContactsFromFile();

    // Ghi danh bạ vào file CSV
    void ghiDanhBaVaoFile() const;
};
#endif
