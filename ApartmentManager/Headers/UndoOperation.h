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

//    UndoOperation& operator=(const UndoOperation& paramUndoOperation){
//
//        while(!(this->typeOfOperation.empty()))
//        {
//            typeOfOperation.pop();
//        }
//
//        std::stack<int> auxTypeOfOperation;
//
//        while(!(paramUndoOperation.typeOfOperation.empty()))
//        {
//            auxTypeOfOperation.push(paramUndoOperation.typeOfOperation.top());
//            paramUndoOperation.typeOfOperation.pop();
//        }
//
//        while(!(auxTypeOfOperation.empty()))
//        {
//            this->typeOfOperation.push(auxTypeOfOperation.top());
//            auxTypeOfOperation.pop();
//        }
//
//        while(!(this->operations.empty()))
//        {
//            this->operations.pop();
//        }
//
//        std::stack<T> auxOperations;
//
//        while(!(paramUndoOperation.operations.empty()))
//        {
//            auxOperations.push(paramUndoOperation.operations.top());
//            paramUndoOperation.operations.pop();
//        }
//
//        while(!(auxOperations.empty()))
//        {
//            this->operations.push(auxOperations.top());
//            auxOperations.pop();
//        }
//
//        return *this;
//
//    }

};

#endif //LAB7_UNDOOPERATION_H
