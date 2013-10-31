#include "stdafx.h"
#include "Reminder.h"

const std::string Reminder::URGENT_TITLE = "Urgent!";
const std::string Reminder::PENDING_TITLE = "Pending Tasks!";


Reminder::Reminder() {
	convertFrom = new DataConverter;
	isUrgent = false;
	numberOfUrgentTasks = ZERO;
	numberOfPendingTasks = ZERO;
	hourLeft = ZERO;
	minutesLeft = ZERO;
}

//This method is invoked by the events in the windows form to display appropriate balloons when
//the form is minimised
void Reminder::determineReminderToDisplay(NotifyIcon^ trayIcon, DataGridView^ dataGridView1) {
	int currentRowIndex = FIRST_ROW;
	IEnumerator^ dataGridEnumerator;
	DataGridViewRow^ currentRow;

	dataGridEnumerator = safe_cast<IEnumerable^>(dataGridView1->Rows)->GetEnumerator();

	while(dataGridEnumerator->MoveNext()) {
		currentRow = safe_cast<DataGridViewRow^>(dataGridEnumerator->Current);
		currentRow->HeaderCell->Value = String::Format(L"Row {0}", currentRowIndex);

		//The balloon only displays notifications for today's task
		if(currentRow->Cells[TASK_DATE_COLUMN]->Value->ToString() == "Today") {

			//Task must be pending and have less than an hour before deadline to be declared urgent
			if((isPendingTask(currentRow)) && (isUrgentTask(currentRow))) {
				isUrgent = true;
				numberOfUrgentTasks++;
			}

			if(isPendingTask(currentRow)) {
				numberOfPendingTasks++;
			}
		}
		currentRowIndex++;
	}
	displayNotification(trayIcon);

	return;
}

Reminder::~Reminder() {
	delete convertFrom;
}

void Reminder::displayNotification(NotifyIcon^ trayIcon) {
	
	//Priority is given to urgent tasks for displaying of notifications
	if(isUrgent) {
		displayUrgentBalloon(trayIcon);
	}else if (numberOfPendingTasks != ZERO) {
		displayPendingBalloon(trayIcon);
	}

	return;
}

void Reminder::displayUrgentBalloon(NotifyIcon^ trayIcon) {
	trayIcon->BalloonTipTitle = convertFrom->stdToSysString(URGENT_TITLE);
	if(hourLeft == ZERO && minutesLeft < 55){
		trayIcon->BalloonTipText = "There are task(s) with about " + convertFrom->intToString(minutesLeft) + " minutes left before deadline.";
	}else if(hourLeft >= 1){
		trayIcon->BalloonTipText = "There are task(s) with about 1 hour left.";
	}
	trayIcon->ShowBalloonTip(ONE_SECOND);

	return;
}

void Reminder::displayPendingBalloon(NotifyIcon^ trayIcon) {
	trayIcon->BalloonTipTitle = convertFrom->stdToSysString(PENDING_TITLE);
	trayIcon->BalloonTipText = convertFrom->intToString(numberOfPendingTasks) + " task(s) left for today.";
	trayIcon->ShowBalloonTip(ONE_SECOND);

	return;
}

bool Reminder::isUrgentTask(DataGridViewRow^ currentRow) {
	String^ currentRowTime = currentRow->Cells[TASK_DEADLINE_COLUMN]->Value->ToString();
	if(currentRowTime == "-") {
		return false;
	} 
	DateTime rowDateTime = convertFrom->sysStringToDateTimeWithMinutes(currentRowTime);
	DateTime currentDateTime = DateTime::Now;
	TimeSpan timeDiff = rowDateTime - currentDateTime;

	if(timeDiff.Hours == ZERO && timeDiff.Minutes > ZERO) {
		minutesLeft = timeDiff.Minutes;
		return true;
	}else if(timeDiff.Hours > 1 && timeDiff.Minutes < 5) {
		hourLeft = timeDiff.Hours;
		return true;
	}else {
		return false;
	}
}

bool Reminder::isPendingTask(DataGridViewRow^ currentRow) {
	return (currentRow->Cells[TASK_STATUS_COLUMN]->Value->ToString() == "Pending");
}