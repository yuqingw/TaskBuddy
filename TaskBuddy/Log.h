#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Log {

private:
	time_t rawtime;
	struct tm * timeinfo;
	static const string FILE_NAME; 

public:

	void writeLogToFile(string funcName,string status);


};

#endif