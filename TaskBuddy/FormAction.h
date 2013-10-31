// This class manipulates the GUI by taking in the controls from the form by it's pointer.
// It is invoked by the events that occur on the windows form.
// Controls that are passed in include datagridviews, status labels, textbox, monthcalendar and tooltips.
// This class depends on the Logic class' feedback to execute actions.
// Actions that are executed include displaying help balloons, updating datagridview rows, highlighting datagridview row,
// bolding monthcalendar on specific dates and displaying appropriate message based on user commands.

#ifndef FORMACTION_H
#define FORMACTION_H

#include <string>
#include <vector>
#include "Logic.h"
#include "Task.h"
#include "DataConverter.h"
#include "DataFeedback.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace std;

//This enumeration is used to determine the type of help
//balloon to display to the user
enum HelpType {
	START_HELP,
	ADD_HELP, 
	DELETE_HELP, 
	UPDATE_HELP, 
	SEARCH_HELP, 
	UNDO_HELP, 
	MARK_HELP
};

class FormAction {
private:
	static const int NO_TASK = 0;
	static const int FIRST_RUN = 1;
	static const int FIRST_POSITION = 0;
	static const int FIRST_ROW = 1;

	//Positions of columns in the table
	static const int TASK_NAME_COLUMN = 1;
	static const int TASK_DATE_COLUMN = 2;
	static const int TASK_STATUS_COLUMN = 5;

	//Feedback messages
	static const std::string NULL_TIME;
	static const std::string DEAD_LINE;
	static const std::string NO_START_TIME;
	static const std::string TIME_SEPARATOR;
	static const std::string DEFAULT_MESSAGE;
	static const std::string ADD_SUCCESS_MESSAGE;
	static const std::string DELETE_SUCCESS_MESSAGE;
	static const std::string DELETE_FAIL_MESSAGE;
	static const std::string UNDO_ADD_SUCCESS_MESSAGE;
	static const std::string UNDO_DELETE_SUCCESS_MESSAGE;
	static const std::string SEARCH_SUCCESS_MESSAGE;
	static const std::string UPDATE_SUCCESS_MESSAGE;
	static const std::string UNDO_UPDATE_SUCCESS_MESSAGE;
	static const std::string MARK_SUCCESS_MESSAGE;
	static const std::string UNDO_MARK_SUCCESS_MESSAGE;
	static const std::string LOAD_SUCCESS_MESSAGE;
	static const std::string BACK_TO_MAIN_MESSAGE;
	static const std::string UNMARK_SUCCESS_MESSAGE;
	static const std::string EMPTY_SEARCH_MESSAGE;
	static const std::string INVALID_NO_NAME_MESSAGE;
	static const std::string INVALID_TIME_FORMAT_MESSAGE;
	static const std::string INVALID_TIME_MESSAGE;
	static const std::string INVALID_DATE_PASSED_MESSAGE;
	static const std::string INVALID_DATE_MESSAGE;
	static const std::string INVALID_DURATION_MESSAGE;
	static const std::string INVALID_POSITION_MESSAGE;
	static const std::string INVALID_DEL_COMMAND_MESSAGE;
	static const std::string INVALID_NO_COMMAND_MESSAGE;
	static const std::string INVALID_COMMAND_MESSAGE;

	DataFeedback dataContainer;
	DataConverter* convertFrom;
	UserFeedback feedback;
	vector<Task*> taskList;
	int newPosition;
	bool mainTaskChange;
	bool floatTaskChange;
	int mainRowCount;
	int floatRowCount;

public:
	FormAction();
	FormAction(DataFeedback dataContainer);
	UserFeedback startExecution(DataGridView^ dataGridView1, DataGridView^ dataGridView2, Label^ status, MonthCalendar^ calendarDisplay);
	void executeRowAdd(DataGridView^ dataGridView1, DataGridView^  dataGridView2);
	void executeRowDelete(DataGridView^ dataGridView1, DataGridView^  dataGridView2);
	void resetStatusMessage(Label^ status);
	void setRowCount(int mainRowCount, int floatRowCount);
	void showBalloon(array<ToolTip^>^ toolTipArray, TextBox^ textBox1, Label^ dummyTasks, Label^ dummyWL, MonthCalendar^ calendarDisplay, HelpType typeOfHelp);
	~FormAction();

private:
	void executeRowAddOrDelete(DataGridView^ dataGridView1, DataGridView^  dataGridView2);
	bool isAdd();
	void addRowToMainTask(Task* currentTask, DataGridView^ dataGridView1);
	void addRowToFloatTask(Task* currentTask, DataGridView^  dataGridView2);
	void getRowNumber(int rowCount, String^& rowNumber);
	void getTaskName(Task* currentTask, String^& taskName);
	void determineTaskDate(Task* currentTask, String^& taskDate);
	void determineTimeAndDeadline(Task* currentTask, String^& time, String^& taskDeadLine);
	void determineTaskStatus(Task* currentTask, String^ &taskStatus);
	void clearRow(DataGridView^ dataGridView1, DataGridView^  dataGridView2);
	void displayOperationMessage(UserFeedback feedback, Label^ status);
	void changeStatusForegroundColour(Label^ status, Color colour);
	void changeStatusMessage(Label^ status, std::string message);
	bool isNewTask(int index);
	void changeRowColour(DataGridView^ dataGridView);
	void changeDeletedRowColour(DataGridView^ dataGridView1, DataGridView^ dataGridView2);
	void changeCompletedAndExpiredTaskRowColour(DataGridView^ dataGridView);
	IEnumerator^ setDataGridEnumerator(DataGridView^ dataGridView1, DataGridView^ dataGridView2);
	String^ determineCurrentRowTaskName(DataGridView^ dataGridView1, DataGridView^ dataGridView2, int currentRowIndex);
	bool isTaskDone(DataGridViewRow^ currentRow);
	bool isTaskExpired(DataGridViewRow^ currentRow);
	bool isDeadLinePresent(Task* currentTask);
	bool isEvent(Task* currentTask);
	String^ mergeTime(String^ startTime, String^ endTime);
	void determineColourChange(DataGridViewRow^ currentRow);
	void changeBackgroundColour(DataGridViewRow^ currentRow, Color colour);
	void changeDeletedTaskStatus(DataGridViewRow^ currentRow);
	void boldTaskDates(DataGridView^ dataGridView1, MonthCalendar^ calendarDisplay);
};

#endif