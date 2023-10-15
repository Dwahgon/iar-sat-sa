#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

#include <unordered_map>
#include <string>

struct Argument
{
    const std::string name;
    const unsigned char argLetter;
    const std::string argLong;
    const std::string description;
    const bool isBool;
    std::string value;
};

class ArgumentsParser
{
    std::unordered_map<std::string, Argument> args;
    std::unordered_map<unsigned char, const std::string> argLetterToArgName;
    std::unordered_map<std::string, const std::string> argLongToArgName;

    void printHelp();

public:
    ArgumentsParser(){};
    void addArgument(const Argument &arg);
    void parseArgs(int argv, char **argc);
    std::string &operator[](const std::string name);
};

#endif