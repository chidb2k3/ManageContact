#ifndef CONTACT_H
#define CONTACT_H
#include <iostream>
using namespace std;
class Contact
{
private:
    int id;
    string name;
    int phoneNumber;
    string email;
    string address;
public:
    Contact(int _id, const  string& _name, int _phoneNumber, const  string& _email, const string& _address);
    string getInfoAsString() const;
    int getID();
    void setID(int id);
    string getName();
    void setName(string name);
    int getSDT();
    void setPhoneNumber(int sDT);
    string getEmail();
    void setEmail(string email);
    string getAddress();
    void setAddress(string address);
};
#endif
