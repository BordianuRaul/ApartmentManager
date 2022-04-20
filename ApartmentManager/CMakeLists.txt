cmake_minimum_required(VERSION 3.21)
project(ApartmentManager)

set(CMAKE_CXX_STANDARD 14)

add_executable(ApartmentManager main.cpp Domain/Expense.cpp Headers/Expense.h Tests/Tests.cpp Headers/Tests.h Repository/Repository.h Service/Service.cpp Service/Service.h Headers/UndoOperation.h UI/Console.cpp UI/Console.h)
