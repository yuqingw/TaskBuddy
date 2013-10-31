
#ifndef LOADFILE_H
#define LOADFILE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Task.h"
#include "DeadlineTask.h"
#include "Event.h"

using namespace std;



class LoadFile{

private:

	fstream textFile;
	static const string FLOAT_FILE_NAME;
	static const string EVENT_FILE_NAME;

public:

	vector<Task*> loadFloatTasks();
	vector<Task*> loadTimedTasks();
	void inputFloatTasksToFile(vector<Task*> &tasks);
	void inputTimedTasksToFile(vector<Task*> &tasks);

};

#endif
