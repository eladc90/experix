#include <iostream>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <boost/unordered_map.hpp>

template<class T>
void EnterToMap (boost::unordered_map<T,  int>& a_map, std::vector<T>& a_vector) {
    int counter = 0;
    typename std::vector<T>::iterator begin = a_vector.begin();
    typename std::vector<T>::iterator end = a_vector.end();
    while (begin != end) {    
        //begin->Print();
        typename boost::unordered_map<T,  int>::iterator val = a_map.find(*begin);
        if (val == a_map.end()) {
            a_map.insert(std::make_pair(*begin, counter));
        }
        else {
            val->second = -1;
        }
        ++counter;
        ++begin;
    }
    
}

template<class T>
T findFirstUniq(std::vector<T>& a_vector) {
    typename boost::unordered_map<T,  int> map;
    EnterToMap(map, a_vector);
    
    typename boost::unordered_map<T,  int>::iterator begin = map.begin();
    typename boost::unordered_map<T,  int>::iterator end = map.end();
    T reval = begin->first;
    int secIndex = a_vector.size();
    while (begin != end) {
        if (begin->second != -1 && begin->second < secIndex) {
            reval = begin->first;
            secIndex = begin->second;
        }
        ++begin;
    }
    return reval;
}

class TestClass {
public:
    TestClass(int a_id) : m_id(a_id) {}
    //~TestClass() = default;
    TestClass(const TestClass& a_other) : m_id(a_other.GetId()) {}
    TestClass& operator=(const TestClass& a_other) { m_id = a_other.m_id; return *this; }
    const bool operator<(const TestClass& a_other)const {
        if (m_id < a_other.m_id) {
            return true;
        }
        else {
            return 0;
        }
    }
    int GetId() const { return m_id; }
    void Print() { std::cout << "the id is: " << m_id << std::endl; }
    bool operator==(const TestClass& a_other) {
        if (a_other.m_id == m_id) {
            return true;
        }
    }
private:
    int m_id;
};

