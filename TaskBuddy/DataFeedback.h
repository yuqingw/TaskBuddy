//	
//	NAME: class DataFeedback
//	DESCRIPTION: This class contains information required by GUI class
//	that are required for display.
//	Information include:	
//		Information about the users actions and any invalidities for message displays.
//		Whether to change display for timedtasks or floating tasks.
//		The vector of tasks to be displayed.
//		Position of tasks in the vector that are to be highlighted if applicable.
//	The above information is determined in the Logic class whereby Logic will analyse
//	and set the information accordingly.
//


#ifndef DATAFEEDBACK_H
#define DATAFEEDBACK_H

#include <vector>
#include "Task.h"

enum UserFeedback {
	NIL, 
	ADD_SUCCESS, 
	DEL_SUCCESS,
	MARK_SUCCESS,
	UNMARK_SUCCESS,
	DEL_FAIL,
	UPD_SUCCESS, 
	UNDONE, 
	UNDO_ADD, 
	UNDO_DELETE,
	UNDO_UPD,
	UNDO_MARK,
	SEARCH_SUCCESS,  
	LOAD_SUCCESS,
	MAIN,
	EMPTY_SEARCH, 
	INVALID_COMMAND,
	INVALID_NO_COMMAND,
	INVALID_DEL_COMMAND,
	INVALID_SEARCH,
	INVALID_NO_NAME,
	INVALID_TIME_FORMAT,
	INVALID_TIME,
	INVALID_DATE,
	INVALID_DATE_PASSED,
	INVALID_DURATION,
	INVALID_POSITION
};

class DataFeedback {

private:

	static const int FLOAT_WAS_CHANGED = 0;
	static const int TIMED_WAS_CHANGED = 1;
	static const int NULL_POSITION = -1;

	UserFeedback messageToUser;
	vector<Task*> listOfTasksForDisplay;
	vector<Task*> mainPageList;
	Task* changedTask;
	int changedPos;
	bool changedFloat;
	bool changedTimed;
	

public:

	DataFeedback();
	DataFeedback(UserFeedback feedBack, vector<Task*> tasks, Task* task, int whatChanged);
	DataFeedback(UserFeedback feedBack, vector<Task*> tasks, int whatChanged);
	DataFeedback(UserFeedback feedBack);

	bool haveChangedFloat();
	bool haveChangedTimed();
	int getAddedPos();
	UserFeedback getFeedback();
	vector<Task*> getTaskList();
	vector<Task*> getMainList();
	Task* getChangedTask();
	
	void setFeedback(UserFeedback feedback);
	void setChangedPosition(int position);
	void changeTaskList(vector<Task*> list);
	void setMainList(vector<Task*> list);

};

#endif