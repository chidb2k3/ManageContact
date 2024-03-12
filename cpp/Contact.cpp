#include "../header/Contact.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

Contact::Contact(int _id, const  string& _name, int _phoneNumber, const  string& _email, const std::string& _address)
        : id(_id), name(_name), phoneNumber(_phoneNumber), email(_email), address(_address) {}
string Contact::getInfoAsString() const {
        stringstream ss;
        ss << id << "|" << name << "|" << phoneNumber << "|" << email << "|" << address;
        return ss.str();
}
int Contact::getID(){
    return this->id;
}
void Contact::setID(int id){
    this->id = id;
}
string Contact::getName(){
    return this->name;
}
void Contact::setName(string name){
    this->name = name;
}
int Contact::getSDT(){
    return this->phoneNumber;
}
void Contact::setPhoneNumber(int sDT){
    this->phoneNumber= sDT;
}
string Contact::getEmail(){
    return this->email;
}
void Contact::setEmail(string email){
    this->email = email;
}
string Contact::getAddress(){
    return this->address;
}
void Contact::setAddress(string address){
    this->address = address;
}