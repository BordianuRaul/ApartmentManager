//
// Created by Raul on 4/18/2022.
//

#include <stack>

#ifndef LAB7_UNDOOPERATION_H
#define LAB7_UNDOOPERATION_H

template <class T>
class UndoOperation {
private:

public:
    std::stack<int> typeOfOperation;
    std::stack<std::stack<T>> operations;

    UndoOperation() = default;

    ~UndoOperation(){

        while(!(this->typeOfOperation.empty()))
        {
            this->typeOfOperation.pop();
        }

        while(!(this->operations.empty()))
        {
            this->operations.pop();
        }

    }

    void addOperation(int paramTypeOfOperation, std::stack<T> paramOperation){
        this->typeOfOperation.push(paramTypeOfOperation);
        this->operations.push(paramOperation);
    }

    std::stack<T> deleteOperation(){

        std::stack<T> returnOperations;
        returnOperations = this->operations.top();

        this->typeOfOperation.pop();
        this->operations.pop();

        return returnOperations;
    }
    
};

#endif //LAB7_UNDOOPERATION_H
