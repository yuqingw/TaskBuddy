#include "Logic.h"
#include "DataConverter.h"
#include "Task.h"
#include "DataFeedback.h"
#include "FormAction.h"
#include "Log.h"
#include "Reminder.h"
#include <string>
#include <vector>

#pragma once

namespace TaskBuddy {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void) {
			InitializeComponent();
			Form1::MaximizeBox = false;
			textBox1->Focus();

			TextBoxTT->SetToolTip(textBox1, "Enter Command Here");
			TasksTT->SetToolTip(DummyTasks, "Timed Tasks");
			WLTT->SetToolTip(DummyWL, "Wish List");
			CalendarTT->SetToolTip(monthCalendar1, "Calendar");

			ReminderTimer->Interval = 5000;
			pastTime = DateTime::Now;
			taskBalloonTime = DateTime::Now;

			perform = NULL;
			ptrToLogic = new Logic;
			convertFrom = new DataConverter;

			isHelpEnabled = true;
			isHelp = false;
			isAtBackGround = false;

			Help->ForeColor = Color::GreenYellow;
			Help->Text = "Help Enabled";
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1() {
			if (components) {
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^  components;
	protected: 
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

	private: FormAction* perform;
	private: Logic* ptrToLogic;
	private: DataConverter* convertFrom;
	private: UserFeedback feedback;
	private: System::Boolean isHelpEnabled;
	private: System::Boolean isHelp;
	private: System::Boolean isAtBackGround;
	private: System::DateTime taskBalloonTime;
	private: System::DateTime pastTime;
	private: System::Windows::Forms::Label^  Command;
	private: System::Windows::Forms::Label^  Tasks;
	private: System::Windows::Forms::Label^  Status;
	private: System::Windows::Forms::Label^  FloatingTasks;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridView^  dataGridView2;
	private: System::Windows::Forms::MonthCalendar^  monthCalendar1;
	private: System::Windows::Forms::Label^  StatusDisplay;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Number_Floating;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Floating_Task;
	private: System::Windows::Forms::ToolTip^  TextBoxTT;
	private: System::Windows::Forms::ToolTip^  TasksTT;
	private: System::Windows::Forms::Label^  DummyTasks;
	private: System::Windows::Forms::Label^  DummyWL;
	private: System::Windows::Forms::ToolTip^  WLTT;
	private: System::Windows::Forms::ToolTip^  CalendarTT;






	private: System::Windows::Forms::Label^  Help;
	private: System::Windows::Forms::NotifyIcon^  TrayIcon;
	private: System::Windows::Forms::Timer^  ReminderTimer;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Number;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  TaskName;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Date;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Time;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  DeadLine;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  TaskStatus;
	private: System::Windows::Forms::Timer^  MinimizeTimer;


















	private: System::Windows::Forms::TextBox^  textBox1;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void) {
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle4 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->Number = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TaskName = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Date = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Time = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->DeadLine = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->TaskStatus = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Command = (gcnew System::Windows::Forms::Label());
			this->Tasks = (gcnew System::Windows::Forms::Label());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->Number_Floating = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Floating_Task = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Status = (gcnew System::Windows::Forms::Label());
			this->FloatingTasks = (gcnew System::Windows::Forms::Label());
			this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
			this->StatusDisplay = (gcnew System::Windows::Forms::Label());
			this->TextBoxTT = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->TasksTT = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->DummyTasks = (gcnew System::Windows::Forms::Label());
			this->DummyWL = (gcnew System::Windows::Forms::Label());
			this->WLTT = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->CalendarTT = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->Help = (gcnew System::Windows::Forms::Label());
			this->TrayIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->ReminderTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->MinimizeTimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView2))->BeginInit();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::Window;
			this->textBox1->Location = System::Drawing::Point(14, 437);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(632, 23);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::textBox1_KeyDown);
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &Form1::textBox1_KeyPress);
			// 
			// dataGridView1
			// 
			this->dataGridView1->AllowUserToAddRows = false;
			this->dataGridView1->AllowUserToDeleteRows = false;
			this->dataGridView1->AllowUserToResizeColumns = false;
			this->dataGridView1->AllowUserToResizeRows = false;
			this->dataGridView1->BackgroundColor = System::Drawing::Color::Snow;
			this->dataGridView1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {this->Number, 
				this->TaskName, this->Date, this->Time, this->DeadLine, this->TaskStatus});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView1->DefaultCellStyle = dataGridViewCellStyle2;
			this->dataGridView1->Location = System::Drawing::Point(14, 117);
			this->dataGridView1->MultiSelect = false;
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->dataGridView1->RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->ReadOnly = true;
			this->dataGridView1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView1->Size = System::Drawing::Size(632, 300);
			this->dataGridView1->TabIndex = 1;
			this->dataGridView1->TabStop = false;
			this->dataGridView1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::dataGridView1_MouseClick);
			// 
			// Number
			// 
			this->Number->HeaderText = L"No.";
			this->Number->Name = L"Number";
			this->Number->ReadOnly = true;
			this->Number->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Number->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Number->Width = 30;
			// 
			// TaskName
			// 
			this->TaskName->HeaderText = L"Task Name";
			this->TaskName->Name = L"TaskName";
			this->TaskName->ReadOnly = true;
			this->TaskName->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->TaskName->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->TaskName->Width = 240;
			// 
			// Date
			// 
			this->Date->HeaderText = L"Date";
			this->Date->Name = L"Date";
			this->Date->ReadOnly = true;
			this->Date->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Date->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Date->Width = 75;
			// 
			// Time
			// 
			this->Time->HeaderText = L"Time";
			this->Time->Name = L"Time";
			this->Time->ReadOnly = true;
			this->Time->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Time->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Time->Width = 130;
			// 
			// DeadLine
			// 
			this->DeadLine->HeaderText = L"DeadLine";
			this->DeadLine->Name = L"DeadLine";
			this->DeadLine->ReadOnly = true;
			this->DeadLine->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->DeadLine->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->DeadLine->Width = 70;
			// 
			// TaskStatus
			// 
			this->TaskStatus->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->TaskStatus->HeaderText = L"Status";
			this->TaskStatus->Name = L"TaskStatus";
			this->TaskStatus->ReadOnly = true;
			this->TaskStatus->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->TaskStatus->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Command
			// 
			this->Command->AutoSize = true;
			this->Command->BackColor = System::Drawing::Color::Transparent;
			this->Command->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Command->ForeColor = System::Drawing::Color::White;
			this->Command->Location = System::Drawing::Point(10, 419);
			this->Command->Name = L"Command";
			this->Command->Size = System::Drawing::Size(134, 13);
			this->Command->TabIndex = 2;
			this->Command->Text = L"Enter Command Here: ";
			// 
			// Tasks
			// 
			this->Tasks->AutoSize = true;
			this->Tasks->BackColor = System::Drawing::Color::Transparent;
			this->Tasks->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Tasks->ForeColor = System::Drawing::Color::White;
			this->Tasks->Location = System::Drawing::Point(10, 101);
			this->Tasks->Name = L"Tasks";
			this->Tasks->Size = System::Drawing::Size(41, 13);
			this->Tasks->TabIndex = 3;
			this->Tasks->Text = L"Tasks";
			// 
			// dataGridView2
			// 
			this->dataGridView2->AllowUserToAddRows = false;
			this->dataGridView2->AllowUserToDeleteRows = false;
			this->dataGridView2->AllowUserToResizeColumns = false;
			this->dataGridView2->AllowUserToResizeRows = false;
			this->dataGridView2->BackgroundColor = System::Drawing::Color::Snow;
			this->dataGridView2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->Number_Floating, 
				this->Floating_Task});
			dataGridViewCellStyle4->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle4->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle4->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			dataGridViewCellStyle4->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle4->SelectionBackColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle4->SelectionForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle4->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView2->DefaultCellStyle = dataGridViewCellStyle4;
			this->dataGridView2->Location = System::Drawing::Point(669, 37);
			this->dataGridView2->MultiSelect = false;
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->ReadOnly = true;
			this->dataGridView2->RowHeadersVisible = false;
			this->dataGridView2->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dataGridView2->Size = System::Drawing::Size(227, 246);
			this->dataGridView2->TabIndex = 4;
			this->dataGridView2->TabStop = false;
			this->dataGridView2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::dataGridView2_MouseClick);
			// 
			// Number_Floating
			// 
			this->Number_Floating->HeaderText = L"No.";
			this->Number_Floating->Name = L"Number_Floating";
			this->Number_Floating->ReadOnly = true;
			this->Number_Floating->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Number_Floating->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Number_Floating->Width = 30;
			// 
			// Floating_Task
			// 
			this->Floating_Task->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Floating_Task->HeaderText = L"Task Name";
			this->Floating_Task->Name = L"Floating_Task";
			this->Floating_Task->ReadOnly = true;
			this->Floating_Task->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Floating_Task->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			// 
			// Status
			// 
			this->Status->AutoSize = true;
			this->Status->BackColor = System::Drawing::Color::Transparent;
			this->Status->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Status->Location = System::Drawing::Point(66, 463);
			this->Status->Name = L"Status";
			this->Status->Size = System::Drawing::Size(0, 13);
			this->Status->TabIndex = 5;
			// 
			// FloatingTasks
			// 
			this->FloatingTasks->AutoSize = true;
			this->FloatingTasks->BackColor = System::Drawing::Color::Transparent;
			this->FloatingTasks->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FloatingTasks->ForeColor = System::Drawing::Color::White;
			this->FloatingTasks->Location = System::Drawing::Point(666, 21);
			this->FloatingTasks->Name = L"FloatingTasks";
			this->FloatingTasks->Size = System::Drawing::Size(59, 13);
			this->FloatingTasks->TabIndex = 6;
			this->FloatingTasks->Text = L"Wish List";
			// 
			// monthCalendar1
			// 
			this->monthCalendar1->ForeColor = System::Drawing::SystemColors::WindowText;
			this->monthCalendar1->Location = System::Drawing::Point(669, 298);
			this->monthCalendar1->Margin = System::Windows::Forms::Padding(10, 12, 10, 12);
			this->monthCalendar1->MaxSelectionCount = 1;
			this->monthCalendar1->Name = L"monthCalendar1";
			this->monthCalendar1->ShowTodayCircle = false;
			this->monthCalendar1->TabIndex = 7;
			// 
			// StatusDisplay
			// 
			this->StatusDisplay->AutoSize = true;
			this->StatusDisplay->BackColor = System::Drawing::Color::Transparent;
			this->StatusDisplay->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->StatusDisplay->ForeColor = System::Drawing::Color::White;
			this->StatusDisplay->Location = System::Drawing::Point(10, 463);
			this->StatusDisplay->Name = L"StatusDisplay";
			this->StatusDisplay->Size = System::Drawing::Size(51, 13);
			this->StatusDisplay->TabIndex = 8;
			this->StatusDisplay->Text = L"Status: ";
			// 
			// TextBoxTT
			// 
			this->TextBoxTT->AutoPopDelay = 1000;
			this->TextBoxTT->InitialDelay = 500;
			this->TextBoxTT->IsBalloon = true;
			this->TextBoxTT->ReshowDelay = 100;
			// 
			// TasksTT
			// 
			this->TasksTT->IsBalloon = true;
			// 
			// DummyTasks
			// 
			this->DummyTasks->AutoSize = true;
			this->DummyTasks->Location = System::Drawing::Point(14, 151);
			this->DummyTasks->Name = L"DummyTasks";
			this->DummyTasks->Size = System::Drawing::Size(0, 15);
			this->DummyTasks->TabIndex = 9;
			// 
			// DummyWL
			// 
			this->DummyWL->AutoSize = true;
			this->DummyWL->Location = System::Drawing::Point(669, 68);
			this->DummyWL->Name = L"DummyWL";
			this->DummyWL->Size = System::Drawing::Size(0, 15);
			this->DummyWL->TabIndex = 10;
			// 
			// WLTT
			// 
			this->WLTT->IsBalloon = true;
			// 
			// CalendarTT
			// 
			this->CalendarTT->AutoPopDelay = 1000;
			this->CalendarTT->InitialDelay = 500;
			this->CalendarTT->IsBalloon = true;
			this->CalendarTT->ReshowDelay = 100;
			// 
			// Help
			// 
			this->Help->AutoSize = true;
			this->Help->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->Help->Location = System::Drawing::Point(565, 419);
			this->Help->Name = L"Help";
			this->Help->Size = System::Drawing::Size(41, 13);
			this->Help->TabIndex = 11;
			this->Help->Text = L"label1";
			// 
			// TrayIcon
			// 
			this->TrayIcon->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"TrayIcon.Icon")));
			this->TrayIcon->Visible = true;
			this->TrayIcon->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::TrayIcon_MouseDoubleClick);
			// 
			// ReminderTimer
			// 
			this->ReminderTimer->Enabled = true;
			this->ReminderTimer->Tick += gcnew System::EventHandler(this, &Form1::ReminderTimer_Tick);
			// 
			// MinimizeTimer
			// 
			this->MinimizeTimer->Tick += gcnew System::EventHandler(this, &Form1::MinimizeTimer_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoValidate = System::Windows::Forms::AutoValidate::EnablePreventFocusChange;
			this->BackColor = System::Drawing::Color::DarkSlateGray;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(912, 489);
			this->Controls->Add(this->Help);
			this->Controls->Add(this->DummyWL);
			this->Controls->Add(this->DummyTasks);
			this->Controls->Add(this->StatusDisplay);
			this->Controls->Add(this->monthCalendar1);
			this->Controls->Add(this->FloatingTasks);
			this->Controls->Add(this->Status);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->Tasks);
			this->Controls->Add(this->Command);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->textBox1);
			this->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"TaskBuddy";
			this->Activated += gcnew System::EventHandler(this, &Form1::Form1_Activated);
			this->Deactivate += gcnew System::EventHandler(this, &Form1::Form1_Deactivate);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Move += gcnew System::EventHandler(this, &Form1::Form1_Move);
			this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
    //@author A0088643U
	//Event handling
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

				 //Load main task table from file
				 DataFeedback dataContainer (LOAD_SUCCESS, ptrToLogic->getInitialTimedDisplay(), 0);
				 perform = new FormAction(dataContainer);
				 feedback = perform->startExecution(dataGridView1, dataGridView2, Status, monthCalendar1);
				 delete perform;

				 //Load wish list from file
				 DataFeedback dataContainer2 (LOAD_SUCCESS, ptrToLogic->getInitialFloatDisplay() ,0);
				 perform = new FormAction(dataContainer2);
				 feedback = perform->startExecution(dataGridView1, dataGridView2, Status, monthCalendar1);
				 delete perform;

				 feedback = NIL;
			 }

	private: System::Void textBox1_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
				 //Handles everything after "enter" key press
				 if((e->KeyChar == (char)(Keys::Enter))) {
					 
					 //To prevent beeping sound
					 e->Handled = true;

					 //pastTime is renewed with current time with every user action
					 //prevent unnecessary refresh of the screen when user is using the form
					 pastTime = DateTime::Now;

					 checkDeleteAndUndoAdd();
					 hideAllBalloons();

					 Log write;
					 String^ userEnteredInBox = textBox1->Text;
					 std::string userEntered = convertFrom->sysToStdString(userEnteredInBox);
					 write.writeLogToFile(userEntered,"Input");

					 //Exiting the form with command
					 if(userEntered == "exit") {
						 this->Close();
						 return;
					 }

					 DataFeedback dataContainer = ptrToLogic->analyseInput(userEntered);
					 perform = new FormAction(dataContainer);

					 //Setting disable or enable help
					 if(isHelpEnabled && userEntered == "help") {
						 array<ToolTip^> ^ toolTipArray = gcnew array<ToolTip^>
						 {TextBoxTT,TasksTT, WLTT, CalendarTT};

						 perform->setRowCount(dataGridView1->RowCount, dataGridView2->RowCount);
						 perform->showBalloon(toolTipArray, textBox1, DummyTasks, DummyWL, monthCalendar1, START_HELP);
						 delete perform;
						 isHelp = true;
						 textBox1->Clear();
						 return;
					 }else if(userEntered == "enable help") {
						 isHelpEnabled = true;
						 Help->ForeColor = Color::GreenYellow;
						 Help->Text = "Help Enabled";
						 textBox1->Clear();
						 return;
					 }else if(userEntered == "disable help") {
						 isHelpEnabled = false;
						 Help->ForeColor = Color::Red;
						 Help->Text = "Help Disabled";
						 textBox1->Clear();
						 return;
					 }

					 feedback = perform->startExecution(dataGridView1, dataGridView2, Status, monthCalendar1);
					 write.writeLogToFile(convertFrom->sysToStdString(Status->Text),"Output");

					 //Perform cannot be cleared yet until the next user action for deletion
					 if(feedback != DEL_SUCCESS && feedback != UNDO_ADD && userEntered != "help") {
						 delete perform;
					 }

					 textBox1->Clear();
				 }
			 }

	  private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 pastTime = DateTime::Now;

				 //Balloon disappears when user clears the textbox
				 if(textBox1->Text->Length == 0 && !isHelp) {
					 hideAllBalloons();
				 }

				 isHelp = false;

				 //This handles the action done after each operation
				 //Deleting the row task after highlighting as well
				 if(textBox1->Text->Length > 0) {
					 perform->resetStatusMessage(Status);
					 checkDeleteAndUndoAdd();
				 }

				 //Display specific help message based on user's pre-entered command
				 if(isHelpEnabled) {
					 checkHelp();
				 }
			 }

	  private: System::Void textBox1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				   pastTime = DateTime::Now;

				   //Minimizing windows with command
				   if(e->KeyData == (Keys::Control | Keys::M)) {
					   this->WindowState = FormWindowState::Minimized;
				   }

				   //Scrolling for main tasks
				   if(e->KeyData == (Keys::Up)) {
					   //Prevent scrolling out of bounds
					   if(dataGridView1->FirstDisplayedScrollingRowIndex != 0) {
						   dataGridView1->FirstDisplayedScrollingRowIndex = dataGridView1->FirstDisplayedScrollingRowIndex -1;
					   }
				   }else if(e->KeyData == (Keys::Down)) {
					   int num = dataGridView1->FirstDisplayedScrollingRowIndex;
					   dataGridView1->FirstDisplayedScrollingRowIndex = dataGridView1->FirstDisplayedScrollingRowIndex + 1;
				   }

				   //Scrolling for wish list
				   if((e->Control) && (e->KeyCode == Keys::Up)) {
					   if(dataGridView2->FirstDisplayedScrollingRowIndex != 0) {
						   dataGridView2->FirstDisplayedScrollingRowIndex = dataGridView2->FirstDisplayedScrollingRowIndex - 1;
					   }
				   }else if((e->Control) && (e->KeyCode == Keys::Down)) {
					   dataGridView2->FirstDisplayedScrollingRowIndex = dataGridView2->FirstDisplayedScrollingRowIndex + 1;
				   }
			   }

	  private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				   //This will load tasks in TaskBuddy to the files before closing it
				   ptrToLogic->callStorageToLoad();

				   delete convertFrom;
				   delete ptrToLogic;
			   }

	  private: System::Void Form1_Move(System::Object^  sender, System::EventArgs^  e) {
				   //Updating pastime to prevent screen refresh
				   pastTime = DateTime::Now;

				   //Prevents weird balloon behaviour when user drags TaskBuddy from it's original position
				   hideAllBalloons();
			   }

	  private: System::Void Form1_Activated(System::Object^  sender, System::EventArgs^  e) {
				   //Setting the flag to false, to prevent screen refresh when user is performing action
				   isAtBackGround = false;
			   }

	  private: System::Void Form1_Deactivate(System::Object^  sender, System::EventArgs^  e) {
				   //Safety check if the user has performed no action since deleting a row
				   //Row is only highlighted, a real delete execution happens on next user action
				   //Should the form lost focus, this will delete the task
				   checkDeleteAndUndoAdd();
				   
				   //Prevent balloons from overlapping other windows, should the user run TaskBuddy at the background
				   hideAllBalloons();

				   //Setting the background flag to true, for screen to be able to refresh anonymously
				   isAtBackGround = true;
			   }

	  private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				   TrayIcon->BalloonTipTitle = "TaskBuddy";
				   TrayIcon->BalloonTipText = "I'm still here!!";

				   //If the program is minimised, pop a balloon to remind
				   if(this->WindowState == FormWindowState::Minimized) {
					   TrayIcon->Visible = true;
					   TrayIcon->ShowBalloonTip(2000);
					   this->Hide();
				   }else if(this->WindowState == FormWindowState::Normal) {
					   TrayIcon->Visible = false;
				   }

				   //Set up timer for the first notification after minimising program
				   initialiseMinimizerTimer();
			   }

	  private: System::Void TrayIcon_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				   this->Show();
				   this->WindowState =FormWindowState::Normal;
			   }

	  private: System::Void ReminderTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
				   DateTime currentTime = DateTime::Now;

				   if(this->WindowState == FormWindowState::Minimized) {

					   DataFeedback dataContainer = ptrToLogic->analyseInput("back");
					   FormAction* timedPerform = new FormAction(dataContainer);
				       Reminder* remindUser = new Reminder;
					   TimeSpan balloonTimeDiff = currentTime - taskBalloonTime;

					   //Refreshing the screen every 5 seconds the timer ticks
					   timedPerform->startExecution(dataGridView1, dataGridView2, Status, monthCalendar1);
					   timedPerform->resetStatusMessage(Status);
					   
					   //Limit balloon to display hourly
					   if(balloonTimeDiff.Hours >= 1) {
						   remindUser->determineReminderToDisplay(TrayIcon, dataGridView1);
						   taskBalloonTime = DateTime::Now;
					   }

				       delete timedPerform;
				       delete remindUser;

				   }else if (isAtBackGround){

					   TimeSpan idleTime = currentTime - pastTime;
					   //Refreshing the screen after idling for more than 10 seconds
					   if(idleTime.Seconds > 10) {
						   DataFeedback dataContainer = ptrToLogic->analyseInput("back");
						   FormAction* timedPerform = new FormAction(dataContainer);
						   timedPerform->startExecution(dataGridView1, dataGridView2, Status, monthCalendar1);
						   timedPerform->resetStatusMessage(Status);

						   delete timedPerform;
					   }

				   }
			   }

	  private: System::Void MinimizeTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
				   Reminder* remindUser = new Reminder;
				   remindUser->determineReminderToDisplay(TrayIcon, dataGridView1);
				   delete remindUser;

				   //This is to ensure the timer runs only once since minimizing
				   MinimizeTimer->Enabled = false;
			   }

      private: System::Void dataGridView1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				   //Prevent unusual highlighting in the cell rows should the user click on it
				   dataGridView1->ClearSelection();
			   }

      private: System::Void dataGridView2_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				   dataGridView2->ClearSelection();
			   }
	  
	  //Non-events
	  //This method clears the FormAction pointer to prevent memory leak
      private: System::Void checkDeleteAndUndoAdd() {
				   //perform is not cleared for delete success and undoing add
				   //So it has to be cleared at the next user action
				   if(feedback == DEL_SUCCESS || feedback == UNDO_ADD) {
					   perform->executeRowDelete(dataGridView1, dataGridView2);
					   feedback = NIL;
					   delete perform;
				   }
			   }

	  private: System::Void hideAllBalloons() {
				   TasksTT->Hide(DummyTasks);
				   TextBoxTT->Hide(textBox1);
				   WLTT->Hide(DummyWL);
				   CalendarTT->Hide(monthCalendar1);
			   }

	  private: System::Void checkHelp() {
				   //Create managed tooltip array for easy passing into FormAction Method
				   array<ToolTip^> ^ toolTipArray = gcnew array<ToolTip^>
				   {TextBoxTT,TasksTT, WLTT, CalendarTT};

				   FormAction* tempPerform = new FormAction;

				   if(textBox1->Text == "add") {
					   tempPerform = new FormAction;
					   tempPerform->setRowCount(dataGridView1->RowCount, dataGridView2->RowCount);
					   tempPerform->showBalloon(toolTipArray, textBox1, DummyTasks, DummyWL, monthCalendar1, ADD_HELP);

				   }else if(textBox1->Text == "delete") {
					   tempPerform->setRowCount(dataGridView1->RowCount, dataGridView2->RowCount);
					   tempPerform->showBalloon(toolTipArray, textBox1, DummyTasks, DummyWL, monthCalendar1, DELETE_HELP);

				   }else if(textBox1->Text == "update") {
					   tempPerform->setRowCount(dataGridView1->RowCount, dataGridView2->RowCount);
					   tempPerform->showBalloon(toolTipArray, textBox1, DummyTasks, DummyWL, monthCalendar1, UPDATE_HELP);

				   }else if(textBox1->Text == "search") {
					   tempPerform->setRowCount(dataGridView1->RowCount, dataGridView2->RowCount);
					   tempPerform->showBalloon(toolTipArray, textBox1, DummyTasks, DummyWL, monthCalendar1, SEARCH_HELP);

				   }else if(textBox1->Text == "undo") {
					   tempPerform->setRowCount(dataGridView1->RowCount, dataGridView2->RowCount);
					   tempPerform->showBalloon(toolTipArray, textBox1, DummyTasks, DummyWL, monthCalendar1, UNDO_HELP);

				   }else if(textBox1->Text == "mark") {
					   tempPerform->setRowCount(dataGridView1->RowCount, dataGridView2->RowCount);
					   tempPerform->showBalloon(toolTipArray, textBox1, DummyTasks, DummyWL, monthCalendar1, MARK_HELP);

				   }

				   delete tempPerform;
				   return;
			   }

	  private: System::Void initialiseMinimizerTimer() {
				   //This is enable only once since minimising
				   MinimizeTimer->Enabled = true;
				   //Setting the timer interval to 10 seconds
				   MinimizeTimer->Interval = 10000;
			   }
};
};

