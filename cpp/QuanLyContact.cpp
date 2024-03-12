#include <iostream>
#include "../header/Contact.h"
#include "../header/QuanLyContact.h"
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <windows.h>
#include <fstream>
using namespace std;

QuanLyContact::QuanLyContact(const std::string &_tenFile) : tenFile(_tenFile)
{
    // Khởi tạo danh bạ từ file CSV khi tạo đối tượng QuanLyContact
    readContactsFromFile();
}

// Hiển thị thông tin các liên hệ
void QuanLyContact::hienThiDanhBa() const
{
    for (const auto &lienHe : danhBa)
    {
        std::cout << "ID: " << lienHe.getInfoAsString() << std::endl;
    }
}

// Thêm mới liên hệ vào danh bạ và ghi vào file CSV
void QuanLyContact::themLienHe()
{
    int id;
    std::string name;
    int phoneNumber;
    std::string email;
    std::string address;

    std::cout << "Add Contact:" << std::endl;

    std::cout << "ID: ";
    std::cin >> id;

    cin.ignore();

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Phone number: ";
    std::cin >> phoneNumber;

    std::cout << "Email: ";
    std::cin >> email;
    cin.ignore();

    std::cout << "Address: ";
    std::getline(std::cin, address);

    danhBa.push_back(Contact(id, name, phoneNumber, email, address));
    ghiDanhBaVaoFile();
    std::cout << "Add success." << std::endl;
}

void QuanLyContact::timContactTheoTen()
{
    std::string ten;
    std::cout << "Enter search name: ";
    cin.ignore();
    std::getline(std::cin, ten);
    vector<Contact> ds;

    for (auto &lienHe : danhBa)
    {
        if (lienHe.getName() == ten)
        {
            ds.push_back(lienHe);
        }
    }
    if (ds.size() == 0)
    {
        cout << "Does not exits";
    }
    else
    {
        for (const auto &i : ds)
        {
            std::cout << "ID: " << i.getInfoAsString() << std::endl;
        }
    }
}

// Đọc danh bạ từ file CSV
void QuanLyContact::readContactsFromFile()
{
    std::ifstream file(tenFile);

    if (!file.is_open())
    {
        std::cerr << "Không thể mở file " << tenFile << std::endl;
        return;
    }

    danhBa.clear(); // Xóa dữ liệu cũ trước khi đọc mới

    std::string line;
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;

        while (std::getline(ss, token, '|'))
        {
            tokens.push_back(token);
        }

        if (tokens.size() == 5)
        {
            int id = std::stoi(tokens[0]);
            std::string name = tokens[1];
            int phoneNumber = std::stoi(tokens[2]);
            std::string email = tokens[3];
            std::string address = tokens[4];

            danhBa.push_back(Contact(id, name, phoneNumber, email, address));
        }
    }

    file.close();
}

// Ghi danh bạ vào file CSV
void QuanLyContact::ghiDanhBaVaoFile() const
{
    std::ofstream file(tenFile);

    if (!file.is_open())
    {
        std::cerr << "Không thể mở file " << tenFile << " để ghi." << std::endl;
        return;
    }

    for (const auto &lienHe : danhBa)
    {
        file << lienHe.getInfoAsString() << std::endl;
    }

    file.close();
}

void QuanLyContact::thayDoiThongTinLienHe()
{
    int id;
    std::cout << "ID: ";
    std::cin >> id;

    auto it = std::find_if(danhBa.begin(), danhBa.end(), [id](Contact &contact)
                           { return contact.getID() == id; });

    if (it != danhBa.end())
    {
        // Thực hiện thay đổi thông tin
        std::string newName;
        int newPhoneNumber;
        std::string newEmail;
        std::string newAddress;

        std::cout << "Enter info:" << std::endl;

        std::cout << "New Name: ";
        std::cin.ignore();
        std::getline(std::cin, newName);

        std::cout << "New Phone: ";
        std::cin >> newPhoneNumber;

        std::cout << "New Email: ";
        std::cin >> newEmail;

        std::cout << "New Address: ";
        std::cin.ignore();
        std::getline(std::cin, newAddress);

        // Áp dụng thay đổi
        it->setName(newName);
        it->setPhoneNumber(newPhoneNumber);
        it->setEmail(newEmail);
        it->setAddress(newAddress);

        ghiDanhBaVaoFile();
        std::cout << "Update Success." << std::endl;
    }
    else
    {
        std::cout << "ID does not exits " << id << std::endl;
    }
}

void QuanLyContact::xoaContact()
{
    int id;
    std::cout << "Enter ID remove ";
    std::cin >> id;

    auto it = std::remove_if(danhBa.begin(), danhBa.end(), [id](Contact &contact)
                             { return contact.getID() == id; });

    if (it != danhBa.end())
    {
        danhBa.erase(it, danhBa.end());
        ghiDanhBaVaoFile();
        std::cout << "Remove success" << std::endl;
    }
    else
    {
        std::cout << "ID does not exits " << id << std::endl;
    }
}
void QuanLyContact::thongKeDanhBa()
{
    std::cout << "Number Contact: " << danhBa.size() << std::endl;
}

void QuanLyContact::saoLuuDuLieu()
{

    bool suDungNgayThang = true;
    // Tạo tên file sao lưu có chứa ngày tháng và thời gian (nếu được yêu cầu)
    std::string tenFileSaoLuu = "../backup/backup_danhba.csv";

    if (suDungNgayThang)
    {
        // Lấy thời gian hiện tại
        auto now = std::chrono::system_clock::now();
        std::time_t time = std::chrono::system_clock::to_time_t(now);

        // Định dạng thời gian thành chuỗi ngày tháng và thời gian
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time), "%Y-%m-%d_%H-%M-%S");
        std::string ngayThangThoiGian = ss.str();

        // Thêm ngày tháng và thời gian vào tên file
        tenFileSaoLuu = "../backup/danhba_" + ngayThangThoiGian + ".csv";
    }

    std::ofstream fileBackup(tenFileSaoLuu);

    if (!fileBackup.is_open())
    {
        std::cerr << "Khong the mo file " << tenFileSaoLuu << " để sao lưu." << std::endl;
        return;
    }

    for (auto &lienHe : danhBa)
    {
        fileBackup << lienHe.getInfoAsString() << std::endl;
    }

    fileBackup.close();
    std::cout << "Data dc sao luu vao file " << tenFileSaoLuu << "." << std::endl;
}

//     void khoiPhucDuLieu() {
//         danhBa.clear();
//         readContactsFromFile();
//         std::cout << "Dữ liệu đã được khôi phục từ file danhba.csv." << std::endl;
//     }
void QuanLyContact::dongBoBanSao(const std::string &tenTepBackup)
{
    // Mở tệp tin backup để đọc
    std::ifstream fileBackup(tenTepBackup, std::ios::binary);
    if (!fileBackup.is_open())
    {
        std::cerr << "Khong the mo file backup de doc." << std::endl;
        return;
    }

    // Mở tệp tin gốc để ghi
    std::ofstream fileGoc("../data/danhba.csv", std::ios::binary);
    if (!fileGoc.is_open())
    {
        std::cerr << "Khong the mo file goc de ghi." << std::endl;
        return;
    }

    // Đọc từ tệp tin backup và ghi vào tệp tin gốc
    char buffer[1024];
    while (!fileBackup.eof())
    {
        fileBackup.read(buffer, sizeof(buffer));
        fileGoc.write(buffer, fileBackup.gcount());
    }

    // Đóng tệp tin
    fileBackup.close();
    fileGoc.close();

    std::cout << "Dong bo thanh cong." << std::endl;
}

void QuanLyContact::khoiPhucDuLieu()
{
    std::string tenThuMuc = "../backup";
    vector<string> list_backup;

    // Kiểm tra sự tồn tại của thư mục
    if (GetFileAttributesA(tenThuMuc.c_str()) != INVALID_FILE_ATTRIBUTES)
    {
        std::cout << "Folder ton tai." << std::endl;

        // Duyệt qua tất cả các tệp tin trong thư mục
        WIN32_FIND_DATAA findFileData;
        HANDLE hFind = FindFirstFileA((tenThuMuc + "\\*").c_str(), &findFileData);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0)
                {
                    list_backup.push_back(findFileData.cFileName);
                }
            } while (FindNextFileA(hFind, &findFileData) != 0);

            FindClose(hFind);
        }
    }
    else
    {
        std::cerr << "Backup does not exits." << std::endl;
    }
    for (size_t i = 0; i < list_backup.size(); i++)
    {
        cout << i + 1 << "." << list_backup[i] << endl;
    }

    cout << "So luong file back_up " << list_backup.size();
    cout << "\nChon file back_up restore: ";
    int k;
    cin >> k;
    dongBoBanSao("../backup/" + list_backup[k - 1]);
    readContactsFromFile();
}