http://gamel.com/http://gamel.com/#ifndef _QUERY_HPP_
#define _QUERY_HPP_

#include "record.hpp"

namespace experis {

class IQuery {  

public:
     enum QUERY_REQWEST
    {
        MSISDN = 0,
        OPREATOR_RETRIVE,
        LINK,
        LINK_PATH
    };

    IQuery(){}
    virtual ~IQuery(){}
    /*virtual Record* GetRecord(const std::string& a_key , QUERY_REQWEST a_reqType) = 0;*/

private:
    IQuery(const IQuery& a_other);
    IQuery& operator=(const IQuery& a_other);
};

}//namespace experis

#endif //  _Query_HPP_
