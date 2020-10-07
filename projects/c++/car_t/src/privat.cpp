#include "private.h"
#include <iostream> 
#include <stdio.h>
#include <string>
using namespace std;

size_t private_t ::mg_DefaultSpeed = 100;

string private_t::mg_DefaultName = "private";


private_t::private_t():car_t()
{
    m_speed = mg_DefaultSpeed;
    SetName(mg_DefaultName);
}


private_t::private_t(private_t& _private):car_t(_private.GetCapacity())
{
    m_speed = _private.m_speed;
    SetName(_private.GetName());
}