//
// Created by Raul on 4/18/2022.
//

#ifndef LAB7_CONSOLE_H
#define LAB7_CONSOLE_H


class Console {
public:
    Console();

    ~Console();

    static void showConsole();

    static void showModifyExpenses();

    static void showIdentifyExpenses();

    static void showCharacteristicExpenses();

    static void showFilterExpenses();

    static int runConsole();
};


#endif //LAB7_CONSOLE_H
