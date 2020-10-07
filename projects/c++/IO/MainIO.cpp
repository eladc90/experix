#include "virtIO_t.h"
#include "asciiIO_t.h"
#include "binIO_t.h"
#include <iostream>
using namespace std;

int main()
{
 
    int option;
    int status = 1;
    char *fileName = new char[100];
    char data[100];
    int numData = 0;
    asciiIO_t file;
    binIO_t Bfile;
    while (status)
    {
        cout << "Choose option:\n" << endl;
        cout << "1:create ascii file" << endl;
        cout << "2:write to file" << endl;

        cin >>  option;
        switch (option) 
        {
            case 1:
            
                cout << "Choose file name:\n" << endl;
                cin >> fileName;
                try
                {
                    file.Open((const char *)fileName, "w");
                }
                catch(TExeption<int> i)
                {
                    cout << i.GetDescription() << endl;
                }
                break;
            
            case 2:
            
                cout << "enter your data:" << endl;
                cin >> numData;
                file >> numData;
                break;
            
            default:
            
                status = 0;
                break;
            
        }

    }
    

}


