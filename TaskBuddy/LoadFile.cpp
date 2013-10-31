#include "stdafx.h"
#include "LoadFile.h"

Task* fileTask;
Task* check;

const string LoadFile::FLOAT_FILE_NAME="floating.txt";
const string LoadFile::EVENT_FILE_NAME="event.txt";

//load floating tasks from file and store them in a vector
vector<Task*> LoadFile::loadFloatTasks(){

	string taskName;
	vector<Task*> tasks;
	textFile.open(FLOAT_FILE_NAME.c_str(), ios::in);
	while (textFile.peek() != EOF){    
			while (getline(textFile, taskName)){
				Task* fileTask = new Task (taskName);
				tasks.push_back(fileTask);}
	}

	textFile.close();	

	return tasks;
}

//load event and deadline tasks from file and store them in a vector
vector<Task*> LoadFile::loadTimedTasks(){

	vector<Task*> timedtasks;
	string taskName, taskInfo;
	int year=0, day =0, month=0, strtHr=0, strtMin=0, endHr=0, endMin=0;
	int mark=0;
	textFile.open(EVENT_FILE_NAME.c_str(), ios::in);
	while (textFile.peek() != EOF){

		while(getline(textFile, taskInfo)){

			taskName=taskInfo;
			getline(textFile, taskInfo);
			istringstream instr(taskInfo);
			instr >> day;
			instr >> month;
			instr >> year;
			instr >> strtHr;
			instr >> strtMin;
			instr >> endHr;
			instr >> endMin;
			instr >> mark;

			TIME startTime;
			startTime.hour = strtHr;
			startTime.min = strtMin;

			TIME endTime;
			endTime.hour = endHr;
			endTime.min = endMin;

			TASK_DATE taskDate;
			taskDate.year = year;
			taskDate.month = month;
			taskDate.day = day;
		
			if (strtHr == 0 && strtMin == 0){

				Task* fileTask = new DeadlineTask(taskName, taskDate, endTime);
				if (mark==1)
					fileTask->changeMark();
				timedtasks.push_back(fileTask);
			}
			else{

				Task* fileTask = new Event(taskName, taskDate, startTime, endTime);
				if (mark==1)
					fileTask->changeMark();
				timedtasks.push_back(fileTask);
			}
		
		}

	}
	textFile.close();	

	return timedtasks;
}

//write all floating tasks to file
void LoadFile:: inputFloatTasksToFile(vector<Task*> &tasks){	
	
	string text;
	textFile.open(FLOAT_FILE_NAME.c_str(), ios::out);

	for (int i=0;i<tasks.size(); i++ ){
	textFile << tasks[i]->getName() << endl; 
	}
	textFile.close();

}
//write all event and deadline tasks to file
void LoadFile:: inputTimedTasksToFile(vector<Task*> &tasks){

	textFile.open(EVENT_FILE_NAME.c_str(), ios::out);
	for(int i=0;i<tasks.size(); i++ ) {

		textFile << tasks[i]->getName() << endl;
		textFile << tasks[i]->getDeadLine().day << " "; 
		textFile << tasks[i]->getDeadLine().month << " ";
		textFile << tasks[i]->getDeadLine().year << " " ;
		textFile << tasks[i]->getStartTime().hour << " ";
		textFile << tasks[i]->getStartTime().min <<" " ;
		textFile << tasks[i]->getEndTime().hour <<" ";
		textFile << tasks[i]->getEndTime().min <<" ";
		textFile << noboolalpha<< tasks[i]->isMarked()<<  endl;
	
	}
	textFile.close();

}