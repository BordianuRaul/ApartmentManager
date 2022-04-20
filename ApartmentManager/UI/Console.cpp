//
// Created by Raul on 4/18/2022.
//

#include "Console.h"
#include <iostream>
#include "../Service/Service.h"

using namespace std;

Console::Console() = default;

Console::~Console() = default;

void Console::showConsole() {

    cout << "1.Adaugare cheltuiala." << endl;
    cout << "2.Modificare cheltuieli." << endl;
    cout << "3.Identificare cheltuieli." << endl;
    cout << "4.Obitenere caracteristici despre cheltuieli." << endl;
    cout << "5.Filtrare cheltuieli." << endl;
    cout << "6.Undo." << endl;
    cout << "0.Iesire din program." << endl;

}

void Console::showModifyExpenses() {

    cout << "1.Eliminare cheltuieli pentru un apartament." << endl;
    cout << "2.Eliminare cheltuieli pentru un interval de apartament." << endl;
    cout << "3.Eliminare chelutieli pentru un anumit tip[gaz/apa]" << endl;
    cout << "4.Inlocuire suma pentru cheltuiala unui apartament" << endl;
    cout << "0.Revenire la panoul principal." << endl;

}

void Console::showIdentifyExpenses() {
    cout << "1.Listeaza toate cheltuielile din lista." << endl;
    cout << "2.Listeaza toate cheltuielile unui apartament." << endl;
    cout << "3.Listeaza toate cheltuielile cu valoarea mai mare decat n." << endl;
    cout << "4.Listeaza toate cheltuielile de o anumita valoare." << endl;
    cout << "0.Revenire la panoul principal." << endl;
}

void Console::showCharacteristicExpenses() {
    cout << "1.Aiseaza suma totala pentru un timp de cheltuaiala[gaz/apa]."<<endl;
    cout << "2.Afiseaza cea mai valoroasa cheltuiala a unui apartament."<<endl;
    cout << "0.Revenire la panoul principal."<<endl;
}

void Console::showFilterExpenses() {
    cout << "1.Filtreaza dupa un anumit tip de cheltuiala [apa/gaz]." << endl;
    cout << "2.Filtreaza toate cheltuielile cu valoarea mai mica decat o suma n." << endl;
    cout << "Revenire la panoul principal." << endl;
}

int Console::runConsole() {

    auto* expenses = new Expense[1];

    Repository<Expense> repo(expenses, 1, 0);
    UndoOperation<Expense> undoOperation;
    Service expensesService(repo, undoOperation);


    while(true){

        showConsole();

        int option;
        cout << "Introduceti optiunea: ";
        cin >> option;
        cout << endl;

        switch(option){

            case 0: return 0;
            case 1:{

                int apartmentNumber;
                int sum;
                char* type = new char[4];

                cout << "Introduceti numarul apartamentului: ";
                cin>> apartmentNumber;
                cout << endl;

                cout << "Introduceti suma cheltuielii: ";
                cin >> sum;
                cout << endl;

                cout << "Introduceti tipul cheltuielii [gaz/apa]: ";
                cin >> type;
                cout << endl;

                expensesService.create(apartmentNumber, sum, type);
                cout << "Cheltuiala s-a adaugat cu succes!" << endl;
                break;
            }
            case 2:
            {
                while(true){
                    showModifyExpenses();

                    int modifyOption;

                    cout << "Introduceti opiunea: ";

                    cin >> modifyOption;

                    if (modifyOption == 0)
                        break;

                    cout << endl;

                    switch(modifyOption){
                        case 1:{
                            int apartmentNumber;

                            cout << "Introduceti numarul apartamentului: ";
                            cin >>apartmentNumber;
                            cout << endl;
                            expensesService.deleteForOneApartment(apartmentNumber);
                            cout << "Stergerea s-a efectuat cu succes" << endl;
                            break;
                        }
                        case 2:{
                            int firstApartment;
                            int secondApartment;

                            cout << "Introduceti numarul primului apartament: ";
                            cin >> firstApartment;
                            cout << endl << "Introduceti numarul celui de al doilea apartament: ";
                            cin>> secondApartment;
                            cout << endl;

                            expensesService.deleteIntervalOfApartments(firstApartment, secondApartment);
                            cout << "Stergerea s-a efectuat cu succes" << endl;

                            break;

                        }

                        case 3:{
                            char* type = new char[4];

                            cout << "Introduceti tipul de cheltuiala pe care doriti sa il stergeti[gaz/apa]: ";
                            cin >> type;
                            cout << endl;
                            expensesService.deleteForOneType(type);

                            break;

                        }

                        case 4:{
                            int apartmentNumber;
                            int sum;
                            char* type = new char[4];

                            cout << "Introduceti numarul apartamentului: ";
                            cin >> apartmentNumber;
                            cout << endl;

                            cout << "Introduceti tipul de cheltuiala: ";
                            cin >> type;
                            cout << endl;

                            cout << "Introduceti noua suma: ";
                            cin >> sum;
                            cout << endl;

                            expensesService.update(apartmentNumber, sum, type);
                            break;
                        }
                        default: break;
                    }
                }
                break;
            }
            case 3:{
                while(true)
                {
                    int identifyOption;

                    showIdentifyExpenses();

                    cout << "Introduceti optiunea: ";
                    cin >> identifyOption;
                    cout << endl;

                    if (identifyOption == 0)
                        break;

                    switch (identifyOption) {
                        case 1:{
                            Repository<Expense> allExpenses;
                            allExpenses = expensesService.read();


                            for ( int i = 0; i < allExpenses.getNumberOfEntities(); i ++)
                                cout << allExpenses.getEntities()[i] << endl;

                            break;
                        }

                        case 2:{

                            int apartmentNumber;
                            cout << "Introduceti numarul apartamentului: ";
                            cin >> apartmentNumber;
                            cout << endl;

                            Repository<Expense> allExpenses;
                            allExpenses = expensesService.listExpensesForOneApartment(apartmentNumber);

                            for (int i = 0; i < allExpenses.getNumberOfEntities(); i++)
                                cout << allExpenses.getEntities()[i] << endl;

                            break;

                        }

                        case 3:{

                            int sum;
                            cout << "Introduceti suma: ";
                            cin >> sum;
                            cout << endl;

                            Repository<Expense> allExpenses;
                            allExpenses = expensesService.listExpensesForOneApartment(sum);

                            for (int i = 0; i < allExpenses.getNumberOfEntities(); i++)
                                cout << allExpenses.getEntities()[i] << endl;

                            break;
                        }

                        case 4:{

                            int sum;
                            cout << "Introduceti suma: ";
                            cin >> sum;
                            cout << endl;

                            Repository<Expense> allExpenses;
                            allExpenses = expensesService.listExpensesForOneApartment(sum);

                            for (int i = 0; i < allExpenses.getNumberOfEntities(); i++)
                                cout << allExpenses.getEntities()[i] << endl;

                            break;
                        }
                        default: break;

                    }
                }
                break;

            }
            case 4:{
                while(true)
                {
                    int characteristicOption;

                    showCharacteristicExpenses();
                    cout << "Introduceti optiunea:";
                    cin >> characteristicOption;
                    cout << endl;

                    if (characteristicOption == 0)
                        break;

                    switch (characteristicOption) {
                        case 1:{
                            char* type = new char[4];

                            cout << "Introduceti tipul cheltuielii [gaz/apa]: ";
                            cin >> type;
                            cout << endl;

                            int totalSum;
                            totalSum = expensesService.sumForType(type);
                            cout << "Suma totala este: " << totalSum << endl;

                            break;
                        }
                        case 2:{
                            int apartmentNumber;

                            cout << "Introduceti numarul apartamentului: ";
                            cin >> apartmentNumber;
                            cout << endl;

                            Expense biggestExpense;
                            biggestExpense = expensesService.biggestExpenseForApartment(apartmentNumber);

                            cout << "Cea mai mare cheltuiala este: " << biggestExpense << endl;

                            break;
                        }
                        default: break;

                    }
                }
                break;
            }
            case 5:{
                while(true){

                    int filterOption;

                    showFilterExpenses();

                    cout << "Introduceti optiunea ";
                    cin >> filterOption;
                    cout << endl;

                    if(filterOption == 0)
                        break;

                    if(filterOption == 1)
                    {
                        char* type = new char[4];

                        cout <<"Introduceti tipul cheltuielii [gaz/apa]: ";
                        cin >> type;
                        cout << endl;

                        expensesService.filterExpensesByType(type);
                        cout << "Filtrarea s-a efectuat cu succes" << endl;
                    }else {
                        if (option == 2)
                        {
                            int sum;

                            cout << "Introduceti suma: ";
                            cin >> sum;
                            cout << endl;

                            expensesService.filterExpensesLessThenSum(sum);
                            cout << "Filtrarea s-a efectuat cu succes" << endl;
                        }
                    }
                }
                break;
            }
            case 6:{
                expensesService.do_undo();
                cout << "Undo s-a efectuat cu succes." << endl;
                break;
            }

            default : return 0;
        }


    }

}