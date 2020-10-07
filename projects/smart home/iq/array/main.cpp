#include <vector>
#include "funs.hpp"


void FillVec(std::vector<int>& a_vec, size_t a_numOfVals) {
    while (--a_numOfVals) {
        int valEnter = rand() % 100000;
        a_vec.push_back(valEnter);
    }
}

int main () {
    std::vector<TestClass> vecClass;
    TestClass class1(1);
    TestClass class2(2);
    TestClass class3(3);
    TestClass class4(6);
    TestClass class5(8);
    TestClass class6(1);
    TestClass class7(5);
    TestClass class8(3);
    vecClass.push_back(class1);
    vecClass.push_back(class2);
    vecClass.push_back(class3);
    vecClass.push_back(class4);
    vecClass.push_back(class5);
    vecClass.push_back(class6);
    vecClass.push_back(class7);
    vecClass.push_back(class8);
    TestClass class9 = findFirstUniq(vecClass);
    
    class9.Print();
   
    std::vector<int> vec;
    std::vector<int> vecCheck;
    FillVec(vec, 1000);
    std::cout << findFirstUniq(vec) << std::endl;
    vecCheck.push_back(1);
    vecCheck.push_back(2);
    vecCheck.push_back(3);
    vecCheck.push_back(3);
    vecCheck.push_back(3);
    vecCheck.push_back(3);
    vecCheck.push_back(1);
    vecCheck.push_back(3);
    std::cout << findFirstUniq(vecCheck) << std::endl;
    return 0;
}