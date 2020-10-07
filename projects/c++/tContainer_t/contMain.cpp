

#include "tContainer_t.h"



int main()
{

    int Tempelement = 5;
    int *newElement = 0;
    
    int option;
    int status = 1;
    tContainer_t<int, vector<int *> > cont;
    tContainer_t<int, list<int *> > cont1;
    cout << "Choose option:\n 1: for vector\n 2: for list" << endl;
    cin >>  option;
    if (option == 1)
    {
        tContainer_t<int, vector<int *> > cont;
    }
    else 
    {
        /* cont = cont1; */
    }

     while(status)
    {
        cout << "Choose option:\n" << endl;
        cout << "1:insert element" << endl;
        cout << "2:is empty" << endl;
        cout << "3:size of container" << endl;
        cout << "4:first element" << endl;
        cout << "5:last element" << endl;
        cout << "6:find element by value" << endl;
        cout << "7:remove specific element" << endl;
        cout << "8:remove all elements" << endl;
        cout << "9:remove and delete specific element" << endl;
        cout << "10:remove and delete all elements " << endl;
        cout << "remove and delete specific element" << endl;

        cin >>  option;
        switch (option) 
        {
            case 1:

                cout<<"enter a number to store in the container"<< endl;
                cin>> Tempelement;
                newElement = new int(Tempelement);
                cont.Insert(newElement);

                cout<< "element inserted" << endl;
                break; 

            case 2:

                if (cont.IsEmpty())
                {
                    cout << "not empty" << endl;
                }
                else
                {
                    cout << "container empty" << endl;
                }

                break; 

            case 3:

                cout << cont.Size() << endl; 
                break; 

            /* case 4:
                (const int*)newElement = cont.FirstElement();
                cout << newElement << endl; 
                break;

            case 5:
                (const int*)newElement = cont.LastElement();
                cout << newElement << endl; 
                break;
  */
            case 6:
                
                cout << "enter a value to find" << endl;
                cin>> Tempelement;

                if (cont.FindIf(Tempelement))
                {
                    cout << "find in container" << endl;
                }

                cout << "not found in container" << endl;
                break;

            case 7:
                
                cout << "enter a value to remove" << endl;
                cin>> Tempelement;

                if (cont.RemoveByElement(Tempelement))
                {
                    cout << "remove from container" << endl;
                }

                cout << "not found in container" << endl;
                break;

            case 8:
            
                cont.RemoveAllElements();
                cout << "size of container is: " << cont.Size() << endl;
                break;

            case 9:
                
                cout << "enter a value to remove and delete" << endl;
                cin>> Tempelement;

                cont.DeleteByElement(Tempelement);
                
                break;
            
            case 10:

                cont.DeleteAllElements();
                
                break;

            default:
                status = 0;
                break;
            
        }

    }
    return 0;
}
