#include "ArgParser.hpp"

ArgParser::ArgParser(const int argc, char **argv)
{
	this->parse(argc, argv);

	return;
}

bool ArgParser::get(const std::string argName, std::string &argOut)
{
	auto argIter = this->parsedArgs.find(argName);
	if (argIter != this->parsedArgs.end())
	{
		argOut = argIter->second;
		return true;
	}
	else
		return false;
}

bool ArgParser::get(const std::string argName, double &argOut)
{
	auto argIter = this->parsedArgs.find(argName);
	if (argIter != this->parsedArgs.end())
	{
		std::istringstream(argIter->second) >> argOut;
		return true;
	}
	else
		return false;
}

bool ArgParser::get(const std::string argName, int &argOut)
{
	auto argIter = this->parsedArgs.find(argName);
	if (argIter != this->parsedArgs.end())
	{
		std::istringstream(argIter->second) >> argOut;
		return true;
	}
	else
		return false;
}

bool ArgParser::get(const std::string argName, char &argOut)
{
	auto argIter = this->parsedArgs.find(argName);
	if (argIter != this->parsedArgs.end())
	{
		argOut = argIter->second.c_str()[0];
		return true;
	}
	else
		return false;
}

bool ArgParser::get(const std::string argName, bool &argOut)
{
	auto argIter = this->parsedArgs.find(argName);
	if (argIter != this->parsedArgs.end())
	{
		argOut = true;
		return true;
	}
	else
		return false;
}

/*
This method attempts to 'do the obvious thing' and parses the given input arguments using the following rules
	- If the argument starts with 1 or more dashes 
		- Then leading dashes are removed and it is treated as a 'key'
		- If the 'key' contains an equals sign 
			- Then it is split on equals with the left side being the 'key' and right side being the 'value'
		- If the argument following a 'key' with no equals sign starts with a dash 
			- Then the current 'key' is treated as a boolean flag i.e. no corresponding 'value'
		- If the argument following a 'key' with no equals sign doesn't start with a dash 
			- Then it becomes the 'value' of the current key
	- If the argument doesn't start with a dash and doesn't follow a 'key'
		- Then it is ignored
*/
void ArgParser::parse(const int argc, char **argv)
{
	// argv[0] is the program name, so skip it
	for(int argNum = 1; argNum < argc; ++argNum)
	{
		std::string currentArg = argv[argNum];
		
		if (currentArg.at(0) == '-')
		{
			currentArg = this->stripLeadingDashes(currentArg);
			std::pair<std::string, std::string> argKeyValue;

			if (currentArg.find("=") != std::string::npos)
				argKeyValue = this->splitOnEquals(currentArg);
			else 
			{
				argKeyValue.first = currentArg;

				if (argNum + 1 < argc)
				{
					std::string possibleValue = argv[argNum + 1];
				
					if (possibleValue.at(0) != '-')
					{
						argKeyValue.second = possibleValue;
						++argNum; // Skip next one since we know it is the value of the current key
					}
				}
			}
			this->parsedArgs[argKeyValue.first] = argKeyValue.second;
		}
	}

	return;
}

std::string ArgParser::stripLeadingDashes(const std::string arg) const
{
	std::string cleanArg = arg;

	while(cleanArg.at(0) == '-')
		cleanArg.erase(0,1);

	return cleanArg;
}

std::pair<std::string, std::string> ArgParser::splitOnEquals(const std::string arg) const
{
	size_t equalPos = arg.find('=');
	auto keyValue = std::make_pair(arg.substr(0, equalPos), std::string());

	if (equalPos == std::string::npos)
		keyValue.second = "";
	else
		keyValue.second = arg.substr(equalPos + 1, std::string::npos);

	return keyValue;
}
