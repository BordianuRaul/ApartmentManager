//
// Created by Raul on 4/6/2022.
//

#ifndef LAB7_EXPENSE_H
#define LAB7_EXPENSE_H


#include <ostream>

class Expense {
private:
    int apartmentNumber;
    int sum;
    char* type;
public:
    Expense();
    Expense(int, int, char*);
    Expense(const Expense&);

    ~Expense();

    void setApartmentNumber(int);

    void setSum(int);

    void setType(char*);

    int getApartmentNumber() const;

    int getSum() const;

    char* getType() const;

    Expense& operator=(const Expense&);

    bool operator==(const Expense &rhs) const;

    bool operator!=(const Expense &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Expense &expense);

    bool operator<(const Expense &rhs) const;

    bool operator>(const Expense &rhs) const;

    bool operator<=(const Expense &rhs) const;

    bool operator>=(const Expense &rhs) const;

};

#endif //LAB7_EXPENSE_H
