#include "stdafx.h"
#include "FormAction.h"

const std::string FormAction::NULL_TIME = "-";
const std::string FormAction::DEAD_LINE = "0/0/0";
const std::string FormAction::NO_START_TIME = "";
const std::string FormAction::TIME_SEPARATOR = " - ";
const std::string FormAction::DEFAULT_MESSAGE = "";
const std::string FormAction::ADD_SUCCESS_MESSAGE = "Add Successful!";
const std::string FormAction::DELETE_SUCCESS_MESSAGE = "Delete Successful!";
const std::string FormAction::DELETE_FAIL_MESSAGE = "Delete Fail!";
const std::string FormAction::UNDO_ADD_SUCCESS_MESSAGE = "Previous Add Action Successfully Undone!";
const std::string FormAction::UNDO_DELETE_SUCCESS_MESSAGE = "Previous Delete Action Successfully Undone!";
const std::string FormAction::SEARCH_SUCCESS_MESSAGE = "Search Successful!";
const std::string FormAction::UPDATE_SUCCESS_MESSAGE = "Update Successful!";
const std::string FormAction::UNDO_UPDATE_SUCCESS_MESSAGE = "Previous Update Action Successfully Undone!";
const std::string FormAction::MARK_SUCCESS_MESSAGE = "Task Is Successfully Marked/Unmarked!";
const std::string FormAction::UNDO_MARK_SUCCESS_MESSAGE = "Previous Mark/Unmark Action Successfully Undone!";
const std::string FormAction::LOAD_SUCCESS_MESSAGE = "Welcome To TaskBuddy!";
const std::string FormAction::BACK_TO_MAIN_MESSAGE = "Returned To Main Page.";
const std::string FormAction::UNMARK_SUCCESS_MESSAGE = "Task Is Successfully Unmarked!";
const std::string FormAction::EMPTY_SEARCH_MESSAGE = "Sorry, No Search Results Found.";
const std::string FormAction::INVALID_NO_NAME_MESSAGE = "Sorry, You Did Not Enter a Task Name. Please Try Again.";
const std::string FormAction::INVALID_TIME_FORMAT_MESSAGE = "Sorry, You Did Not Enter a Valid Time Format. Please Try Again.";
const std::string FormAction::INVALID_TIME_MESSAGE = "Sorry, You Did Not Enter a Valid Time. Please Try Again.";
const std::string FormAction::INVALID_DATE_PASSED_MESSAGE = "Sorry, The Time Or Date Entered Has Passed. Please Try Again.";
const std::string FormAction::INVALID_DATE_MESSAGE = "Sorry, You Did Not Enter a Valid Date. Please Try Again.";
const std::string FormAction::INVALID_DURATION_MESSAGE = "Sorry, You Did Not Enter a Valid Time Duration. Please Try Again.";
const std::string FormAction::INVALID_POSITION_MESSAGE = "Sorry, You Did Not Enter a Valid Index. Please Try Again.";
const std::string FormAction::INVALID_DEL_COMMAND_MESSAGE = "Sorry, You Did Not Enter a Valid Delete Command. Please Try Again.";
const std::string FormAction::INVALID_NO_COMMAND_MESSAGE = "Sorry, There Is No Action To Undo.";
const std::string FormAction::INVALID_COMMAND_MESSAGE = "Invalid Command, Sorry.";


FormAction::FormAction() {
	convertFrom = NULL;
}

FormAction::FormAction(DataFeedback dataContainer) {
	this->dataContainer = dataContainer;
	convertFrom = new DataConverter;
	feedback = dataContainer.getFeedback();
	taskList = dataContainer.getTaskList();
	newPosition = dataContainer.getAddedPos();
	mainTaskChange = dataContainer.haveChangedTimed();
	floatTaskChange = dataContainer.haveChangedFloat();

}

UserFeedback FormAction::startExecution(DataGridView^ dataGridView1, DataGridView^ dataGridView2, Label^ status, MonthCalendar^ calendarDisplay) {
	
	//This is to prevent the calendar to flash too often
	if(feedback != INVALID_COMMAND) {
		//Remove and update to refresh the calendar
		calendarDisplay->RemoveAllBoldedDates();
		calendarDisplay->UpdateBoldedDates();
	}else if (feedback == INVALID_COMMAND) {
		displayOperationMessage(feedback, status);
		return feedback;
	}

	executeRowAddOrDelete(dataGridView1, dataGridView2);
	changeCompletedAndExpiredTaskRowColour(dataGridView1);
	boldTaskDates(dataGridView1, calendarDisplay);
	displayOperationMessage(feedback, status);

	return feedback;
}

//This method executes row add or row delete based on feedback from the logic class
void FormAction::executeRowAddOrDelete(DataGridView^ dataGridView1, DataGridView^ dataGridView2) {
	if(isAdd()) {
		executeRowAdd(dataGridView1, dataGridView2);
	}else if (feedback == DEL_SUCCESS) {
		changeDeletedRowColour(dataGridView1, dataGridView2);
	}else if (feedback == UNDO_ADD) {
		taskList.clear();
		taskList = dataContainer.getMainList();
		executeRowAdd(dataGridView1, dataGridView2);
		changeDeletedRowColour(dataGridView1, dataGridView2);
	}

	return;
}

bool FormAction::isAdd() {
	return ((feedback == ADD_SUCCESS) || (feedback == SEARCH_SUCCESS) || 
		    (feedback == UNDO_DELETE) || (feedback == UPD_SUCCESS) || 
			(feedback == UNDO_UPD) || (feedback == MARK_SUCCESS) || 
			(feedback == UNDO_MARK) || (feedback == LOAD_SUCCESS) ||
			(feedback == MAIN) || (feedback == UNMARK_SUCCESS));
}

//This method add rows to both the main task table and wish list table
void FormAction::executeRowAdd(DataGridView^ dataGridView1, DataGridView^  dataGridView2) {
	int mainRowTracker = FIRST_RUN;
	int floatRowTracker = FIRST_RUN;

	for(int index=0; index< taskList.size(); index++) {
		//Only main tasks have deadlines
		if(isDeadLinePresent(taskList[index])) {
			if(mainRowTracker == FIRST_RUN) {
				dataGridView1->Rows->Clear();
				mainRowTracker++;
			}
			addRowToMainTask(taskList[index], dataGridView1);
			//Highlight newly added task in light green
			if(isNewTask(index)) {
				changeRowColour(dataGridView1);
			}
		}else {
			if(floatRowTracker == FIRST_RUN) {
				dataGridView2->Rows->Clear();
				floatRowTracker++;
			}
			addRowToFloatTask(taskList[index], dataGridView2);
		}
	}
	return;
}

//This method clears the table and add the rows back to the table excluding the deleted task
void FormAction::executeRowDelete(DataGridView^ dataGridView1, DataGridView^  dataGridView2) {
	int mainRowTracker = FIRST_RUN;
	int floatRowTracker = FIRST_RUN;

	if(taskList.size() == NO_TASK) {
		clearRow(dataGridView1, dataGridView2);
	}else {
		for(int i=0; i< taskList.size(); i++) {
			if(isDeadLinePresent(taskList[i])) {
				if(mainRowTracker == FIRST_RUN) {
					dataGridView1->Rows->Clear();
				}
				addRowToMainTask(taskList[i], dataGridView1);
				mainRowTracker++;
			}else {
				if(floatRowTracker == FIRST_RUN) {
					dataGridView2->Rows->Clear();
				}
				addRowToFloatTask(taskList[i], dataGridView2);
				floatRowTracker++;
			}
		}
	}
	changeCompletedAndExpiredTaskRowColour(dataGridView1);

	return;
}

//Clears the status message before each user operation
void FormAction::resetStatusMessage(Label^ status) {
	status->Text = "";
}

//This method facilitates the process of displaying appropriate help balloons depending on how many current
//tasks are there in the main task table and wish list table
void FormAction::setRowCount(int mainRowCount, int floatRowCount) {
	this->mainRowCount = mainRowCount;
	this->floatRowCount = floatRowCount;
}

//This method displays help balloons based on the row counts and user input
void FormAction::showBalloon(array<ToolTip^>^ toolTipArray, TextBox^ textBox1, Label^ dummyTasks, Label^ dummyWL, MonthCalendar^ calendarDisplay, HelpType typeOfHelp) {
	ToolTip^ textBoxTT = toolTipArray[0];
	ToolTip^ tasksTT = toolTipArray[1];
	ToolTip^ wlTT = toolTipArray[2];
	ToolTip^ calendarTT = toolTipArray[3];

	if(typeOfHelp == START_HELP && mainRowCount == NO_TASK && floatRowCount == NO_TASK) {
		textBoxTT->Show("You may start by adding a task using this textbox.\n" + 
						"Type add for further guidance.\n" + 
						"Type enable/disable help to enable or disable help balloons.", 
						textBox1, 
						260, 10);
		tasksTT->Show("This table contains all your tasks with time and deadlines.", dummyTasks, 0, 0);
		wlTT->Show("This table contains your wish list, with no time constraint.", dummyWL, 0, 0);
		calendarTT->Show("This calendar shows your added tasks' dates in bold.", calendarDisplay, 40, 150);

	}else if(typeOfHelp == START_HELP && mainRowCount > NO_TASK) {
		textBoxTT->Show("Type one of the following command for further instructions.\n" + 
						"add, delete, update, search, undo, mark.\n", textBox1, 230, 10);
	}
	
	if(typeOfHelp == ADD_HELP){
		textBoxTT->Show("To add to main task, \n" + 
						"type \"add [Task Name] [Day OR Date] [Time Duration]\"\n" +
						"e.g. add attend party friday OR 11 nov 3pm-5pm\n" +
						"To add to wish list, \n" + 
						"type \"add wl [Task Name]\"\n",
						textBox1,
						310, 10);

	}else if(typeOfHelp == DELETE_HELP) {

		if(mainRowCount > NO_TASK && floatRowCount > NO_TASK) {
			textBoxTT->Show("To delete from main task, \n" + 
							"type \"delete [Table Index]\"\n" +
							"e.g. delete 3\n" +
							"To delete from wish list, \n" + 
							"type \"delete wl [Table Index]\"\n",
							textBox1,
							230, 10);

		}else if(mainRowCount > NO_TASK && floatRowCount == NO_TASK) {
			textBoxTT->Show("You may only delete from main task.\n" + 
							"To delete from main task, \n" + 
							"type \"delete [Table Index]\"\n" +
							"e.g. delete 3\n",
							textBox1,
							230, 10);

		}else if(mainRowCount == NO_TASK && floatRowCount > NO_TASK) {
			textBoxTT->Show("You may only delete from wish list.\n" + 
							"To delete from wish list, \n" + 
							"type \"delete wl [Table Index]\"\n" + 
							"e.g. delete wl 3\n",
							textBox1,
							230, 10);

		}else {
			textBoxTT->Show("There are no task to be deleted.\n", textBox1, 230, 10);
		}

	}else if(typeOfHelp == UPDATE_HELP) {
		if(mainRowCount > 0) {
			textBoxTT->Show("To update main task, \n" + 
							"type \"update [Table Index] [New Task Name] [Day OR Date] [Time Duration]\"\n" +
							"e.g. update 3 attend summer party friday OR 11 nov 3pm-5pm\n",
							textBox1,
							230, 10);
		}else {
			textBoxTT->Show("There are no task to be updated.\n", textBox1, 230, 10);
		}

	}else if(typeOfHelp == SEARCH_HELP) {
		textBoxTT->Show("To search, \n" + 
						"type \"search [Keyword] OR [Day OR Date]\"\n" +
						"e.g. search party\n",
						textBox1,
						230, 10);

	}else if(typeOfHelp == UNDO_HELP) {
		textBoxTT->Show("To undo, \n" + 
						"type \"undo\"\n" +
						"Previous action will be undone.\n",
						textBox1,
						230, 10);

	}else if(typeOfHelp == MARK_HELP) {
		textBoxTT->Show("To mark pending task as done OR done task to pending, \n" + 
						"type \"mark [Table Index]\"\n",
						textBox1,
						230, 10);
	}

	return;
}

FormAction::~FormAction() {
	if(convertFrom != NULL) {
		delete convertFrom;
	}
}

void FormAction::addRowToMainTask(Task* currentTask, DataGridView^ dataGridView1) {
	int rowCount = dataGridView1->RowCount;
	String^ rowNumber;
	String^ taskName;
	String^ taskDate;
	String^ time;
	String^ taskDeadLine;
	String^ taskStatus;

	getRowNumber(rowCount, rowNumber);
	getTaskName(currentTask, taskName);
	determineTaskDate(currentTask, taskDate);
	determineTimeAndDeadline(currentTask, time, taskDeadLine);
	determineTaskStatus(currentTask, taskStatus);

	array<String^>^ rowToBeAdded = gcnew array<String^>
	{rowNumber, taskName, taskDate, time, taskDeadLine, taskStatus};

	dataGridView1->Rows->Add(rowToBeAdded);

	return;
}

void FormAction::addRowToFloatTask(Task* currentTask, DataGridView^  dataGridView2) {
	int rowCount = dataGridView2->RowCount;
	String^ rowNumber;
	String^ taskName;

	getRowNumber(rowCount, rowNumber);
	getTaskName(currentTask, taskName);

	array<String^>^ rowToBeAdded = gcnew array<String^> {rowNumber, taskName};
	dataGridView2->Rows->Add(rowToBeAdded);

	return;
}

void FormAction::getRowNumber(int rowCount, String^& rowNumber) {
	rowNumber = convertFrom->intToString(++rowCount) + ".";

	return;
}

void FormAction::getTaskName(Task* currentTask, String^ &taskName) {
	taskName = convertFrom->stdToSysString(currentTask->getName());

	return;
}

void FormAction::determineTaskDate(Task* currentTask, String^& taskDate) {
	if(currentTask->isToday()) {
		taskDate = "Today";
	}else {
		taskDate = convertFrom->dateToString(currentTask->getDeadLine());
	}

	return;
}

void FormAction::determineTimeAndDeadline(Task* currentTask, String^& time, String^ &taskDeadLine) {
	String^ startTime = convertFrom->timeToString(currentTask->getStartTime());
	String^ endTime = convertFrom->timeToString(currentTask->getEndTime());

	if(isEvent(currentTask)) {
		time = mergeTime(startTime, endTime);
		taskDeadLine = convertFrom->stdToSysString(NULL_TIME);
	}else {
		time = convertFrom->stdToSysString(NULL_TIME);
		taskDeadLine = mergeTime(startTime, endTime);
	}

	return;
}

void FormAction::determineTaskStatus(Task* currentTask, String^& taskStatus) {
	if(currentTask->isMarked()) {
		taskStatus = "Done";
	}else if(currentTask->isExpired()) {
		taskStatus = "Expired";
	}else {
		taskStatus = "Pending";
	}

	return;
}

void FormAction::clearRow(DataGridView^ dataGridView1, DataGridView^ dataGridView2) {
	if (mainTaskChange) {
		dataGridView1->Rows->Clear();
	}else if (floatTaskChange) {
		dataGridView2->Rows->Clear();
	}

	return;
}

//This method displays different kind of feedbacks to the user about the way they enter commands
void FormAction::displayOperationMessage(UserFeedback feedback, Label^ status) {
	switch (feedback) {
		case ADD_SUCCESS:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, ADD_SUCCESS_MESSAGE);
			break;		
		case DEL_SUCCESS:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, DELETE_SUCCESS_MESSAGE);
			break;
		case UNDO_ADD:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, UNDO_ADD_SUCCESS_MESSAGE);
			break;
		case UNDO_DELETE:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, UNDO_DELETE_SUCCESS_MESSAGE);
			break;
		case SEARCH_SUCCESS:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, SEARCH_SUCCESS_MESSAGE);
			break;
		case NIL:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_COMMAND_MESSAGE);
			break;
		case UPD_SUCCESS:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, UPDATE_SUCCESS_MESSAGE);
			break;
		case DEL_FAIL:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, DELETE_FAIL_MESSAGE);
			break;
		case UNDO_UPD:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, UNDO_UPDATE_SUCCESS_MESSAGE);
			break;
		case MARK_SUCCESS:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, MARK_SUCCESS_MESSAGE);
			break;
		case LOAD_SUCCESS:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, LOAD_SUCCESS_MESSAGE);
			break;
		case UNDO_MARK:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, UNDO_MARK_SUCCESS_MESSAGE);
			break;
		case MAIN:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, BACK_TO_MAIN_MESSAGE);
			break;
		case UNMARK_SUCCESS:
			changeStatusForegroundColour(status, Color::GreenYellow);
			changeStatusMessage(status, UNMARK_SUCCESS_MESSAGE);
			break;
		case EMPTY_SEARCH:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, EMPTY_SEARCH_MESSAGE);
			break;
		case INVALID_NO_NAME:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_NO_NAME_MESSAGE);
			break;
		case INVALID_TIME_FORMAT:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_TIME_FORMAT_MESSAGE);
			break;
		case INVALID_TIME:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_TIME_MESSAGE);
			break;
		case INVALID_DATE_PASSED:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_DATE_PASSED_MESSAGE);
			break;
		case INVALID_DATE:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_DATE_MESSAGE);
			break;
		case INVALID_DURATION:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_DURATION_MESSAGE);
			break;
		case INVALID_POSITION:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_POSITION_MESSAGE);
			break;
		case INVALID_DEL_COMMAND:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_DEL_COMMAND_MESSAGE);
			break;
		case INVALID_NO_COMMAND:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_NO_COMMAND_MESSAGE);
			break;
		default:
			changeStatusForegroundColour(status, Color::Red);
			changeStatusMessage(status, INVALID_COMMAND_MESSAGE);
			break;
	}

	return;
}

//This method colour codes the feedbacks to indicate whether or not the operation done previously is valid
void FormAction::changeStatusForegroundColour(Label^ status, Color colour) {
	status->ForeColor = colour;

	return;
}

void FormAction::changeStatusMessage(Label^ status, std::string message) {
	status->Text = convertFrom->stdToSysString(message);

	return;
}

bool FormAction::isNewTask(int index) {
	return (index == newPosition && feedback != SEARCH_SUCCESS);
}

void FormAction::changeRowColour(DataGridView^ dataGridView) {
	int currentRowIndex = FIRST_ROW;
	IEnumerator^ dataGridEnumerator;
	DataGridViewRow^ currentRow;

	//Clear selection to prevent uneven back color change
	dataGridView->ClearSelection();

	dataGridEnumerator = safe_cast<IEnumerable^>(dataGridView->Rows)->GetEnumerator();

	//If newly added task's position is zero, there is no need to loop through the rows
	if(newPosition == 0) {
		dataGridEnumerator->MoveNext();
		currentRow = safe_cast<DataGridViewRow^>(dataGridEnumerator->Current);
		currentRow->HeaderCell->Value = String::Format(L"Row {0}", currentRowIndex);
	}else {
		while(dataGridEnumerator->MoveNext()) {
			currentRow = safe_cast<DataGridViewRow^>(dataGridEnumerator->Current);
			currentRow->HeaderCell->Value = String::Format(L"Row {0}", currentRowIndex);
			currentRowIndex++;
		}
	}
	determineColourChange(currentRow);

	return;
}

void FormAction::changeDeletedRowColour(DataGridView^ dataGridView1, DataGridView^ dataGridView2) {
	int currentRowIndex = FIRST_ROW;
	int currentVectorIndex = FIRST_POSITION;
	int loopCount = 0;
	IEnumerator^ dataGridEnumerator;
	String^ taskName;
	DataGridViewRow^ currentRow;

	//Clear selection to prevent uneven back color change
	dataGridView1->ClearSelection();
	dataGridView2->ClearSelection();

	//Set the enumerator depending on which DGV to change
	dataGridEnumerator = setDataGridEnumerator(dataGridView1, dataGridView2);

	//Looping is not necessary when position is zero, the first row must be the deleted one
	if(newPosition == FIRST_POSITION) {
		dataGridEnumerator->MoveNext();
		currentRow = safe_cast<DataGridViewRow^>(dataGridEnumerator->Current);
		currentRow->HeaderCell->Value = String::Format(L"Row {0}", currentRowIndex);
	}else {
		while(dataGridEnumerator->MoveNext() && loopCount <= newPosition) {
			currentRow = safe_cast<DataGridViewRow^>(dataGridEnumerator->Current);
			currentRow->HeaderCell->Value = String::Format(L"Row {0}", currentRowIndex);
			loopCount++;
			currentRowIndex++;
		}
	}

	changeBackgroundColour(currentRow, Color::Red);

	//If there is a deletion in main task table, change status to deleted
	if(mainTaskChange) {
		changeDeletedTaskStatus(currentRow);
	}

	//Update task list with deleted vector, because the next action will delete it
	taskList.clear();
	taskList = dataContainer.getTaskList();

	return;
}

void FormAction::changeCompletedAndExpiredTaskRowColour(DataGridView^ dataGridView) {
	int currentRowIndex = FIRST_ROW;
	IEnumerator^ dataGridEnumerator;
	DataGridViewRow^ currentRow;

	//Clear selection to prevent uneven back color change
	dataGridView->ClearSelection();

	dataGridEnumerator = safe_cast<IEnumerable^>(dataGridView->Rows)->GetEnumerator();

	//Loop through the rows to find done and expired task to highlight them accordingly
	while(dataGridEnumerator->MoveNext()) {
		currentRow = safe_cast<DataGridViewRow^>(dataGridEnumerator->Current);
		currentRow->HeaderCell->Value = String::Format(L"Row {0}", currentRowIndex);

		if(isTaskDone(currentRow)) {
			changeBackgroundColour(currentRow, Color::LightSkyBlue);

		}else if(isTaskExpired(currentRow)) {
			changeBackgroundColour(currentRow, Color::Fuchsia);
		}
		currentRowIndex++;
	}
}

//This method sets the enumerator to appropriate tables for further manipulation 
IEnumerator^ FormAction::setDataGridEnumerator(DataGridView^ dataGridView1, DataGridView^ dataGridView2) {
	if(mainTaskChange) {
		return safe_cast<IEnumerable^>(dataGridView1->Rows)->GetEnumerator();
	}else if(floatTaskChange){
		return safe_cast<IEnumerable^>(dataGridView2->Rows)->GetEnumerator();
	}
}

String^ FormAction::determineCurrentRowTaskName(DataGridView^ dataGridView1, DataGridView^ dataGridView2, int currentRowIndex) {
	if(mainTaskChange) {
		return dataGridView1->Rows[--currentRowIndex]->Cells[TASK_NAME_COLUMN]->Value->ToString();
	}else if(floatTaskChange) {
		return dataGridView2->Rows[--currentRowIndex]->Cells[TASK_NAME_COLUMN]->Value->ToString();
	}
}

bool FormAction::isTaskDone(DataGridViewRow^ currentRow) {
	return (currentRow->Cells[TASK_STATUS_COLUMN]->Value->ToString() == "Done");
}

bool FormAction::isTaskExpired(DataGridViewRow^ currentRow) {
	return (currentRow->Cells[TASK_STATUS_COLUMN]->Value->ToString() == "Expired");
}

bool FormAction::isDeadLinePresent(Task* currentTask) {
	String^ taskDeadLine = convertFrom->dateToString(currentTask->getDeadLine());

	//Floating tasks have no deadlines
	return (convertFrom->sysToStdString(taskDeadLine) != DEAD_LINE);
}

bool FormAction::isEvent(Task* currentTask) {
	String^ startTime = convertFrom->timeToString(currentTask->getStartTime());

	//Events have starting time
	return (startTime != convertFrom->stdToSysString(NO_START_TIME));
}

String^ FormAction::mergeTime(String^ startTime, String^ endTime) {
	String^ time;
	if(startTime == convertFrom->stdToSysString(NO_START_TIME)) {
		time = endTime;
	}else {
		time = startTime + convertFrom->stdToSysString(TIME_SEPARATOR) + endTime;
	}

	return time;
}

void FormAction::determineColourChange(DataGridViewRow^ currentRow) {
	if(feedback == ADD_SUCCESS || feedback == UNDO_DELETE) {
		changeBackgroundColour(currentRow, Color::LightGreen);
	}else if(feedback == UPD_SUCCESS || feedback == UNDO_UPD) {
		changeBackgroundColour(currentRow, Color::Yellow);
	}

	return;
}

void FormAction::changeBackgroundColour(DataGridViewRow^ currentRow, Color colour) {
	currentRow->DefaultCellStyle->BackColor = colour;

	return;
}

void FormAction::changeDeletedTaskStatus(DataGridViewRow^ currentRow) {
	currentRow->Cells[TASK_STATUS_COLUMN]->Value = "Deleted";

	return;
}

//This method bolds the pending tasks in the table according to their dates
void FormAction::boldTaskDates(DataGridView^ dataGridView, MonthCalendar^ calendarDisplay) {
	int currentRowIndex = FIRST_ROW;
	IEnumerator^ dataGridEnumerator;
	DataGridViewRow^ currentRow;
	String^ currentRowDate;

	//Clear selection to prevent uneven back color change
	dataGridView->ClearSelection();

	dataGridEnumerator = safe_cast<IEnumerable^>(dataGridView->Rows)->GetEnumerator();

	//Loop through the table's date column and bold it's date on the calendar
	while(dataGridEnumerator->MoveNext()) {
		currentRow = safe_cast<DataGridViewRow^>(dataGridEnumerator->Current);
		currentRow->HeaderCell->Value = String::Format(L"Row {0}", currentRowIndex);
		currentRowDate = dataGridView->Rows[currentRowIndex-1]->Cells[TASK_DATE_COLUMN]->Value->ToString();

		if(currentRow->Cells[TASK_STATUS_COLUMN]->Value != "Deleted" && 
		   currentRow->Cells[TASK_STATUS_COLUMN]->Value != "Expired" &&
		   currentRow->Cells[TASK_STATUS_COLUMN]->Value != "Done") {
			//DateTime variable is immutable after creation, therefore a direct function call is necessary
			calendarDisplay->AddBoldedDate(convertFrom->sysStringToDateTime(currentRowDate));
		}
		currentRowIndex++;
	}
	calendarDisplay->UpdateBoldedDates();

	return;
}