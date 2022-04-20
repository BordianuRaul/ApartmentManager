//
// Created by Raul on 4/6/2022.
//

#include "../Headers/Expense.h"
#include <cstring>
#include <iostream>

Expense::Expense() {
    this->apartmentNumber = -1;
    this->sum = 0;
    this->type = nullptr;
}

Expense::Expense(int paramApartmentNumber, int paramSum, char* paramType) {
    this->apartmentNumber = paramApartmentNumber;
    this->sum = paramSum;
    this->type = new char[strlen(paramType) + 1];
    strcpy_s(this->type, strlen(paramType) + 1 ,paramType);


}
Expense::Expense(const Expense& paramEntity) {
    this->apartmentNumber = paramEntity.apartmentNumber;
    this->sum = paramEntity.sum;
    this->type = new char[strlen(paramEntity.getType()) + 1];
    strcpy_s(this->type, strlen(paramEntity.getType()) + 1 ,paramEntity.getType());
}

Expense::~Expense() {
    this->apartmentNumber = 0;
    this->sum = 0;
    delete[] this->type;
    this->type = nullptr;
}

void Expense::setApartmentNumber(int paramApartmentNumber){
    this->apartmentNumber = paramApartmentNumber;
}

void Expense::setSum(int paramSum) {
    this->sum = paramSum;
}

void Expense::setType(char* paramType) {

    if(this->type != nullptr) {
        delete[] type;
        this->type= nullptr;
    }
    this->type = new char[strlen(paramType) + 1];
    strcpy_s(this->type, strlen(paramType) + 1 ,paramType);
}

int Expense::getApartmentNumber() const {
    return apartmentNumber;
}

int Expense::getSum() const {
    return this->sum;
}

char* Expense::getType() const{
    return this->type;

}


Expense& Expense::operator=(const Expense& paramEntity){

    if (this != &paramEntity) {
        setApartmentNumber(paramEntity.apartmentNumber);
        setSum(paramEntity.sum);
        setType(paramEntity.type);
    }

    return *this;
}

bool Expense::operator==(const Expense &rhs) const {
    return apartmentNumber == rhs.apartmentNumber &&
           sum == rhs.sum &&
           strcmp(this->type, rhs.type) == 0;
}

bool Expense::operator!=(const Expense &rhs) const {
    return apartmentNumber != rhs.apartmentNumber &&
           sum != rhs.sum &&
           strcmp(this->type, rhs.type) != 0;
}

std::ostream &operator<<(std::ostream &os, const Expense &expense) {
    os << "Numarul apartamentului: " << expense.apartmentNumber << std::endl
    << "Suma: " << expense.sum << std::endl
    << "Tipul: " << expense.type << std::endl;
    return os;
}

bool Expense::operator<(const Expense &rhs) const {
    if (apartmentNumber < rhs.apartmentNumber)
        return true;
    if (rhs.apartmentNumber < apartmentNumber)
        return false;
    if (sum < rhs.sum)
        return true;
    if (rhs.sum < sum)
        return false;
    return type < rhs.type;
}

bool Expense::operator>(const Expense &rhs) const {
    return rhs < *this;
}

bool Expense::operator<=(const Expense &rhs) const {
    return !(rhs < *this);
}

bool Expense::operator>=(const Expense &rhs) const {
    return !(*this < rhs);
}
