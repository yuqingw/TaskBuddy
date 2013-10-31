//This class is invoked by the timer events and minimising events to constantly remind user
//urgent tasks and pending tasks at a set timed interval of the timer.
//It also takes in the trayicon control's by pointer to manipulate the behaviour of the balloon displayed.
//

#ifndef REMINDER_H
#define REMINDER_H

#include <vector>
#include "DataConverter.h";

using namespace System;
using namespace System::Drawing;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace std;

class Reminder {
private:
	static const int ZERO = 0;
	static const int NO_TODAY_PENDING_TASK = 0;
	static const int FIRST_ROW = 1;
	static const int ONE_SECOND = 1000;

	//Position of columns in the table
	static const int TASK_DATE_COLUMN = 2;
	static const int TASK_DEADLINE_COLUMN = 4;
	static const int TASK_STATUS_COLUMN = 5;

	//Balloon titles
	static const std::string URGENT_TITLE;
	static const std::string PENDING_TITLE;

private:
	DataConverter* convertFrom;
	bool isUrgent;
	int numberOfUrgentTasks;
	int numberOfPendingTasks;
	int hourLeft;
	int minutesLeft;

public:
	Reminder();
	void determineReminderToDisplay(NotifyIcon^ trayIcon, DataGridView^ dataGridView1);
	~Reminder();
private:
	void displayNotification(NotifyIcon^ trayIcon);
	void displayUrgentBalloon(NotifyIcon^ trayIcon);
	void displayPendingBalloon(NotifyIcon^ trayIcon);
	bool isUrgentTask(DataGridViewRow^ currentRow);
	bool isPendingTask(DataGridViewRow^ currentRow);
};

#endif