#ifndef __CITY_T_H__
#define __CITY_T_H__

#include <iostream>
#include <vector> 
#include "Building_t.h"
#include "Street_t.h"

using namespace std;

template <class CT, class STR, class BID>
class City_t
{
    public:
        
        City_t();
        City_t(CT _id);
        ~City_t();
        void SetCityId(CT _id);
        const CT GetCityId()const;
        void AddStreet2City(const Street_t<STR, BID>& _street);
        Street_t<STR, BID>& GetStreet(const STR _ID);
    
    private:

        CT m_id;
        vector <Street_t<STR, BID> > m_city;

};


template <class CT, class STR, class BID>
City_t<CT ,STR, BID>::City_t()
{
    ;
}

template <class CT, class STR, class BID>
City_t<CT ,STR, BID>::City_t(CT _id)
{
    m_id = _id;
}

template <class CT, class STR, class BID>
City_t<CT ,STR, BID>::~City_t()
{
    ;
}


template <class CT, class STR, class BID>
void City_t<CT ,STR, BID>::SetCityId(CT _id)
{
    m_id = _id;
}


template <class CT, class STR, class BID>
const CT City_t<CT ,STR, BID>::GetCityId()const
{
    return m_id;
}


template <class CT, class STR, class BID>
void City_t<CT ,STR, BID>::AddStreet2City(const Street_t<STR, BID>& _street)
{
    m_city.push_back(_street);
}

template <class CT, class STR, class BID>
Street_t<STR, BID>& City_t<CT ,STR, BID>::GetStreet(const STR _ID)
{
    size_t sizeOfVector = m_city.size();
    int index = 0;
    if (sizeOfVector == 0)
    {
        throw 0;
    }
    for (;index < sizeOfVector; index++)
    {
        if (_ID == m_city[index].GetStreetId())
        {
            return m_city[index];
        }
    }
    throw 1;
}



#endif //__CITY_T_H__