#include "exHand.h"
#include <iostream>

int func(int _num);

int main()
{
    
    int test = 3;
    int testNot3 = 9;
    TExeption<int>( 0, __FILE__, __LINE__);
    try
    {
        func(test);
    }
    catch(TExeption<int> e)
    {
        cout << e.GetDescription() << endl;
        cout << e.GetFile() << endl;
        cout << e.GetLine() << endl;
        cout << e.GetExe() << endl;
    }

    try
    {
        func(testNot3);
    }
    catch(TExeption<int> e)
    {
        cout << e.GetDescription() << endl;
        cout << e.GetFile() << endl;
        cout << e.GetLine() << endl;
        cout << e.GetExe() << endl;
    }
}



int func(int _num)
{
    if (_num == 3)
    {
        throw TExeption<int>(50, __FILE__, __LINE__); 
    }
    else
    {
        throw TExeption<int>(22, __FILE__, __LINE__);
    }
    
}