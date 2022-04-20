//
// Created by Raul on 4/14/2022.
//

#include "../Repository/Repository.h"
#include "../Headers/UndoOperation.h"

#ifndef LAB7_SERVICE_H
#define LAB7_SERVICE_H


class Service {
private:
    Repository<Expense> repo;
    UndoOperation<Expense> undoOperation;
public:

    Service();
    explicit Service(const Repository<Expense>&, const UndoOperation<Expense>&);
    Service(Service&);

    ~Service();

    Repository<Expense> getRepository();

    void setRepo(const Repository<Expense> &);

    void create(int, int,char*);

    Repository<Expense> read();

    void update(int, int, char*);

    void deleteForOneApartment(int);

    void deleteIntervalOfApartments(int, int);

    void deleteForOneType(char*);

    Repository<Expense> listExpensesForOneApartment(int);

    Repository<Expense> listExpensesOverSum(int);

    Repository<Expense> listExpensesEqualToSum(int);

    int sumForType(char*);

    Expense biggestExpenseForApartment(int);

    void filterExpensesByType(char*);

    void filterExpensesLessThenSum(int);

    int do_undo();

};


#endif //LAB7_SERVICE_H
