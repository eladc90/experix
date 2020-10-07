#include <iostream>
#include <vector> 
#include "Building_t.h"
#include "Street_t.h"
#include "City_t.h"

int main()
{
    int option;
    int status = 1;
    int ID = 0;
    Building_t<int> building(8);
    Street_t <int, int> street(5);
    City_t <int, int, int> city(12);
    

    while(status)
    {
        cout << "Choose option:\n" << endl;
        cout << "1:Set building ID" << endl;
        cout << "2:Set street ID" << endl;
        cout << "3:Set city ID" << endl;
        cout << "4:Get building ID" << endl;
        cout << "5:Get street ID" << endl;
        cout << "6:Get city ID" << endl;
        cout << "7:add building to street" << endl;
        cout << "8:add street to city" << endl;
        cout << "9:Get Building from street" << endl;
        cout << "10:Get street from city" << endl;
        cout << "Any another number - stop" << endl;


        cin >>  option;
        switch (option) 
        {
            case 1:

                cout<<"enter a number for the ID"<< endl;
                cin>> ID;

                building.SetBuildingId(ID);

                cout<< "building ID changed" << endl;
                break;

            case 2:

                cout<<"enter a number for the ID"<<endl;
                cin>> ID;

                street.SetStreetId(ID);

                cout<< "street ID changed" << endl;
                break;

            case 3:

                cout<<"enter a number for the ID"<< endl;
                cin>> ID;

                city.SetCityId(ID);

                cout<< "city ID changed" << endl;
                break;

            case 4:

                ID = building.GetBuildingId();
                cout<< ID << endl;
                break;

            case 5:

                ID = street.GetStreetId();
                cout<< ID << endl;
                break;

            case 6:

                ID = city.GetCityId();
                cout<< ID << endl;
                break;

            case 7:

                street.AddBuilding2Street(building);
                break;

            case 8:

                city.AddStreet2City(street);
                break;

            case 9:

                cout<<"enter a building ID"<< endl;
                cin>> ID;
                try
                {
                    street.GetBuilding(ID);
                }
                catch(int i)
                {
                    if (i == 0)
                    {
                        cout<<"street is empty"<< endl;
                    }
                    else if(i == 1)
                    {
                        cout<<"ID not found"<< endl;
                    }
                }
                
                break;

            case 10:

                cout<<"enter a street ID"<< endl;
                cin>> ID;
                try
                {
                    city.GetStreet(ID);
                }
                catch(int i)
                {
                    if (i == 0)
                    {
                        cout<<"street is empty"<< endl;
                    }
                    else if(i == 1)
                    {
                        cout<<"ID not found"<< endl;
                    }
                }
                
                break;
                
            default:
            {
                status = 0;	
                break;
            }

        }
    }

    
}