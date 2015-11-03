#pragma once
#include <string>
#include <fstream>
class FileIO
{
public:
	FileIO();
	~FileIO();
	std::string getLine(std::string filelocation, int row);
	void saveLine(std::string filelocation, std::string line, int row);
	void saveLine(std::string filelocation, std::string line, bool);
	int linesCount(std::string filelocation);
};

