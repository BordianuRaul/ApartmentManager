//
// Created by Raul on 4/14/2022.
//

#include "Service.h"
#include <cstring>
#include <stack>

Service::Service()= default;

Service::Service(const Repository<Expense> &paramRepo, const UndoOperation<Expense> &paramUndoOperation) {

    this->repo = paramRepo;

}

Service::Service(Service &paramService) {

    this->repo = paramService.repo;

}

Service::~Service() = default;

Repository<Expense> Service::getRepository() {

    return this->repo;

}

void Service::setRepo(const Repository<Expense> &paramRepo) {

    this->repo = paramRepo;

}

void Service::create(int paramApartmentNumber, int paramSum, char* paramType) {

    Expense expense;
    expense.setApartmentNumber(paramApartmentNumber);
    expense.setSum(paramSum);
    expense.setType(paramType);

    this->repo.addElem(expense);
    //Undo
    this->undoOperation.typeOfOperation.push(1);
    std::stack<Expense> addExpense;
    addExpense.push(expense);
    this->undoOperation.operations.push(addExpense);

}

Repository<Expense> Service::read() {

    return this->repo;
}

void Service::update(int paramApartmentNumber, int paramSum, char* paramType) {

    int numberOfExpenses;
    numberOfExpenses = repo.numberOfEntities;
    numberOfExpenses --;

    while(numberOfExpenses >= 0)
    {
        if(this->repo.entities[numberOfExpenses].getApartmentNumber() == paramApartmentNumber)

            if(strcmp(this->repo.entities[numberOfExpenses].getType(), paramType) == 0)
            {
                //Undo
                Expense initialExpense(paramApartmentNumber, this->repo.entities[numberOfExpenses].getSum(),
                                       paramType);
                this->undoOperation.typeOfOperation.push(3);
                std::stack<Expense> addExpense;
                addExpense.push(initialExpense);
                this->undoOperation.operations.push(addExpense);
                //Undo
                this->repo.entities[numberOfExpenses].setSum(paramSum);
                break;
            }

        numberOfExpenses--;
    }

}

void Service::deleteForOneApartment(int paramApartmentNumber) {

    Expense* expenses = this->repo.getEntities();
    int numberOfExpenses = this->repo.numberOfEntities;

    std::stack<Expense> addExpenses;

    for(int i = 0; i < numberOfExpenses; i++)
    {
        if(expenses[i].getApartmentNumber() == paramApartmentNumber) {

            addExpenses.push(expenses[i]);
            this->repo.deleteElem(expenses[i]);
            i--;
            numberOfExpenses--;
        }

    }

    if(!addExpenses.empty())
    {
        this->undoOperation.typeOfOperation.push(2);
        this->undoOperation.operations.push(addExpenses);
    }

}

void Service::deleteIntervalOfApartments(int firstApartment, int lastApartment) {

    Expense* expenses = this->repo.entities;
    int numberOfExpenses = this->repo.numberOfEntities;

    std::stack<Expense> addExpenses;

    for(int i = 0; i < numberOfExpenses; i++)
    {
        int auxApartmentNumber = expenses[i].getApartmentNumber();
        if(auxApartmentNumber >= firstApartment && auxApartmentNumber <= lastApartment) {
            addExpenses.push(expenses[i]);
            this->repo.deleteElem(expenses[i]);
            i--;
            numberOfExpenses--;
        }

    }
    if(!addExpenses.empty())
    {
        this->undoOperation.typeOfOperation.push(2);
        this->undoOperation.operations.push(addExpenses);
    }
}

void Service::deleteForOneType(char* paramType){

    int numberOfExpenses = this->repo.numberOfEntities;

    std::stack<Expense> addExpenses;

    for(int i = 0; i < numberOfExpenses; i++)
    {

        if(strcmp(this->repo.entities[i].getType(), paramType) == 0) {
            addExpenses.push(this->repo.entities[i]);
            this->repo.deleteElem(this->repo.entities[i]);
            i--;
            numberOfExpenses--;
        }

    }

    if(!addExpenses.empty())
    {
        this->undoOperation.typeOfOperation.push(2);
        this->undoOperation.operations.push(addExpenses);
    }

}

Repository<Expense> Service::listExpensesForOneApartment(int paramApartmentNumber) {

    int expensesCapacity = 1;
    int numberOfExpenses = 0;
    auto* expenses = new Expense[expensesCapacity];

    int numberOfEntities = this->repo.numberOfEntities;

    for(int  i = 0; i < numberOfEntities; i++)
    {

        if(this->repo.entities[i].getApartmentNumber() == paramApartmentNumber)
        {
            if(numberOfExpenses >= expensesCapacity)
            {
                expensesCapacity *= 2;
                auto* aux = new Expense[expensesCapacity];
                for (int j = 0; j < numberOfExpenses; j++)
                    aux[j] = expenses[j];
                delete[] expenses;
                expenses = aux;
            }
            expenses[numberOfExpenses] = repo.entities[i];
            numberOfExpenses++;
        }

    }

    Repository<Expense> expensesForOneApartment(expenses, expensesCapacity,
                                                numberOfExpenses);

    delete[] expenses;

    return expensesForOneApartment;
}

Repository<Expense> Service::listExpensesOverSum(int paramSum) {

    int expensesCapacity = 1;
    int numberOfExpenses = 0;
    auto* expenses = new Expense[expensesCapacity];

    int numberOfEntities = this->repo.numberOfEntities;

    for(int  i = 0; i < numberOfEntities; i++)
    {

        if(this->repo.entities[i].getSum() > paramSum)
        {
            if(numberOfExpenses >= expensesCapacity)
            {
                expensesCapacity *= 2;
                auto* aux = new Expense[expensesCapacity];
                for (int j = 0; j < numberOfExpenses; j++)
                    aux[j] = expenses[j];
                delete[] expenses;
                expenses = aux;
            }
            expenses[numberOfExpenses] = repo.entities[i];
            numberOfExpenses++;
        }

    }

    Repository<Expense> expensesOverSum(expenses, expensesCapacity,
                                                numberOfExpenses);

    delete[] expenses;

    return expensesOverSum;

}

Repository<Expense> Service::listExpensesEqualToSum(int paramSum) {

    int expensesCapacity = 1;
    int numberOfExpenses = 0;
    auto* expenses = new Expense[expensesCapacity];

    int numberOfEntities = this->repo.numberOfEntities;

    for(int  i = 0; i < numberOfEntities; i++)
    {

        if(this->repo.entities[i].getSum() == paramSum)
        {
            if(numberOfExpenses >= expensesCapacity)
            {
                expensesCapacity *= 2;
                auto* aux = new Expense[expensesCapacity];
                for (int j = 0; j < numberOfExpenses; j++)
                    aux[j] = expenses[j];
                delete[] expenses;
                expenses = aux;
            }
            expenses[numberOfExpenses] = repo.entities[i];
            numberOfExpenses++;
        }

    }

    Repository<Expense> expensesEqualToSum(expenses, expensesCapacity,
                                        numberOfExpenses);

    delete[] expenses;

    return expensesEqualToSum;

}

int Service::sumForType(char* paramType) {

    int sumForType = 0;
    int numberOfExpenses = this->repo.numberOfEntities;
    for(int i = 0; i < numberOfExpenses; i++)
    {
        if(strcmp(this->repo.entities[i].getType(), paramType) == 0)
            sumForType += this->repo.entities[i].getSum();
    }

    return sumForType;
}

Expense Service::biggestExpenseForApartment(int paramApartmentNumber) {

    Expense biggestExpense;

    int numberOfExpenses = this->repo.numberOfEntities;
    for(int i = 0; i < numberOfExpenses; i++)
    {
        if(this->repo.entities[i].getApartmentNumber() == paramApartmentNumber)
        {
            if(this->repo.entities[i].getSum() > biggestExpense.getSum())
                biggestExpense = this->repo.entities[i];
        }
    }

    return biggestExpense;

}

void Service::filterExpensesByType(char *paramType) {

    int numberOfExpenses = this->repo.getNumberOfEntities();

    std::stack<Expense> addExpenses;

    for(int i = 0; i < numberOfExpenses; i++)
    {
        if(strcmp(this->repo.getEntities()[i].getType(), paramType) != 0)
        {
            addExpenses.push(this->repo.getEntities()[i]);
            this->repo.deleteElem(this->repo.getEntities()[i]);
            i--;
            numberOfExpenses--;
        }
    }

    if(!addExpenses.empty())
    {
        this->undoOperation.typeOfOperation.push(2);
        this->undoOperation.operations.push(addExpenses);
    }

}

void Service::filterExpensesLessThenSum(int paramSum) {

    int numberOfExpenses = this->repo.getNumberOfEntities();

    std::stack<Expense> addExpenses;

    for(int i = 0; i < numberOfExpenses; i++)
    {
        if(this->repo.getEntities()[i].getSum() >= paramSum)
        {
            addExpenses.push(this->repo.getEntities()[i]);
            this->repo.deleteElem(this->repo.getEntities()[i]);
            i--;
            numberOfExpenses--;
        }
    }

    if(!addExpenses.empty())
    {
        this->undoOperation.typeOfOperation.push(2);
        this->undoOperation.operations.push(addExpenses);
    }
}

int Service::do_undo() {

    if(!this->undoOperation.operations.empty()) {
        switch (this->undoOperation.typeOfOperation.top()) {
            case 1: {
                Expense deleteExpense;
                deleteExpense = this->undoOperation.operations.top().top();
                this->repo.deleteElem(deleteExpense);

                this->undoOperation.operations.pop();
                this->undoOperation.typeOfOperation.pop();

                break;
            }

            case 2: {
                std::stack<Expense> expenses;
                expenses = this->undoOperation.operations.top();
                while (!expenses.empty()) {
                    Expense toAddExpense;
                    toAddExpense = expenses.top();
                    this->repo.addElem(toAddExpense);
                    expenses.pop();
                }
                this->undoOperation.operations.pop();
                this->undoOperation.typeOfOperation.pop();

                break;
            }
            case 3: {
                Expense updateExpense;
                updateExpense = this->undoOperation.operations.top().top();
                update(updateExpense.getApartmentNumber(), updateExpense.getSum(),
                       updateExpense.getType());

                this->undoOperation.operations.pop();
                this->undoOperation.typeOfOperation.pop();

                break;
            }

            default:
                return 0;
        }
    }

    return 0;
}
