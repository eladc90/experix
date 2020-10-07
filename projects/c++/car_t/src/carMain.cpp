#include "../include/car_t.h"
#include "../include/private.h"
#include <iostream> 
#include <stdio.h>
#include <string>
#include <bits/stdc++.h> 
using namespace std;

int main()
{
    int test = 1;
    unsigned int option;
    private_t p1;
    private_t p2;
    string gear = p1.GetGear();
    string name = p1.GetName();
    while(test)
    {
        cout << "Choose option: " << endl;
		cout << "1: get name  " << endl;
		cout << "2: get id    " << endl;
		cout << "3: get capacity   " << endl;
        cout << "4: get gear   " << endl;
        cout << "5: get default capacity   " << endl;
		cout << "Any another number - stop " << endl;
        cin >>  option;

        switch (option) 
        {
			case 1:
				cout <<  p1.GetName() << endl; 
                break;
			case 2:
				cout << p1.GetId() << endl;	
                break;
			case 3:
				cout << p1.GetCapacity() << endl;	
                break;
            case 4:
				cout << p1.GetGear() << endl;	
                break;
            case 5:
				cout << p1.GetDefaultCapacity() << endl;	
                break;

			default:
              test = 0;	
              break;
		}
    }
    return 0;
}
