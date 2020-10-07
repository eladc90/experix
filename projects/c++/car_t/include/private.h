#ifndef _PRIVATE_H_
#define _PRIVATE_H_
#include "car_t.h"

class private_t : public car_t
{
    public:
        private_t();
        private_t(private_t& _private);
        ~private_t(){;}
        void AccelerateBy10(){m_speed += 10;}
        void DecelerateBy10(){m_speed -= 10;}
        void SetSpeed(size_t _speed){m_speed = _speed;}
        string GetName(){return car_t::GetName();}
        size_t GetId(){car_t::GetId();}
        size_t GetCapacity(){car_t::GetCapacity();}
        string GetGear(){car_t::GetGear();}
        size_t GetDefaultCapacity(){car_t::GetDefaultCapacity();}
    private:
        size_t m_speed;
        static size_t mg_DefaultSpeed;
        static string mg_DefaultName;
};



#endif //_PRIVATE_H_