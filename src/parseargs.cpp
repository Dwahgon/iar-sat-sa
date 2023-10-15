#include "parseargs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void ArgumentsParser::addArgument(const Argument &arg)
{
    if (arg.argLetter == 'h')
    {
        std::cerr << "Argument letter 'h' is reserved for the help command";
        exit(1);
    }
    this->args.emplace(std::make_pair(arg.name, arg));
    this->argLetterToArgName.emplace(std::make_pair(arg.argLetter, arg.name));
    if (!arg.argLong.empty())
        this->argLongToArgName.emplace(std::make_pair("--" + arg.argLong, arg.name));
}

void ArgumentsParser::printHelp()
{
    for (auto arg : this->args)
    {
        std::cout << '-' << arg.second.argLetter;
        if (!arg.second.argLong.empty())
            std::cout << " --" << arg.second.argLong;
        std::cout << " : " << arg.second.name << std::endl;
        std::cout << '\t' << arg.second.description << std::endl;
    }
}

void ArgumentsParser::parseArgs(int argv, char **argc)
{
    for (int i = 1; i < argv; i++)
    {
        std::string arg(argc[i]);
        if (arg == "-h" || arg == "--help")
        {
            this->printHelp();
            exit(0);
        }
        if (this->argLetterToArgName.find(arg[1]) != this->argLetterToArgName.end())
        {
            Argument &argObj = this->args.at(this->argLetterToArgName.at(arg[1]));
            argObj.value = argObj.isBool ? "1" : std::string(argc[++i]);
            continue;
        }
        if (this->argLongToArgName.find(arg) != this->argLongToArgName.end())
        {
            Argument &argObj = this->args.at(this->argLongToArgName.at(arg));
            argObj.value = argObj.isBool ? "1" : std::string(argc[++i]);
            continue;
        }
        std::cout << "Unknown argument " << arg << std::endl;
        exit(1);
    }
}

std::string &ArgumentsParser::operator[](const std::string name)
{
    return this->args.at(name).value;
}