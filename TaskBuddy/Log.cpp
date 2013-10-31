#include "stdafx.h"
#include "Log.h"


const string Log::FILE_NAME="Logfile.txt";

//takes in user input and keeps track of system function

void Log::writeLogToFile(string funcName,string status){

	ofstream logFile(FILE_NAME.c_str(),ios::app);
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	logFile<<asctime (timeinfo)<<" "<<"System"<< " "<<status<<" "<<funcName<< endl;
	logFile.close();
}