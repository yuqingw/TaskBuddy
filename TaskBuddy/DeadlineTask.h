#ifndef DEADLINETASK_H
#define DEADLINETASK_H
#include "Task.h"

class DeadlineTask : public Task {

private:

	TASK_DATE deadLine;
	TIME endTime;
	bool mark;
	bool expired;
	bool today;

public:

	DeadlineTask(std::string name, TASK_DATE date, TIME time);

	virtual bool isExpired();
	virtual void indicateExpired();
	virtual bool isMarked();
	virtual void changeMark();
	virtual bool isToday();
	virtual void indicateToday(bool indication);
	virtual TASK_DATE getDeadLine();
	virtual TIME getStartTime();
	virtual TIME getEndTime();


};

#endif