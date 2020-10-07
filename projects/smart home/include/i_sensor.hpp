#ifndef I_SENSOR_HPP
#define I_SENSOR_HPP


namespace smartHome {

class Isensor {
public:
    Isensor() {}
    virtual ~Isensor() {}
    
    virtual void SendEvent() = 0;
private:

};

}//smartHome

#endif // !I_SENSOR_HPP