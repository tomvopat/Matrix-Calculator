//
// Created by Tomáš Vopat on 30.04.18.
//

#include "Test1.h"
#include "Test2.h"
#include "Test3.h"
#include "Test4.h"
#include "Test5.h"

int test() {
    test1();
    test2();
    test3();
    test4();
    test5();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}