#ifndef CONFIG_PARSER_HPP
#define CONFIG_PARSER_HPP

#include <string>
#include <vector>

namespace smartHome {

typedef std::vector<std::string> ParseCont;

class ConfigParser {

enum ContIndex {
    CREATE_FUNC = 0,
    ROOM,
    FLOOR
};

public:
    ConfigParser();
    //~ConfigParser() = default;

    void ParseLine(std::string a_line);
    std::string GetFunc();
    std::string GetRoom();
    std::string GetFloor();

private:
    ParseCont m_parseCont;

};

}// smartHome

#endif // CONFIG_PARSER_HPP