#ifndef __BUILDING_T_H__
#define __BUILDING_T_H__

#include <iostream>

using namespace std;


template <class BID>
class Building_t
{
    public:

        Building_t();
        Building_t(BID _id);
        ~Building_t();
        bool operator==(const Building_t& _building);
        void SetBuildingId(const BID& _id);
        const BID& GetBuildingId()const;


    private:

        BID m_id;
};

template <class BID>
Building_t<BID>::Building_t()
{
    ;
}

template <class BID>
Building_t<BID>::Building_t(BID _id)
{
    m_id = _id;
}


template <class BID>
Building_t<BID>::~Building_t()
{
    ;
}


template <class BID>
void Building_t<BID>::SetBuildingId(const BID& _id)
{
    m_id = _id;
}


template <class BID>
const BID& Building_t<BID>::GetBuildingId()const
{
    return m_id;
}


template <class BID>
bool Building_t<BID>::operator==(const Building_t& _building)
{
    if (m_id == _building.m_id)
    {
        return true;
    }
    return false;
}


#endif //__BUILDING_T_H__