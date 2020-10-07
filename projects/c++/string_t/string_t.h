#ifndef __STRING_T_H__
#define __STRING_T_H__
#include <iostream> 

using namespace std;

class string_t
{
	public:
		string_t();
		~string_t();
		string_t(const char *);
		string_t(const string_t&);
		string_t& operator=(const string_t&);
		string_t& operator+=(const char *);
		string_t& operator+=(const string_t&);
		int operator <= (const string_t&)const;
		int operator == (const string_t&)const;
		int operator != (const string_t&)const;
		int operator < (const string_t& _string)const;
		int operator > (const string_t& _string)const;
		int operator >= (const string_t& _string)const;
		string_t operator()(int start, int len)const;
		char& operator[](size_t _index)const;
		char& operator[](int _index);
		size_t Capacity()const; 
		
		int length()const;
		void setString(const char*);
		const char *getString() const;
		char *CreateFrom(const char* );
		int Compare(const string_t&) const;
		void print() const;
		void LowerCase();
		void UpperCase();
		string_t& Prepend(const char*);
		string_t& PrependFromString(const string_t&);
		int Contains(const string_t& )const;
		const int FirstOccurrence(const char _ch)const;
		const int LastOccurrence(const char _ch)const;
		inline static int NumOstring() {return mg_numOfString;}const
		inline static size_t GetGlbCapacity() {return mg_capacity;}const
		inline static size_t GetCaseSen(){return mg_caseSen;}const
		static size_t ChangeCaseSen(bool _i){return mg_caseSen = _i;}
	private:
		char *m_buffer;
		int m_size;
		size_t m_capacity;
		static size_t mg_numOfString;
		static size_t mg_caseSen;
		static size_t mg_capacity;
};

ostream& operator << (ostream& os, string_t& _str);

istream& operator >> (istream& is, string_t& _str);

inline int string_t::length()const
{
	return m_size;
}

inline const char *string_t::getString()const
{
	return m_buffer;
}

#endif /*__STRING_T_H__*/
