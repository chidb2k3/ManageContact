#include "../header/Contact.h"
#include "../header/QuanLyContact.h"
using namespace std;
int main()
{

    QuanLyContact quanLyDanhBa("../data/danhba.csv");

    int luaChon;
    do
    {
        std::cout << "\n----- MENU -----" << std::endl;
        std::cout << "1. Display contact information" << std::endl;
        std::cout << "2. Add a contact to the address book" << std::endl;
        std::cout << "3. Find a contact by name" << std::endl;
        std::cout << "4. Modify information of a contact in the address book" << std::endl;
        std::cout << "5. Remove a contact from the address book" << std::endl;
        std::cout << "6. Statistics: Number of contacts in the address book" << std::endl;
        std::cout << "7. Backup data" << std::endl;
        std::cout << "8. Restore data" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "-----------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> luaChon;

        switch (luaChon)
        {
        case 1:
            quanLyDanhBa.hienThiDanhBa();
            break;
        case 2:
            quanLyDanhBa.themLienHe();
            break;
        case 3:
            quanLyDanhBa.timContactTheoTen();
            break;
        case 4:
            quanLyDanhBa.thayDoiThongTinLienHe();
            break;
        case 5:
            quanLyDanhBa.xoaContact();
            break;
        case 6:
            quanLyDanhBa.thongKeDanhBa();
            break;
        case 7:
            quanLyDanhBa.saoLuuDuLieu();
            break;
        case 8:
            quanLyDanhBa.khoiPhucDuLieu();
            break;
        case 0:
            std::cout << "Exit" << std::endl;
            break;
        default:
            std::cout << "Select no valid. please select again" << std::endl;
        }

    } while (luaChon != 0);

    return 0;
}