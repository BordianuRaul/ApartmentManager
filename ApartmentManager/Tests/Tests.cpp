//
// Created by Raul on 4/6/2022.
//

#include "../Headers/Tests.h"
#include "../Headers/Expense.h"
#include "../Repository/Repository.h"
#include "../Service/Service.h"
#include "../Headers/UndoOperation.h"
#include <cassert>
#include <cstring>
#include <stack>

using namespace std;


void testExpense()
{
    auto* type = new char[4];
    strcpy(type, "gaz");
    Expense entity(5, 100, type);
    //Getter
    assert(entity.getApartmentNumber() == 5);

    assert(entity.getSum() == 100);

    assert(strcmp(entity.getType(), type) == 0);

    entity.setApartmentNumber(10);
    entity.setSum(120);
    strcpy(type,"apa");
    entity.setType(type);
    //Set-eri
    assert(entity.getApartmentNumber() == 10);

    assert(entity.getSum() == 120);

    assert(strcmp(entity.getType(), "apa") == 0);

    //Operator=
    Expense testEntity;
    testEntity = entity;
    assert(testEntity.getApartmentNumber() == 10);

    assert(testEntity.getSum() == 120);

    assert(strcmp(testEntity.getType(), "apa") == 0);

    delete[] type;

}

void testExpenseSet()
{
    auto* type = new char[4];
    Expense entity;

    strcpy(type,"apa");

    entity.setType(type);
    entity.setApartmentNumber(10);
    entity.setSum(120);
    assert(entity.getApartmentNumber() == 10);

    assert(entity.getSum() == 120);

    assert(strcmp(entity.getType(), "apa") == 0);

    delete[] type;

}

void testConstructorRepo(){

    auto* entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);

    delete[] entities;

}

void testAssigmentRepo(){

    char* type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);
    auto* entities = new Expense[1];
    entities[0] = expense;
    Repository<Expense> repo(entities, 1, 1);
    Repository<Expense> testRepo;
    testRepo = repo;
    assert(testRepo == repo);

    delete[] entities;
    delete[] type;

}

void testGetCapacity(){

    char* type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);
    auto* entities = new Expense[1];
    entities[0] = expense;
    Repository<Expense> repo(entities, 1, 1);

    assert(repo.getCapacity() == 1);

    delete[] entities;
    delete[] type;

}

void testGetNumberOfEntities(){

    char* type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);
    auto* entities = new Expense[1];
    entities[0] = expense;
    Repository<Expense> repo(entities, 1, 1);

    assert(repo.getNumberOfEntities() == 1);

    delete[] entities;
    delete[] type;

}

void testGetEntities(){

    char* type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);
    auto* entities = new Expense[1];
    entities[0] = expense;
    Repository<Expense> repo(entities, 1, 1);

    assert(repo.getEntities()[0]== entities[0]);

    delete[] entities;
    delete[] type;

}

void testAddRepository(){

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);

    Expense entity(3, 100, type);

    repo.addElem(entity);
    repo.addElem(entity);
    assert(repo.getNumberOfEntities() == 2);

    delete[] entities;
    delete[] type;
}

void testGetAllRepository(){

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);

    Expense entity(3, 100, type);

    repo.addElem(entity);

    entity.setApartmentNumber(7);
    repo.addElem(entity);

    strcpy_s(type, 4, "apa");
    entity.setType(type);

    repo.addElem(entity);

    Expense* all_entities;

    all_entities = repo.getAll();

    strcpy_s(type, 4, "gaz");

    Expense compare_entity(3, 100, type);

    assert(all_entities[0] == compare_entity);

    compare_entity.setApartmentNumber(7);
    assert(all_entities[1] == compare_entity);

    strcpy_s(type, 4, "apa");
    compare_entity.setType(type);
    assert(all_entities[2] == compare_entity);

    delete[] entities;
    delete[] type;

}

void testGetSizeRepository()
{
    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    auto *entities = new Expense[10];
    Repository<Expense> repo(entities, 10, 0);

    Expense entity(3, 100, type);
    repo.addElem(entity);

    entity.setApartmentNumber(7);
    repo.addElem(entity);

    entity.setSum(200);
    repo.addElem(entity);

    assert(repo.getSize() == 3);

    delete[] entities;
    delete[] type;
}

void testDeleteElem()
{
    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);

    Expense entity(3, 100, type);

    repo.addElem(entity);
    repo.addElem(entity);

    repo.deleteElem(entity);
    assert(repo.getNumberOfEntities() == 1);

    delete[] entities;
    delete[] type;
}

void testExpenseServiceDefaultConstructor(){

    Service expenseService;

}

void testExpenseServiceConstructor(){

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);
    auto *entities = new Expense[1];
    entities[0] = expense;
    Repository<Expense> repo(entities, 1, 1);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

}

void testExpenseServiceGetRepo(){

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);
    auto *entities = new Expense[1];
    entities[0] = expense;
    Repository<Expense> repo(entities, 1, 1);
    UndoOperation<Expense> undoOperation;

    Service expenseService(repo, undoOperation);

    Repository<Expense> testRepo;
    testRepo = expenseService.getRepository();

    assert(testRepo == repo);

    delete[] entities;
    delete[] type;

}

void testExpenseServiceSetRepo(){

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);
    auto *entities = new Expense[1];
    entities[0] = expense;
    Repository<Expense> repo(entities, 1, 1);

    Repository<Expense> testRepo;
    UndoOperation<Expense> undoOperation;
    Service expenseService(testRepo, undoOperation);

    expenseService.setRepo(repo);

    assert(expenseService.getRepository() == repo);

    delete[] entities;
    delete[] type;

}

void testExpenseServiceCreate(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);

    expenseService.create(1, 100, type);
    expenseService.create(12, 120, type);
    expenseService.create(52, 10, type);

    assert(expenseService.getRepository().getNumberOfEntities() == 3);

    delete[] type;
    delete[] entities;

}

void testExpensesServiceUpdate(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);

    expenseService.create(1, 100, type);

    expenseService.update(1, 200, type);

    expense.setSum(200);

    Expense compareExpense;
    compareExpense = expenseService.getRepository().getEntities()[0];

    assert(compareExpense == expense);

    delete[] entities;
    delete[] type;

}

void testDeleteExpensesForOneForApartment()
{
    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(1, 100, type);

    expenseService.create(11, 200, type);

    strcpy_s(type, 4, "apa");

    expenseService.create(11, 350, type);

    expenseService.deleteForOneApartment(11);

    assert(expenseService.getRepository().getNumberOfEntities() == 1);

    delete[] entities;
    delete[] type;

}

void testDeleteExpensesForIntervalOfApartments(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(1, 100, type);

    expenseService.create(11, 200, type);

    strcpy_s(type, 4, "apa");

    expenseService.create(2, 350, type);

    expenseService.deleteIntervalOfApartments(1, 5);

    assert(expenseService.getRepository().getNumberOfEntities() == 1);

    delete[] entities;
    delete[] type;

}

void testDeleteExpensesForOneType(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(1, 100, type);

    expenseService.create(11, 200, type);

    strcpy_s(type, 4, "apa");

    expenseService.create(2, 350, type);

    strcpy_s(type, 4, "gaz");

    expenseService.deleteForOneType(type);

    assert(expenseService.getRepository().getNumberOfEntities() == 1);

    delete[] entities;
    delete[] type;

}

void testListExpensesForOneApartment(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(1, 100, type);

    expenseService.create(11, 200, type);

    expenseService.create(11, 350, type);

    Repository<Expense> testRepo;

    testRepo = expenseService.listExpensesForOneApartment(11);

    Expense compareExpense(11, 200, type);
    assert(testRepo.getEntities()[0] == compareExpense);

    compareExpense.setSum(350);
    assert(testRepo.getEntities()[1] == compareExpense);

    delete[] entities;
    delete[] type;

}

void testListExpensesOverSum(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(1, 100, type);

    expenseService.create(11, 200, type);

    expenseService.create(11, 350, type);

    Repository<Expense> testRepo;

    testRepo = expenseService.listExpensesOverSum(100);

    Expense compareExpense(11, 200, type);
    assert(testRepo.getEntities()[0] == compareExpense);

    compareExpense.setSum(350);
    assert(testRepo.getEntities()[1] == compareExpense);

    delete[] entities;
    delete[] type;

}

void testListExpensesEqualToSum(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);
    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(1, 100, type);

    expenseService.create(11, 200, type);

    expenseService.create(11, 200, type);

    Repository<Expense> testRepo;

    testRepo = expenseService.listExpensesEqualToSum(200);

    Expense compareExpense(11, 200, type);
    assert(testRepo.getEntities()[0] == compareExpense);

    assert(testRepo.getEntities()[1] == compareExpense);

    delete[] entities;
    delete[] type;

}

void testSumForType(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(1, 100, type);

    expenseService.create(11, 200, type);

    strcpy_s(type, 4, "apa");

    expenseService.create(2, 350, type);

    strcpy_s(type, 4, "gaz");

    int sumForType = 300;

    assert(expenseService.sumForType(type) == sumForType);

    delete[] entities;
    delete[] type;

}

void testBiggestExpenseForApartment()
{

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);
    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(11, 100, type);

    expenseService.create(11, 1500, type);

    strcpy_s(type, 4, "apa");

    expenseService.create(11, 350, type);

    strcpy_s(type, 4, "gaz");

    Expense biggestExpense(11, 1500, type);

    assert(expenseService.biggestExpenseForApartment(11) == biggestExpense);

    delete[] entities;
    delete[] type;

}

void testFilterExpensesByType(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(11, 100, type);

    expenseService.create(11, 1500, type);

    strcpy_s(type, 4, "apa");

    expenseService.create(11, 350, type);

    expenseService.filterExpensesByType(type);

    assert(expenseService.getRepository().getNumberOfEntities() == 1);

    delete[] entities;
    delete[] type;

}

void testFilterExpensesLessThenSum()
{
    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(11, 100, type);

    expenseService.create(11, 1500, type);

    strcpy_s(type, 4, "apa");

    expenseService.create(11, 350, type);

    expenseService.filterExpensesLessThenSum(500);

    assert(expenseService.getRepository().getNumberOfEntities() == 2);

    delete[] entities;
    delete[] type;
}


void testUndoConstructor()
{
    UndoOperation<Repository<Expense>> undoOperation;
}

void testUndoAdd(){

    char* type = new char[4];
    strcpy_s(type, 4, "gaz");

    Expense addExpense(1, 200, type);

    stack<Expense> stackExpenses;

    stackExpenses.push(addExpense);

    UndoOperation<Expense> undoOperation;

    undoOperation.addOperation(1, stackExpenses);

    delete[] type;
}

void testUndoDelete()
{
    char* type = new char[4];
    strcpy_s(type, 4, "gaz");

    Expense addExpense(1, 200, type);

    stack<Expense> stackExpenses;

    stackExpenses.push(addExpense);

    UndoOperation<Expense> undoOperation;

    undoOperation.addOperation(1, stackExpenses);

    Expense compareExpanse;

    compareExpanse = (undoOperation.deleteOperation().top());

    assert(compareExpanse == addExpense);

    delete[] type;
}

void testDoUndoCreate(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");
    Expense expense(1, 100, type);

    expenseService.create(1, 100, type);
    expenseService.create(12, 120, type);
    expenseService.create(52, 10, type);

    expenseService.do_undo();
    expenseService.do_undo();

    assert(expenseService.getRepository().getNumberOfEntities() == 1);

    delete[] type;
    delete[] entities;

}

void testDoUndoDelete(){

    auto *entities = new Expense[1];
    Repository<Expense> repo(entities, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expenseService(repo, undoOperation);

    auto *type = new char[4];
    strcpy_s(type, 4, "gaz");

    expenseService.create(1, 100, type);

    expenseService.create(11, 200, type);

    strcpy_s(type, 4, "apa");

    expenseService.create(11, 350, type);

    expenseService.deleteForOneApartment(11);

    expenseService.do_undo();

    assert(expenseService.getRepository().getNumberOfEntities() == 3);

    delete[] entities;
    delete[] type;

}


void testAll(){

    testExpense();
    testExpenseSet();
    testConstructorRepo();
    testGetCapacity();
    testGetNumberOfEntities();
    testGetEntities();
    testAssigmentRepo();
    testAddRepository();
    testGetAllRepository();
    testGetSizeRepository();
    testDeleteElem();
    testExpenseServiceDefaultConstructor();
    testExpenseServiceConstructor();
    testExpenseServiceGetRepo();
    testExpenseServiceSetRepo();
    testExpenseServiceCreate();
    testExpensesServiceUpdate();
    testDeleteExpensesForOneForApartment();
    testDeleteExpensesForIntervalOfApartments();
    testDeleteExpensesForOneType();
    testListExpensesForOneApartment();
    testListExpensesOverSum();
    testListExpensesEqualToSum();
    testSumForType();
    testBiggestExpenseForApartment();
    testFilterExpensesByType();
    testFilterExpensesLessThenSum();
    testUndoConstructor();
    testUndoAdd();
    testUndoDelete();
    testDoUndoCreate();
}
