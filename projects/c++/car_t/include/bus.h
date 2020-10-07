#ifndef _BUS_H_
#define _BUS_H_
#include "car_t.h"

class bus_t : public car_t
{
    public:
    
        bus_t();
        bus_t(bus_t& _bus);
        bus_t(size_t _capacity);
        ~bus_t(){;}
        string GetName(){return car_t::GetName();}
        size_t GetId(){car_t::GetId();}
        size_t GetCapacity(){car_t::GetCapacity();}
        string GetGear(){car_t::GetGear();}
        size_t GetDefaultCapacity(){car_t::GetDefaultCapacity();}
        void SetSeatsNum(size_t _seats){m_seats = _seats;}
        const size_t GetSeatsNum(){return m_seats;}
        void SetLine(size_t _line){m_line = _line;}
        const size_t GetLine(){return m_line;}

    private:
        size_t m_seats;
        size_t m_line;
        static size_t mg_DefaultLine;
        static size_t mg_DefaultSeats;
        static string mg_DefaultName;
};



#endif //_BUS_H_//