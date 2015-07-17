#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <string>
#include <map>
#include <sstream>

class ArgParser
{
public:
	ArgParser(const int argc, char **argv);
	bool get(const std::string argName, std::string &argOut);
	bool get(const std::string argName, double &argOut);
	bool get(const std::string argName, int &argOut);
	bool get(const std::string argName, char &argOut);
	bool get(const std::string argName, bool &argOut);
			
private:
	std::map<std::string, std::string> parsedArgs;

	void parse(const int argc, char **argv);
	std::string stripLeadingDashes(std::string arg) const;
	std::pair<std::string, std::string> splitOnEquals(std::string arg) const;
};

#endif