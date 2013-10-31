#ifndef EVENT_H
#define EVENT_H
#include "Task.h"

class Event : public Task {

private:
	TASK_DATE deadLine;
	TIME endTime;
	TIME startTime;
	bool mark;
	bool expired;
	bool today;

public:

	Event(std::string name, TASK_DATE date, TIME start, TIME end);
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