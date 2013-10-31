
//This class stores all tasks into containers
//and performs adding, deleting, searching and loading functions

#ifndef STORAGE_H
#define STORAGE_H

#include <map>
#include <vector>
#include <ctime>
#include <assert.h>
#include "DeadlineTask.h"
#include "Event.h"
#include "Task.h"
#include "LoadFile.h"
#include "DataFeedback.h"


struct DEADLINE {
	DEADLINE(): endHr(0), endMin(0), day(0), month(0), year(0) {}
	DEADLINE(int _endHr, int _endMin, int _day, int _month, int _year)
		:  endHr(_endHr), endMin(_endMin),day(_day), month (_month), year(_year) {}
	int endHr; int endMin;int day; int month; int year;};


class Storage {

private:

	LoadFile loader;
	void checkForExpiry();
	void checkForCurrentDay();
	int getCurrentDay();
	int getCurrentMonth();
	int getCurrentYear();
	TIME getCurrentTime();
	bool isToday(Task* task);

	vector<Task*> floatTasks;
	vector<Task*> timedTasks;
	multimap <DEADLINE, Task*> timedTaskMap; 

public:

	Storage();
	~Storage();

	bool isExpired(Task* task);

	vector<Task*> addTimedTask(Task* timedTask);
	vector<Task*> addFloatTask(Task* TaskName);
	vector<Task*> searchByName(string taskName);
	vector<Task*> searchByDate(TASK_DATE dateToSearch);
	vector<Task*> delFloatTask(Task* taskToDel);
	vector<Task*> delTimedTask(Task* taskToDel);
	
	vector<Task*> getFloatTasks();
	vector<Task*> getTimedTasks();
	vector<Task*> getAllTasks();
	
	void loadToFile();
	void loadFromFile();
	void loadTimedTasksToMap();
};


#endif
