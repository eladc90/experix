#ifndef __STREET_T_H__
#define __STREET_T_H__

#include <iostream>
#include <vector> 
#include "Building_t.h"

using namespace std;


template <class STR, class BID>
class Street_t
{
    public:

        Street_t();
        Street_t(STR _id);
        ~Street_t();
        void SetStreetId(STR _id);
        const STR GetStreetId()const;
        void AddBuilding2Street(const Building_t<BID>& _building);
        const Building_t<BID>& GetBuilding(const BID _ID);
        bool operator==(const Street_t& _street);

    private:

        STR m_id;
        vector <Building_t<BID> > m_BuildingArray;

};

template <class STR, class BID>
Street_t<STR, BID>::Street_t()
{
    ;
}

template <class STR, class BID>
Street_t<STR, BID>::Street_t(STR _id)
{
    m_id = _id;
}

template <class STR, class BID>
Street_t<STR, BID>::~Street_t()
{
    ;
}

template <class STR, class BID>
void Street_t<STR, BID>::SetStreetId(STR _id)
{
    m_id = _id;
}

template <class STR, class BID>
const STR Street_t<STR, BID>::GetStreetId()const
{
    return m_id;
}


template <class STR, class BID>
void Street_t<STR, BID>::AddBuilding2Street(const Building_t<BID>& _building)
{
    m_BuildingArray.push_back(_building);
}


template <class STR, class BID>
const Building_t<BID>& Street_t<STR, BID>::GetBuilding(const BID _ID)
{
   
    size_t sizeOfVector = m_BuildingArray.size();
    int index = 0;
    if (sizeOfVector == 0)
    {
        throw 0;
    }
    for (;index < sizeOfVector; index++)
    {
        if (_ID == m_BuildingArray[index].GetBuildingId())
        {
            return m_BuildingArray[index];
        }
    }
    throw 1;
}


template <class STR, class BID>
bool Street_t<STR ,BID>::operator==(const Street_t& _street)
{
    if (m_id == _street.m_id)
    {
        return true;
    }
    return false;
}


#endif //__STREET_T_H__