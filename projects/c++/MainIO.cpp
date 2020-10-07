#include "virtIO_t.h"
#include "asciiIO_t.h"
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
                file.Open((const char *)fileName, "w");
                break;
            
            case 2:
            
                cout << "enter your data:" << endl;
                cin >> numData;
                file << numData;
                break;
            
            default:
            
                status = 0;
                break;
            
        }

    }
    
   /*  i << 5;
    try
    {
        i.SetPosition(1);
    }
    catch(int i)
    {
        cout << i <<endl;
    }
    i << 77;
    return 0; */ 


}


/* cout << "write:\n" << endl;
                cin >> numData; 
                file << numData; */
/* char word[80];  // this will hold 79 letters
    cout << "Please enter a word: ";
    cin >> word;
    cout << word; */