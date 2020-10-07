#include <string>
using namespace std;

template <class T>
class TExeption
{

    public:

        TExeption(){}
        TExeption( T _exeption, const char * _file, int _line, string _desc);
        const string GetDescription()const;
        inline const string GetFile(){return m_file;}
        inline const int GetLine(){return m_line;}
        inline const  T GetExe(){return m_exeption;}
        ~TExeption(){}

    private:
        string m_descrip;
        string m_file;
        int m_line;
        T m_exeption;
};

template <class T>
TExeption<T>:: TExeption( T _exeption,const char * _file, int _line, string _desc):m_file(_file), m_line(_line), m_exeption(_exeption),m_descrip(_desc)
{
    ;
}




template <class T>
const string TExeption<T>::GetDescription()const
{
    return m_descrip;
}