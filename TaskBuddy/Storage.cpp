#include "stdafx.h"
#include "Storage.h"


//Use comparison operator to compare attributes in struct "Deadline"
//so as to allow auto-sorting of keys in multimap 
bool operator <( DEADLINE const& left, DEADLINE const& right )
{
	int leftHour = left.endHr;
	int rightHour = right.endHr;

	if(leftHour == 12 || leftHour == 24) {
		leftHour -=12;
	}

	if(rightHour == 12 || rightHour == 24) {
		rightHour -=12;
	}
    return (left.year< right.year) || 
		(left.year == right.year && left.month < right.month )|| 
		(left.year == right.year && left.month == right.month && left.day < right.day )|| 
		(left.year == right.year && left.month == right.month && left.day == right.day && leftHour < rightHour ) || 
		(left.year == right.year && left.month == right.month && left.day == right.day && left.endHr== right.endHr && left.endMin < right.endMin );
}

Storage::Storage()
{
	loadFromFile();
	checkForExpiry();
}

Storage::~Storage()
{
	
	vector<Task*> timedTasks = getAllTasks();

	for(int i=0; i<timedTasks.size(); i++) {
		delete timedTasks[i];
		timedTasks[i] = NULL;
	}

	for(int i=0; i<floatTasks.size(); i++) {
		delete floatTasks[i];
		floatTasks[i] = NULL;
	}
	
	timedTasks.clear();
	floatTasks.clear();
}


//Checks for expiry of all tasks in the multimap
void Storage::checkForExpiry() {

	multimap<DEADLINE, Task*>::iterator it;
	it=timedTaskMap.begin(); 
	while(it != timedTaskMap.end()){

		if(isExpired((*it).second)) {
			(*it).second->indicateExpired();
		}

		if(isToday((*it).second)) {
			(*it).second->indicateToday(true);
		} else {
			(*it).second->indicateToday(false);
		}

		it++; 
	}
}

//Checks with local task if a task is due today
bool Storage::isToday(Task* task) {

	if(task->getDeadLine().year == getCurrentYear() && task->getDeadLine().month == getCurrentMonth() && task->getDeadLine().day == getCurrentDay()) {
		return true;
	} else {
		return false;
	}
}

//Return true if a task has expired
bool Storage::isExpired(Task* task) {

	int hour = task->getEndTime().hour;
	if(hour == 24 || hour == 12) {
		hour-=12;
	}

	if(task->getDeadLine().year < getCurrentYear()) {
		return true;
	} else if(task->getDeadLine().year == getCurrentYear() && task->getDeadLine().month < getCurrentMonth()) {
		return true;
	} else if(task->getDeadLine().year == getCurrentYear() && task->getDeadLine().month == getCurrentMonth() && task->getDeadLine().day < getCurrentDay()) {
		return true;
	} else if(task->getDeadLine().year == getCurrentYear() && task->getDeadLine().month == getCurrentMonth() && task->getDeadLine().day == getCurrentDay() 
		&& hour < getCurrentTime().hour) {
		return true;
	} else if(task->getDeadLine().year == getCurrentYear() && task->getDeadLine().month == getCurrentMonth() && task->getDeadLine().day == getCurrentDay() 
		&& hour == getCurrentTime().hour && task->getEndTime().min < getCurrentTime().min) {
		return true;
	} else {
		return false;
	}
}
	
//Checks with local time to get the current month
int Storage::getCurrentMonth() {

	time_t now = time(0);
	tm *ltm = localtime(&now);

	return ltm->tm_mon+1;

}

//Checks with local time to get current day
int Storage::getCurrentDay() {

	time_t now = time(0);
	tm *ltm = localtime(&now);

	return ltm->tm_mday;

}

//Checks with local time to get current year
int Storage::getCurrentYear() {

	time_t now = time(0);
	tm *ltm = localtime(&now);

	return 1900 + ltm->tm_year;

}

//Checks local time
TIME Storage::getCurrentTime() {

	TIME currentTime;
	time_t now = time(0);
	tm *ltm = localtime(&now);

	currentTime.min = ltm->tm_min;
	currentTime.hour = ltm->tm_hour;

	return currentTime;
}

//Adds a timed task to multimap and vector
vector<Task*> Storage::addTimedTask(Task* timedTask) {
	
	assert(timedTask != NULL);

	DEADLINE TaskDeadline(timedTask->getEndTime().hour, timedTask->getEndTime().min, 
		timedTask->getDeadLine().day, timedTask->getDeadLine().month, 
		timedTask->getDeadLine().year);
	
	multimap<DEADLINE, Task*>::iterator it;
	
	timedTaskMap.insert(pair<DEADLINE, Task*>(TaskDeadline, timedTask));
	
	vector<Task*> taskList;
	int addPos;
	int posCounter = 0;

	it=timedTaskMap.begin(); 
	while(it != timedTaskMap.end()){

		if((*it).second == timedTask) {
			addPos = posCounter;
		}

		taskList.push_back((*it).second);
		it++; 
		posCounter++;
	}

	checkForExpiry();
	timedTasks=taskList;
	return taskList;

}

//Adds a floating task to vector
vector<Task*> Storage::addFloatTask(Task* TaskName)
{
	assert(TaskName != NULL);
	floatTasks.push_back(TaskName);
	checkForExpiry();

	return floatTasks;
}

//Deletes a floating task from vector
vector<Task*> Storage::delFloatTask(Task* taskToDel) {
	
	assert(taskToDel != NULL);

	bool isFound = false;
	
	for(int i=0; i<floatTasks.size(); i++) {

		if(floatTasks[i] == taskToDel) {

			isFound = true;
			floatTasks.erase(floatTasks.begin() + i);

		}
	}

	checkForExpiry();
	return floatTasks;

}


//Deletes a timed task from multi-map and vector
vector<Task*> Storage::delTimedTask(Task* taskToDel) {

	assert(taskToDel != NULL);

	multimap<DEADLINE, Task*>::iterator it;
	
	for(it=timedTaskMap.begin(); it!=timedTaskMap.end(); it++) {

		if((*it).second == taskToDel) {
			timedTaskMap.erase(it);
			break;
		}
	}

	vector<Task*> taskList;
	it=timedTaskMap.begin();
	while(it != timedTaskMap.end()){

		taskList.push_back((*it).second);
		it++;
	}
	for(int i=0; i<timedTasks.size(); i++) {

		if(timedTasks[i] == taskToDel) {

			timedTasks.erase(timedTasks.begin() + i);

		}
	}

	checkForExpiry();
	return taskList;
}

//Searching of multimap based on name of task
vector<Task*> Storage::searchByName(string taskName) {
	assert(taskName.size() != 0);

	size_t foundName;
	
	multimap<DEADLINE, Task*>::iterator it;
	vector<Task*> taskList;
	
	for(it=timedTaskMap.begin(); it!=timedTaskMap.end(); it++) {

		foundName = (*it).second->getName().find(taskName); 
		if(int(foundName) != string::npos) {
			taskList.push_back((*it).second);
		}
	}
	
	checkForExpiry();
	return taskList;

}


//Searching of multimap by date
vector<Task*> Storage::searchByDate(TASK_DATE dateToSearch) {

	multimap<DEADLINE, Task*>::iterator it;
	vector<Task*> taskList;
	
	for(it=timedTaskMap.begin(); it!=timedTaskMap.end(); it++) {

		if(((*it).second->getDeadLine().day == dateToSearch.day) && 
			((*it).second->getDeadLine().month == dateToSearch.month) && 
			((*it).second->getDeadLine().year == dateToSearch.year)) {

			taskList.push_back((*it).second);
		}
	}

	checkForExpiry();
	return taskList;
}


//Loads to file after exiting program
void Storage::loadToFile()
{
	
	loader.inputFloatTasksToFile(floatTasks);
	loader.inputTimedTasksToFile(timedTasks);
	
}

//Loads from file after opening from program
void Storage::loadFromFile()
{
	
	timedTasks = loader.loadTimedTasks();
	floatTasks = loader.loadFloatTasks();
	loadTimedTasksToMap();
	
}

//Load the tasks from file to multi-map
void Storage::loadTimedTasksToMap()
{
	for (int i=0;i<timedTasks.size();i++)
	{
		DEADLINE TaskDeadline(timedTasks[i]->getEndTime().hour, timedTasks[i]->getEndTime().min, 
			timedTasks[i]->getDeadLine().day, timedTasks[i]->getDeadLine().month, 
			timedTasks[i]->getDeadLine().year);
		timedTaskMap.insert(pair<DEADLINE, Task*>(TaskDeadline, timedTasks[i]));
	}
	
}

//returns all tasks vector
vector<Task*> Storage::getAllTasks() {

	vector<Task*> taskList;
	multimap<DEADLINE, Task*>::iterator it;

	it=timedTaskMap.begin();
	while(it != timedTaskMap.end()){

		taskList.push_back((*it).second);
		it++;
	}

	checkForExpiry();
	return taskList;
}


vector<Task*> Storage::getFloatTasks() {
	
	return floatTasks;

}


vector<Task*> Storage::getTimedTasks() {
	
	return timedTasks;

}