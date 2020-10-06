#include "bus.h"
#include <iostream> 
#include <stdio.h>
#include <string>
using namespace std;

size_t bus_t::mg_DefaultLine = 0;

size_t bus_t::mg_DefaultSeats = 50;

string bus_t::mg_DefaultName = "bus";


bus_t::bus_t():car_t()
{
    m_seats = mg_DefaultSeats;
    m_line = mg_DefaultLine;
    SetName(mg_DefaultName);
}

bus_t::bus_t(bus_t& _bus):car_t(_bus.GetCapacity())
{
    m_seats = _bus.m_seats;
    m_line = _bus.m_line;
    SetName(_bus.GetName());
}

bus_t::bus_t(size_t _capacity):car_t(_capacity)
{
    m_seats = mg_DefaultSeats;
    m_line = mg_DefaultLine;
    SetName(mg_DefaultName);
}

