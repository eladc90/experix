#include "car_t.h"
#include <iostream> 
#include <stdio.h>
#include <string>

using namespace std;

size_t car_t::mg_numOfCars = 0;

size_t car_t::mg_DefCapacity = 500;

string car_t::mg_gear = "auto";

string car_t::mg_name = "private";


car_t::car_t(size_t _capacity)
{
    mg_numOfCars++;
    m_capacity = _capacity;
    m_id = mg_numOfCars;
    m_gear = mg_gear;
    m_name = mg_name;
}


car_t::car_t()
{
    mg_numOfCars++;
    m_capacity = mg_DefCapacity;
    m_id = mg_numOfCars;
    m_gear = mg_gear;
    m_name = mg_name;
}

car_t::car_t(const car_t& _car)
{
    mg_numOfCars++;
    m_capacity = _car.m_capacity;
    m_gear = _car.m_gear;
    m_name = _car.m_name;
}



string car_t::GetName()const
{
    return m_name;
}

string car_t::GetGear()const
{
    return m_gear;
}

bool car_t::operator>(car_t _car)const
{
    if (m_capacity > _car.m_capacity)
    {
        return true;
    }
    return false;
}

bool car_t::IsSameType(const car_t _first, const car_t _second)
{
    if (_first.m_name == _second.m_name)
    {
        return true;
    }
    return false;
}








