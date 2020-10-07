#ifndef __CAR_T_H__
#define __CAR_T_H__

#include <iostream> 
#include <stdio.h>

using namespace std;

class car_t
{
    public:
        car_t();
        car_t(size_t _capacity);
        car_t(const car_t& _car);
        car_t& operator=(const car_t&){;}
        bool operator>(const car_t _car)const;
        bool IsSameType(const car_t _first, const car_t _second);

    protected:
    // functions:

        ~car_t(){;}
        string GetGear()const;/* {return m_gear;}const */
        string GetName()const;/* {return m_name;}const */
        size_t GetCapacity(){return m_capacity;}const
        size_t GetId(){return m_id;}const
        size_t GetDefaultCapacity() {return mg_DefCapacity;}
        void SetName(string _str){m_name = _str;}
        void SetCapacity(size_t _capacity){m_capacity = _capacity;}
        void SetGear(string _str){m_gear = _str;}
        void SetDefaultCapacity(size_t _capacity){mg_DefCapacity = _capacity;}

    // members: 

    private:
        size_t m_id;
        size_t m_capacity;
        string m_gear;
        string m_name;
        static size_t mg_numOfCars;
        static size_t mg_DefCapacity;
        static string mg_gear;
        static string mg_name;
};












#endif /*__CAR_T_H__*/