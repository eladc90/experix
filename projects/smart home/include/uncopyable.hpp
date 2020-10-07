#ifndef UNCOPYABLE_HPP_
#define UNCOPYABLE_HPP_

namespace smartHome {

class Uncopyable {
public:
protected:
    Uncopyable() {}
    virtual ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable& a_other);
    Uncopyable& operator=(const Uncopyable& a_other);

};

class UnAssignable {
public:
protected:
    UnAssignable() {}
    ~UnAssignable() {}

private:
    UnAssignable& operator=(const UnAssignable& a_other);
};

}//smartHome

#endif // _UNCOPYABLE_HPP_