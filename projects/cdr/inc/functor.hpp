#ifndef __HASHFUNCTOR_HPP_
#define __HASHFUNCTOR_HPP_

#include <string>
#include <iostream>
#include <cstdio>

namespace experis{

class FuncT{

public:

	size_t operator()(const std::string a_key){

		 size_t key = a_key.c_str()[1];
		 return key;
	}

};

} //namespace 
#endif /*__HASHFUNCTOR_HPP_*/
