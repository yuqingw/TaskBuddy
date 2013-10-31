#ifndef TASK_H
#define TASK_H

#include <string>

using namespace std;

struct TASK_DATE {
	int month;
	int day;
	int year;
};

struct TIME {

	int hour;
	int min;
};

class Task {

protected:

	std::string taskName;

public:

	Task(std::string name);


	std::string getName();
	virtual TASK_DATE getDeadLine();
	virtual TIME getStartTime();
	virtual TIME getEndTime();
	virtual bool isExpired();
	virtual void indicateExpired();
	virtual bool isMarked();
	virtual void changeMark();
	virtual bool isToday();
	virtual void indicateToday(bool indication);


};
#endif