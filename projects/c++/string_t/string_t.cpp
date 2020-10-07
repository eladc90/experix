#include <string.h>
#include <stdio.h>
#include "string_t.h"
#include <ctype.h>
#include <stdio.h>


size_t string_t::mg_numOfString = 0;

size_t string_t::mg_caseSen = 0;

size_t string_t::mg_capacity = 8;

string_t::string_t()
{
	mg_numOfString++;
	m_buffer = CreateFrom(0);
}


string_t::~string_t()
{
	mg_numOfString--;
	delete[] m_buffer;
}



string_t::string_t(const char *_string)
{
	mg_numOfString++;
	m_buffer = CreateFrom(_string);
}



string_t& string_t::operator=(const string_t& _string)
{
	mg_numOfString++;
	if (this != &_string)
	{
		m_buffer = new char[_string.m_size];
		strcpy(m_buffer, _string.m_buffer);
		m_size = _string.m_size;
	}
	return *this;
}

string_t::string_t(const string_t&_string)
{
	
	operator=(_string);
}



size_t string_t::Capacity()const
{
	return m_capacity;
}

void string_t::setString(const char* str)
{
	delete[]m_buffer;
	m_size = strlen(str);
	if(m_size)
	{
		m_buffer = new char[m_size];
		strcpy(m_buffer,str);
	}	
}



int string_t::Compare(const string_t& _string)const
{
	if (mg_caseSen)
	{
		int cmp = strcmp(m_buffer, _string.m_buffer);
		if (cmp == 0)
		{
			return 0;
		}
		if(cmp < 0)
		{
			return 1;
		}
		else 
		{
			return 2;
		}
	}
	else
	{
		int cmp = strcasecmp(m_buffer, _string.m_buffer);
		if (cmp == 0)
		{
			return 0;
		}
		if(cmp < 0)
		{
			return 1;
		}
		else 
		{
			return 2;
		}
	}
	
}

void string_t::print()const
{
	if (m_buffer)
	{
		printf("this string is: %s\n", m_buffer);
	}
}



char *string_t::CreateFrom(const char* _str)
{
	int reCapacity = mg_capacity;
	char* newStr;
	if (!_str)
	{
		m_capacity = mg_capacity;
		m_buffer = new char[mg_capacity];
		m_size = 0;
		return m_buffer;
	}

    else if (strlen(_str) < reCapacity)
    {
    	m_size = strlen(_str);
		m_capacity = mg_capacity;
        newStr = new char[mg_capacity];
        if (newStr)
        {
        	strcpy(newStr, _str);
        }  	
    }
    else
    {
		while(strlen(_str) >= reCapacity)
		{
			reCapacity*=2;
		}
		m_capacity = reCapacity;
    	newStr = new char[reCapacity];
    	if (newStr)
    	{
    		strcpy(newStr, _str);
    	}
    	m_size = strlen(_str);
    }
    return newStr;
}



void string_t::LowerCase()
{
	int i = 0;
	char *ptr = m_buffer;
	for(; i<m_size;i++)
	{
		m_buffer[i] = tolower(m_buffer[i]);
	}
}

void string_t::UpperCase()
{
	int i = 0;
	char *ptr = m_buffer;
	for(; i<m_size;i++)
	{
		m_buffer[i] = toupper(m_buffer[i]);
	}
}


string_t& string_t::Prepend(const char* _str)
{
	
	char *tmp = new char[m_size + strlen(_str)];
	strcpy(tmp, _str);
	strcat(tmp, m_buffer);
	delete[]m_buffer;
	m_buffer = new char[m_size + strlen(_str)];
	strcpy(m_buffer, tmp);
	m_size += strlen(_str);
	delete[]tmp;
	return *this;
}

string_t& string_t::PrependFromString(const string_t& _string)
{
	return Prepend(_string.m_buffer);
}



string_t& string_t::operator+=(const char *_str)
{
	char *tmp = new char[m_size + strlen(_str)];
	strcpy(tmp, m_buffer);
	strcat(tmp, _str);
	delete[]m_buffer;
	m_buffer = new char[m_size + strlen(_str)];
	strcpy(m_buffer, tmp);
	m_size += strlen(_str);
}

string_t& string_t::operator+=(const string_t& _string)
{
	operator+=(_string.m_buffer);
}



int string_t::operator <= (const string_t& _string)const
{
	if(	(Compare(_string)) <= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int string_t::operator == (const string_t& _string)const
{
	if(	(Compare(_string) == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int string_t::operator!= (const string_t& _string)const
{
	if(	(Compare(_string)) != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int string_t::operator < (const string_t& _string)const
{
	if(	(Compare(_string)) < 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int string_t::operator > (const string_t& _string)const
{
	if(	(Compare(_string)) > 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int string_t::operator >= (const string_t& _string)const
{
	if(	(Compare(_string)) >= 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int string_t::Contains(const string_t& _string)const
{
	char *isContain = 0;
	if (mg_caseSen)
	{
		isContain = strcasestr(m_buffer, _string.m_buffer);
	}
	else
	{
		isContain = strstr(m_buffer, _string.m_buffer);
	}
	
	if(isContain)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

ostream& operator << (ostream& os, string_t& _str)
{
	os << _str.getString();
	return os;
}

istream& operator >> (istream& is, string_t& _str)
{
	char str[64];
	is >> str;
	_str.setString(str);
	return is;
}

const int string_t :: FirstOccurrence(const char _ch)const
{
	char *retValUp;
	char *retVal;
	if (mg_caseSen)
	{
		retVal = strchr(m_buffer,_ch);
		if(retVal == 0)
		{
			return -1;
		}
		else
		{
			return(retVal - m_buffer);
		}
	}
	else
	{
		retVal = strchr(m_buffer, tolower(_ch));
		retValUp = strchr(m_buffer,toupper(_ch));
		if ((retVal == 0) && (retValUp == 0))
		{
			return -1;
		}
		if (retVal == 0)
		{
			return (retValUp - m_buffer);
		}
		else if (retValUp == 0)
		{
			return (retVal - m_buffer);
		}
		
		return (retVal < retValUp) ? (retVal - m_buffer) : (retValUp - m_buffer);
	}
	
}

const int string_t :: LastOccurrence(const char _ch)const
{
	char *retValUp;
	char *retVal;
	if (mg_caseSen)
	{
		retVal = strrchr(m_buffer,_ch);
		if(retVal == 0)
		{
			return -1;
		}
		else
		{
			return(retVal - m_buffer);
		}
	}
	else
	{
		retVal = strrchr(m_buffer, tolower(_ch));
		retValUp = strrchr(m_buffer,toupper(_ch));
		if ((retVal == 0) && (retValUp == 0))
		{
			return -1;
		}
		if (retVal == 0)
		{
			return (retValUp - m_buffer);
		}
		else if (retValUp == 0)
		{
			return (retVal - m_buffer);
		}
		return (retVal < retValUp) ? (retVal - m_buffer) : (retValUp - m_buffer);
	}
}
	


char& string_t::operator[](size_t _index)const
{
	if(_index >= m_size )	
	{
		return m_buffer[strlen(m_buffer)];
	}
	else
	{
		return m_buffer[_index];
	}
}


char& string_t::operator[](int _index)
{
	if(_index >= m_size || _index < 0)	
	{
		return m_buffer[strlen(m_buffer)];
	}
	else
	{
		return m_buffer[_index];
	}
} 


string_t string_t::operator()(int start, int len)const
{
	int index = 0;
	char tmp[64];
	if (m_size >= start + len || len > 0)
	{
		for (;index < len; index++)
		{
			tmp[index] = m_buffer[index + start];
		}
		string_t str(tmp);
	}
	else
	{
		return 0;
	}
	return tmp;
}

















