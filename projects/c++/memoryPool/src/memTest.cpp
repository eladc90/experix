
#include <iostream>
#include <string.h>
#include "memManager_t.h"
#include "memPage_t.h"
#include "memPool_t.h"




using namespace std;




int main()
{		
	int option;
    char buffer[100];
    char readBuffer[100];
    int status = 1;

    memPool_t *myPool = 0;


	while (status) 
    {
        size_t size = 6;
        size_t byteREs = 0;
        size_t pos = 0;
        size_t bytes = 0;
        char c;

		cout << "Choose option:\n" << endl;
        cout << "1:Create Pool" << endl;
		cout << "2:Read" << endl;
        cout << "3:Write" << endl;
        cout << "4:GetPoolPosition" << endl;
        cout << "5:GetPoolCapacity" << endl;
		cout << "Any another number - stop" << endl;

		cin >>  option;

		switch (option) 
        {
			case 1:
            {
                if(myPool)
                {
                    cout << "you already have a pool " << endl;
                    break;
                }
                cout<<"\ndo you want to enter capcity for page(defualt = 6) y/n?"<< endl;
                cin>> c;

                if(c == 'y')  
                {
                    cout<< "enter page size"<< endl;
                    cin>> size;
                }
                
                myPool = new memPool_t(size);

                cout<<"Pool create! page size = "<< size << "\n\n";

                break;
            }

			case 2:
            {
                if (!myPool)
                {
                    cout<< "error! please create a pool before reading..."<<endl;
                }
                else 
                {
                    pos = myPool->GetPosition();

                    cout << "\nplease insert how much byte you want to read from buffer"<<endl;
                    cin >> bytes;

                    cout<< "\n are you want to read from current pos (y/n)"<<endl;
                    cin >> c;

                    if(c != 'y')
                    {
                        cout<< "please enter a position between 0 - " << myPool->GetActualSize() << endl;
                        cin>> pos;
                    }

                    byteREs = myPool->Read(readBuffer,pos, bytes);
                    if(byteREs != bytes)
                    {
                        cout << "you want to read "<< bytes << 
                        " but function can read only " << byteREs << " bytes" << endl;
                    }
                    else
                    {
                        cout << "read sucsses with "<< byteREs << " bytes"<<endl;
                    }
                    cout << readBuffer << endl;
                }
                break;
            }

            case 3:
            {
                if(!myPool)
                {
                    cout<< "error! please create a pool first"<< endl;
                    break;
                }
                pos = myPool->GetPosition();
                cout<< "\nplease insert how mach byte you want to write to buffer"<<endl;
                cin>> bytes;

                cout<< "\nare you want to write from current pos (y/n)"<<endl;
                cin >> c;

                if(c != 'y')
                {
                    cout<< "please enter a position between 0 - " << myPool->GetActualSize() << endl;
                    cin>> pos;
                }
                cout << "Type:" << endl;
                cin >> buffer;
                byteREs = myPool->Write(buffer,pos,bytes);
                if(byteREs != bytes)
                {
                    cout << "you want to write "<< bytes << 
                    " but function can write only " << byteREs << " bytes" << endl;
                }
                else
                {
                    cout << "write sucsses with "<< byteREs << " bytes"<<endl;
                }
                
                break;
            }
            
            case 4:
            {
                if(!myPool)
                {
                    cout<< "error! please create a pool first"<< endl;
                    break;
                }
                cout<< "position = " << myPool->GetPosition() << endl;

                break;
            }

            case 5:
            {

                if(!myPool)
                {
                    cout<< "error! please create a pool first"<< endl;
                    break;
                }

                cout<< myPool -> GetPoolCapacity() << endl; 
                break;

            }
			default:
            {
                status = 0;	
                break;
            }
		
        }
	}
	
    return 0;
}


