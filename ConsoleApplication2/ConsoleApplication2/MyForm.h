#pragma once
#include "Windows.h"
#include "time.h"
#define PI 3.14159265
int xxx = 0;
int Samples = 0;
int sigma = 0;
int mean = 0;
/*int _tmain(int argc, _TCHAR* argv[])
{
double m[3] = { 0, 1, 2 };
double s[3] = { 1, 1, 0.0001 };
double p[3] = { 0 };
double sum = 0;
srand(time(NULL));
rand();
calc_wp(3, m, s, p);
//printf("%.10f\n",acos(-1.0));
for (int i = 0; i < 3; i++)	printf("平均值:%f 標準差:%f 曲線下面積:%f\n", m[i], s[i], p[i]);
for (int i = 0; i < 3; i++) sum += p[i];
printf("P = %f\n", sum);
return 0;
}*/

const int qSize = 30;
int iterations = 1000000;
int initialStates[qSize] = { 23, 22, 21, 20, 19, 18, 24, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
int Count[qSize][qSize];
double Q[qSize][qSize];
double Q2[qSize][qSize];
float UCB[qSize][qSize];

int TCount[qSize];
double V[qSize];
double V2[qSize];

int R[qSize][qSize] = { /* -1, 1, 2, 3, 4, 5, 6, 7, 8, 9,1-1,11,12,13,14,15,16,17,18,19,2-1,21,22,23,24,25,26,27,28,29 */
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //0
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //1
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //2
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //3
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //4
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //5
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //6
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //7
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //8
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //9
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //110
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //11
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //12
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //13
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //14
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //15
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //16
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //17
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //18
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -100, 0, 0, 0, 0 }, //19
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -100, 0, 0, 0 }, //20
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -100, 0, 0 }, //21
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -100, 0 }, //22
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 500 }, //23
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -100, 0, 0, 0, 0 }, //24
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //25
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //26
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //27
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //28
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -100, 0 }, //29
};

int Move_State[qSize][qSize] = { /* -1, 1, 2, 3, 4, 5, 6, 7, 8, 9,1-1,11,12,13,14,15,16,17,18,19,2-1,21,22,23,24,25,26,27,28,29 */
	{ -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //0
	{ -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //1
	{ -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //2
	{ -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //3
	{ -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //4
	{ -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //5
	{ -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //6
	{ -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //7
	{ -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //8
	{ -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //9
	{ -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //110
	{ -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //11
	{ -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //12
	{ -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //13
	{ -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2, -2 }, //14
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2, -2 }, //15
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -2 }, //16
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2 }, //17
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2 }, //18
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2 }, //19
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2 }, //20
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2, -2 }, //21
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2, -2, -1, -2 }, //22
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -1 }, //23
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2 }, //24
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2, -2 }, //25
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2, -2 }, //26
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1, -2 }, //27
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2, -1 }, //28
	{ -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -1, -2, -2, -2, -2, -1, -2 }, //29
};


double episode(int currentState, int step);
void initialize();
float Rvalue(int currentState, int nextState, int step);
bool x[31];
void StartTest();


namespace ConsoleApplication2 {


	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}
		/*
		void Left()
		{
			int x = DD->Location.X;
			int y = DD->Location.Y;
			DD->Location = Point(x - 100, y);
		}
		void Right()
		{
			int x = DD->Location.X;
			int y = DD->Location.Y;
			DD->Location = Point(x + 100, y);
		}
		void Up()
		{
			int x = DD->Location.X;
			int y = DD->Location.Y;
			DD->Location = Point(x, y - 100);
		}
		void Down()
		{
			int x = DD->Location.X;
			int y = DD->Location.Y;
			DD->Location = Point(x, y + 100);
		}
		*/
		void run(int currentState, int nextState)
		{
			
			
			switch (currentState)
			{
			case 0:lb0->Text =xxx.ToString();break;
			case 1:lb1->Text =xxx.ToString(); break;
			case 2:lb2->Text = xxx.ToString(); break;
			case 3:lb3->Text = xxx.ToString(); break;
			case 4:lb4->Text = xxx.ToString(); break;
			case 5:lb5->Text = xxx.ToString();  break;
			case 6:lb6->Text = xxx.ToString(); break;
			case 7:lb7->Text = xxx.ToString(); break;
			case 8:lb8->Text = xxx.ToString(); break;
			case 9:lb9->Text = xxx.ToString(); break;
			case 10:lb10->Text = xxx.ToString(); break;
			case 11:lb11->Text = xxx.ToString(); break;
			case 12:lb12->Text = xxx.ToString(); break;
			case 13:lb13->Text = xxx.ToString(); break;
			case 14:lb14->Text = xxx.ToString(); break;
			case 15:lb15->Text = xxx.ToString(); break;
			case 16:lb16->Text = xxx.ToString(); break;
			case 17:lb17->Text = xxx.ToString(); break;
			case 18:lb18->Text = xxx.ToString(); break;
			case 19:lb19->Text = xxx.ToString(); break;
			case 20:lb20->Text = xxx.ToString(); break;
			case 21:lb21->Text = xxx.ToString(); break;
			case 22:lb22->Text = xxx.ToString(); break;
			case 23:lb23->Text = xxx.ToString(); break;
			case 25:lb25->Text = xxx.ToString(); break;
			case 26:lb26->Text = xxx.ToString(); break;
			case 27:lb27->Text = xxx.ToString(); break;
			case 28:lb28->Text = xxx.ToString(); break;
			case 29:lb29->Text = xxx.ToString(); break;
				/*
				case 0:lb0->Text =int(V[currentState]/TCount[currentState]).ToString();break;
				case 1:lb1->Text =int(V[currentState]/TCount[currentState]).ToString(); break;
				case 2:lb2->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 3:lb3->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 4:lb4->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 5:lb5->Text =int (V[currentState]/TCount[currentState]).ToString();  break;
				case 6:lb6->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 7:lb7->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 8:lb8->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 9:lb9->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 10:lb10->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 11:lb11->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 12:lb12->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 13:lb13->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 14:lb14->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 15:lb15->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 16:lb16->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 17:lb17->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 18:lb18->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 19:lb19->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 20:lb20->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 21:lb21->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 22:lb22->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 23:lb23->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 25:lb25->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 26:lb26->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 27:lb27->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 28:lb28->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				case 29:lb29->Text =int (V[currentState]/TCount[currentState]).ToString(); break;
				*/
			}
			xxx++;
			
			/*
			switch (direction[currentState][nextState])
			{
			case 'N':
				Up();
				break;
			case 'W':
				Left();
				break;
			case 'E':
				Right();
				break;
			case 'S':
				Down();
				break;
			}
			*/
		}
	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
				
			}
		}
	private: System::Windows::Forms::Button^  button1;
	public:
		System::Windows::Forms::Label^  lb0;
		System::Windows::Forms::Label^  lb1;
		System::Windows::Forms::Label^  lb2;
		System::Windows::Forms::Label^  lb5;
		System::Windows::Forms::Label^  lb4;
		System::Windows::Forms::Label^  lb3;
		System::Windows::Forms::Label^  lb11;
		System::Windows::Forms::Label^  lb10;
		System::Windows::Forms::Label^  lb9;
		System::Windows::Forms::Label^  lb8;
		System::Windows::Forms::Label^  lb7;
		System::Windows::Forms::Label^  lb6;
		System::Windows::Forms::Label^  lb17;
		System::Windows::Forms::Label^  lb16;
		System::Windows::Forms::Label^  lb15;
		System::Windows::Forms::Label^  lb14;
		System::Windows::Forms::Label^  lb13;
		System::Windows::Forms::Label^  lb12;
		System::Windows::Forms::Label^  lb23;
		System::Windows::Forms::Label^  lb22;
		System::Windows::Forms::Label^  lb21;
		System::Windows::Forms::Label^  lb20;
		System::Windows::Forms::Label^  lb19;
		System::Windows::Forms::Label^  lb18;
		System::Windows::Forms::Label^  lb29;
		System::Windows::Forms::Label^  lb25;
		System::Windows::Forms::Label^  lb27;
		System::Windows::Forms::Label^  lb26;
		System::Windows::Forms::Label^  lb24;
		System::Windows::Forms::Label^  lb28;
private: System::Windows::Forms::Label^  label2;
		 System::Windows::Forms::PictureBox^  pictureBox1;
		 System::Windows::Forms::TextBox^  show_time;
		 System::Windows::Forms::PictureBox^  pictureBox2;
		 System::Windows::Forms::TextBox^  input;
		 System::Windows::Forms::Label^  h4;
		 System::Windows::Forms::Label^  label1;
		 System::Windows::Forms::Label^  label3;
		 System::Windows::Forms::Label^  label4;
		 System::Windows::Forms::Panel^  panel1;
		 System::Windows::Forms::TextBox^  source;
		 System::Windows::Forms::Label^  label5;
		 System::Windows::Forms::Panel^  panel2;
		 System::Windows::Forms::Panel^  panel4;
		 System::Windows::Forms::Panel^  panel3;
		 System::Windows::Forms::Panel^  panel5;
		 System::Windows::Forms::Panel^  panel6;
		 System::Windows::Forms::Panel^  panel7;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::TextBox^  Number_Samples;
private: System::Windows::Forms::TextBox^  M;
private: System::Windows::Forms::TextBox^  S;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label8;
		 System::ComponentModel::Container ^components;
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::TextBox^  Message;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->lb0 = (gcnew System::Windows::Forms::Label());
			this->lb1 = (gcnew System::Windows::Forms::Label());
			this->lb2 = (gcnew System::Windows::Forms::Label());
			this->lb5 = (gcnew System::Windows::Forms::Label());
			this->lb4 = (gcnew System::Windows::Forms::Label());
			this->lb3 = (gcnew System::Windows::Forms::Label());
			this->lb11 = (gcnew System::Windows::Forms::Label());
			this->lb10 = (gcnew System::Windows::Forms::Label());
			this->lb9 = (gcnew System::Windows::Forms::Label());
			this->lb8 = (gcnew System::Windows::Forms::Label());
			this->lb7 = (gcnew System::Windows::Forms::Label());
			this->lb6 = (gcnew System::Windows::Forms::Label());
			this->lb17 = (gcnew System::Windows::Forms::Label());
			this->lb16 = (gcnew System::Windows::Forms::Label());
			this->lb15 = (gcnew System::Windows::Forms::Label());
			this->lb14 = (gcnew System::Windows::Forms::Label());
			this->lb13 = (gcnew System::Windows::Forms::Label());
			this->lb12 = (gcnew System::Windows::Forms::Label());
			this->lb23 = (gcnew System::Windows::Forms::Label());
			this->lb22 = (gcnew System::Windows::Forms::Label());
			this->lb21 = (gcnew System::Windows::Forms::Label());
			this->lb20 = (gcnew System::Windows::Forms::Label());
			this->lb19 = (gcnew System::Windows::Forms::Label());
			this->lb18 = (gcnew System::Windows::Forms::Label());
			this->lb29 = (gcnew System::Windows::Forms::Label());
			this->lb25 = (gcnew System::Windows::Forms::Label());
			this->lb27 = (gcnew System::Windows::Forms::Label());
			this->lb26 = (gcnew System::Windows::Forms::Label());
			this->lb24 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->input = (gcnew System::Windows::Forms::TextBox());
			this->show_time = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->h4 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->source = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->lb28 = (gcnew System::Windows::Forms::Label());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->Number_Samples = (gcnew System::Windows::Forms::TextBox());
			this->M = (gcnew System::Windows::Forms::TextBox());
			this->S = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			Message = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel4->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel6->SuspendLayout();
			this->panel7->SuspendLayout();
			this->SuspendLayout();
			// 
			// Message
			// 
			Message->BackColor = System::Drawing::SystemColors::ActiveBorder;
			Message->Font = (gcnew System::Drawing::Font(L"新細明體", 15));
			Message->Location = System::Drawing::Point(678, 435);
			Message->Multiline = true;
			Message->Name = L"Message";
			Message->ReadOnly = true;
			Message->Size = System::Drawing::Size(269, 154);
			Message->TabIndex = 100;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(663, 16);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(284, 124);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// lb0
			// 
			this->lb0->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb0->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb0->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb0->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb0.Image")));
			this->lb0->Location = System::Drawing::Point(26, 112);
			this->lb0->Name = L"lb0";
			this->lb0->Size = System::Drawing::Size(100, 100);
			this->lb0->TabIndex = 68;
			this->lb0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb1
			// 
			this->lb1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb1->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb1.Image")));
			this->lb1->Location = System::Drawing::Point(123, 112);
			this->lb1->Name = L"lb1";
			this->lb1->Size = System::Drawing::Size(100, 100);
			this->lb1->TabIndex = 69;
			this->lb1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb2
			// 
			this->lb2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb2->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb2->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb2.Image")));
			this->lb2->Location = System::Drawing::Point(222, 112);
			this->lb2->Name = L"lb2";
			this->lb2->Size = System::Drawing::Size(100, 100);
			this->lb2->TabIndex = 70;
			this->lb2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb5
			// 
			this->lb5->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb5->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb5->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb5.Image")));
			this->lb5->Location = System::Drawing::Point(521, 112);
			this->lb5->Name = L"lb5";
			this->lb5->Size = System::Drawing::Size(100, 100);
			this->lb5->TabIndex = 73;
			this->lb5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb4
			// 
			this->lb4->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb4->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb4->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb4.Image")));
			this->lb4->Location = System::Drawing::Point(421, 112);
			this->lb4->Name = L"lb4";
			this->lb4->Size = System::Drawing::Size(100, 100);
			this->lb4->TabIndex = 72;
			this->lb4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb3
			// 
			this->lb3->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb3->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb3->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb3.Image")));
			this->lb3->Location = System::Drawing::Point(321, 112);
			this->lb3->Name = L"lb3";
			this->lb3->Size = System::Drawing::Size(100, 100);
			this->lb3->TabIndex = 71;
			this->lb3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb11
			// 
			this->lb11->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb11->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb11->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb11->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb11.Image")));
			this->lb11->Location = System::Drawing::Point(521, 212);
			this->lb11->Name = L"lb11";
			this->lb11->Size = System::Drawing::Size(100, 100);
			this->lb11->TabIndex = 79;
			this->lb11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb10
			// 
			this->lb10->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb10->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb10->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb10.Image")));
			this->lb10->Location = System::Drawing::Point(421, 212);
			this->lb10->Name = L"lb10";
			this->lb10->Size = System::Drawing::Size(100, 100);
			this->lb10->TabIndex = 78;
			this->lb10->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb9
			// 
			this->lb9->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb9->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb9->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb9.Image")));
			this->lb9->Location = System::Drawing::Point(321, 212);
			this->lb9->Name = L"lb9";
			this->lb9->Size = System::Drawing::Size(100, 100);
			this->lb9->TabIndex = 77;
			this->lb9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb8
			// 
			this->lb8->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb8->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb8->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb8.Image")));
			this->lb8->Location = System::Drawing::Point(222, 212);
			this->lb8->Name = L"lb8";
			this->lb8->Size = System::Drawing::Size(100, 100);
			this->lb8->TabIndex = 76;
			this->lb8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb7
			// 
			this->lb7->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb7->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb7->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb7.Image")));
			this->lb7->Location = System::Drawing::Point(123, 212);
			this->lb7->Name = L"lb7";
			this->lb7->Size = System::Drawing::Size(100, 100);
			this->lb7->TabIndex = 75;
			this->lb7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb6
			// 
			this->lb6->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb6->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb6->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb6.Image")));
			this->lb6->Location = System::Drawing::Point(26, 212);
			this->lb6->Name = L"lb6";
			this->lb6->Size = System::Drawing::Size(100, 100);
			this->lb6->TabIndex = 74;
			this->lb6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb17
			// 
			this->lb17->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb17->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb17->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb17->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb17.Image")));
			this->lb17->Location = System::Drawing::Point(521, 312);
			this->lb17->Name = L"lb17";
			this->lb17->Size = System::Drawing::Size(100, 100);
			this->lb17->TabIndex = 85;
			this->lb17->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb16
			// 
			this->lb16->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb16->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb16->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb16->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb16.Image")));
			this->lb16->Location = System::Drawing::Point(421, 312);
			this->lb16->Name = L"lb16";
			this->lb16->Size = System::Drawing::Size(100, 100);
			this->lb16->TabIndex = 84;
			this->lb16->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb15
			// 
			this->lb15->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb15->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb15->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb15->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb15.Image")));
			this->lb15->Location = System::Drawing::Point(321, 312);
			this->lb15->Name = L"lb15";
			this->lb15->Size = System::Drawing::Size(100, 100);
			this->lb15->TabIndex = 83;
			this->lb15->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb14
			// 
			this->lb14->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb14->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb14->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb14->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb14.Image")));
			this->lb14->Location = System::Drawing::Point(222, 312);
			this->lb14->Name = L"lb14";
			this->lb14->Size = System::Drawing::Size(100, 100);
			this->lb14->TabIndex = 82;
			this->lb14->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb13
			// 
			this->lb13->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb13->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb13->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb13->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb13.Image")));
			this->lb13->Location = System::Drawing::Point(123, 312);
			this->lb13->Name = L"lb13";
			this->lb13->Size = System::Drawing::Size(100, 100);
			this->lb13->TabIndex = 81;
			this->lb13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb12
			// 
			this->lb12->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb12->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb12->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb12->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb12.Image")));
			this->lb12->Location = System::Drawing::Point(26, 312);
			this->lb12->Name = L"lb12";
			this->lb12->Size = System::Drawing::Size(100, 100);
			this->lb12->TabIndex = 80;
			this->lb12->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb23
			// 
			this->lb23->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb23->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb23->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb23->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb23.Image")));
			this->lb23->Location = System::Drawing::Point(521, 412);
			this->lb23->Name = L"lb23";
			this->lb23->Size = System::Drawing::Size(100, 100);
			this->lb23->TabIndex = 91;
			this->lb23->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb22
			// 
			this->lb22->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb22->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb22->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb22->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb22.Image")));
			this->lb22->Location = System::Drawing::Point(421, 412);
			this->lb22->Name = L"lb22";
			this->lb22->Size = System::Drawing::Size(100, 100);
			this->lb22->TabIndex = 90;
			this->lb22->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb21
			// 
			this->lb21->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb21->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb21->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb21->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb21.Image")));
			this->lb21->Location = System::Drawing::Point(321, 412);
			this->lb21->Name = L"lb21";
			this->lb21->Size = System::Drawing::Size(100, 100);
			this->lb21->TabIndex = 89;
			this->lb21->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb20
			// 
			this->lb20->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb20->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb20->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb20->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb20.Image")));
			this->lb20->Location = System::Drawing::Point(222, 412);
			this->lb20->Name = L"lb20";
			this->lb20->Size = System::Drawing::Size(100, 100);
			this->lb20->TabIndex = 88;
			this->lb20->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb19
			// 
			this->lb19->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb19->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb19->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb19->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb19.Image")));
			this->lb19->Location = System::Drawing::Point(123, 412);
			this->lb19->Name = L"lb19";
			this->lb19->Size = System::Drawing::Size(100, 100);
			this->lb19->TabIndex = 87;
			this->lb19->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb18
			// 
			this->lb18->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->lb18->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb18->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb18->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb18.Image")));
			this->lb18->Location = System::Drawing::Point(26, 412);
			this->lb18->Name = L"lb18";
			this->lb18->Size = System::Drawing::Size(100, 100);
			this->lb18->TabIndex = 86;
			this->lb18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb29
			// 
			this->lb29->BackColor = System::Drawing::Color::Transparent;
			this->lb29->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb29->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb29->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb29.Image")));
			this->lb29->Location = System::Drawing::Point(0, 0);
			this->lb29->Name = L"lb29";
			this->lb29->Size = System::Drawing::Size(100, 100);
			this->lb29->TabIndex = 97;
			this->lb29->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb25
			// 
			this->lb25->BackColor = System::Drawing::Color::Transparent;
			this->lb25->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb25->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb25->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb25.Image")));
			this->lb25->Location = System::Drawing::Point(0, 0);
			this->lb25->Name = L"lb25";
			this->lb25->Size = System::Drawing::Size(100, 100);
			this->lb25->TabIndex = 96;
			this->lb25->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb27
			// 
			this->lb27->BackColor = System::Drawing::Color::Transparent;
			this->lb27->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb27->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb27->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb27.Image")));
			this->lb27->Location = System::Drawing::Point(0, 0);
			this->lb27->Name = L"lb27";
			this->lb27->Size = System::Drawing::Size(100, 100);
			this->lb27->TabIndex = 95;
			this->lb27->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb26
			// 
			this->lb26->BackColor = System::Drawing::Color::Transparent;
			this->lb26->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb26->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb26->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb26.Image")));
			this->lb26->Location = System::Drawing::Point(0, 0);
			this->lb26->Name = L"lb26";
			this->lb26->Size = System::Drawing::Size(100, 100);
			this->lb26->TabIndex = 93;
			this->lb26->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lb24
			// 
			this->lb24->BackColor = System::Drawing::Color::Transparent;
			this->lb24->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb24->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb24->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb24.Image")));
			this->lb24->Location = System::Drawing::Point(0, 0);
			this->lb24->Name = L"lb24";
			this->lb24->Size = System::Drawing::Size(100, 100);
			this->lb24->TabIndex = 92;
			this->lb24->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(623, 88);
			this->label2->TabIndex = 101;
			this->label2->Text = L"Epsilon Greedy";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::LightGreen;
			this->pictureBox1->Location = System::Drawing::Point(659, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(293, 612);
			this->pictureBox1->TabIndex = 102;
			this->pictureBox1->TabStop = false;
			// 
			// input
			// 
			this->input->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->input->Location = System::Drawing::Point(725, 187);
			this->input->Name = L"input";
			this->input->Size = System::Drawing::Size(177, 39);
			this->input->TabIndex = 103;
			this->input->Text = L"10000";
			this->input->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// show_time
			// 
			this->show_time->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->show_time->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->show_time->Location = System::Drawing::Point(725, 245);
			this->show_time->Multiline = true;
			this->show_time->Name = L"show_time";
			this->show_time->ReadOnly = true;
			this->show_time->Size = System::Drawing::Size(177, 33);
			this->show_time->TabIndex = 104;
			this->show_time->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::LightGreen;
			this->pictureBox2->Location = System::Drawing::Point(12, 12);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(623, 612);
			this->pictureBox2->TabIndex = 105;
			this->pictureBox2->TabStop = false;
			// 
			// h4
			// 
			this->h4->AutoSize = true;
			this->h4->BackColor = System::Drawing::Color::Khaki;
			this->h4->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->h4->Location = System::Drawing::Point(908, 199);
			this->h4->Name = L"h4";
			this->h4->Size = System::Drawing::Size(39, 27);
			this->h4->TabIndex = 106;
			this->h4->Text = L"次";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Khaki;
			this->label1->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label1->Location = System::Drawing::Point(908, 248);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 27);
			this->label1->TabIndex = 107;
			this->label1->Text = L"次";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Khaki;
			this->label3->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label3->Location = System::Drawing::Point(666, 199);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(39, 27);
			this->label3->TabIndex = 108;
			this->label3->Text = L"共";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Khaki;
			this->label4->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label4->Location = System::Drawing::Point(666, 248);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(39, 27);
			this->label4->TabIndex = 109;
			this->label4->Text = L"第";
			// 
			// panel1
			// 
			this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel1.BackgroundImage")));
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->panel1->Controls->Add(this->label2);
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(623, 88);
			this->panel1->TabIndex = 110;
			// 
			// source
			// 
			this->source->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->source->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->source->Location = System::Drawing::Point(804, 146);
			this->source->Multiline = true;
			this->source->Name = L"source";
			this->source->Size = System::Drawing::Size(143, 33);
			this->source->TabIndex = 111;
			this->source->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"標楷體", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label5->Location = System::Drawing::Point(666, 149);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(138, 27);
			this->label5->TabIndex = 112;
			this->label5->Text = L"平均分數:";
			// 
			// panel2
			// 
			this->panel2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel2.BackgroundImage")));
			this->panel2->Controls->Add(this->lb29);
			this->panel2->Location = System::Drawing::Point(521, 509);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(100, 100);
			this->panel2->TabIndex = 113;
			// 
			// panel4
			// 
			this->panel4->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel4.BackgroundImage")));
			this->panel4->Controls->Add(this->lb28);
			this->panel4->Location = System::Drawing::Point(421, 509);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(100, 100);
			this->panel4->TabIndex = 116;
			// 
			// lb28
			// 
			this->lb28->BackColor = System::Drawing::Color::Transparent;
			this->lb28->Font = (gcnew System::Drawing::Font(L"新細明體", 48, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->lb28->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->lb28->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"lb28.Image")));
			this->lb28->Location = System::Drawing::Point(0, 0);
			this->lb28->Name = L"lb28";
			this->lb28->Size = System::Drawing::Size(100, 100);
			this->lb28->TabIndex = 118;
			this->lb28->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// panel3
			// 
			this->panel3->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel3.BackgroundImage")));
			this->panel3->Controls->Add(this->lb26);
			this->panel3->Location = System::Drawing::Point(222, 509);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(100, 100);
			this->panel3->TabIndex = 117;
			// 
			// panel5
			// 
			this->panel5->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel5.BackgroundImage")));
			this->panel5->Controls->Add(this->lb27);
			this->panel5->Location = System::Drawing::Point(321, 509);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(100, 100);
			this->panel5->TabIndex = 117;
			// 
			// panel6
			// 
			this->panel6->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel6.BackgroundImage")));
			this->panel6->Controls->Add(this->lb25);
			this->panel6->Location = System::Drawing::Point(123, 509);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(100, 100);
			this->panel6->TabIndex = 118;
			// 
			// panel7
			// 
			this->panel7->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel7.BackgroundImage")));
			this->panel7->Controls->Add(this->lb24);
			this->panel7->Location = System::Drawing::Point(26, 509);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(100, 100);
			this->panel7->TabIndex = 119;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label6->Location = System::Drawing::Point(666, 303);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(100, 27);
			this->label6->TabIndex = 120;
			this->label6->Text = L"樣本數:";
			// 
			// Number_Samples
			// 
			this->Number_Samples->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->Number_Samples->Location = System::Drawing::Point(780, 291);
			this->Number_Samples->Name = L"Number_Samples";
			this->Number_Samples->Size = System::Drawing::Size(122, 39);
			this->Number_Samples->TabIndex = 121;
			this->Number_Samples->Text = L"0";
			this->Number_Samples->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// M
			// 
			this->M->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->M->Location = System::Drawing::Point(780, 336);
			this->M->Name = L"M";
			this->M->Size = System::Drawing::Size(122, 39);
			this->M->TabIndex = 122;
			this->M->Text = L"0";
			this->M->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// S
			// 
			this->S->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->S->Location = System::Drawing::Point(780, 381);
			this->S->Name = L"S";
			this->S->Size = System::Drawing::Size(122, 39);
			this->S->TabIndex = 123;
			this->S->Text = L"0";
			this->S->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label7->Location = System::Drawing::Point(666, 348);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(100, 27);
			this->label7->TabIndex = 124;
			this->label7->Text = L"平均值:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"新細明體", 20));
			this->label8->Location = System::Drawing::Point(666, 393);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(100, 27);
			this->label8->TabIndex = 125;
			this->label8->Text = L"標準差:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Khaki;
			this->ClientSize = System::Drawing::Size(959, 628);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->S);
			this->Controls->Add(this->M);
			this->Controls->Add(this->Number_Samples);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel5);
			this->Controls->Add(this->panel7);
			this->Controls->Add(this->panel6);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->source);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->h4);
			this->Controls->Add(this->show_time);
			this->Controls->Add(this->input);
			this->Controls->Add(Message);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->lb23);
			this->Controls->Add(this->lb22);
			this->Controls->Add(this->lb21);
			this->Controls->Add(this->lb20);
			this->Controls->Add(this->lb19);
			this->Controls->Add(this->lb18);
			this->Controls->Add(this->lb17);
			this->Controls->Add(this->lb16);
			this->Controls->Add(this->lb15);
			this->Controls->Add(this->lb14);
			this->Controls->Add(this->lb13);
			this->Controls->Add(this->lb12);
			this->Controls->Add(this->lb11);
			this->Controls->Add(this->lb10);
			this->Controls->Add(this->lb9);
			this->Controls->Add(this->lb8);
			this->Controls->Add(this->lb7);
			this->Controls->Add(this->lb6);
			this->Controls->Add(this->lb5);
			this->Controls->Add(this->lb4);
			this->Controls->Add(this->lb3);
			this->Controls->Add(this->lb2);
			this->Controls->Add(this->lb1);
			this->Controls->Add(this->lb0);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->pictureBox2);
			this->Name = L"MyForm";
			this->Text = L"Reinforcement Learning";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->panel7->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		void StartTest(){
			int sum = 0;
			int newState;

			initialize();
			for (int i = 0; i < iterations; i++)
			{
				
				show_time->Text =  (i + 1).ToString();
				for (int j = 0; j < 30; j++) x[j] = 0;
				x[24] = 1;

				sum += episode(24, 0);
				Control::Refresh();
				MSG msg;
				if (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
				{
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
					
				}
				source->Text = (sum / (i + 1)).ToString();
				//if (TCount[28]>0)Message->Text = (V[28] / TCount[28]).ToString();
				/*
				if (Count[18][19]>0)Message->Text += "\r\n" + "18->19: " + int(Q[18][19] / Count[18][19]).ToString() + "\t***" + Count[18][19].ToString();
				if (Count[19][20]>0)Message->Text += "\r\n" + "19->20: " + int(Q[19][20] / Count[19][20]).ToString() + "\t***" + Count[19][20].ToString();
				if (Count[20][21]>0)Message->Text += "\r\n" + "20->21: " + int(Q[20][21] / Count[20][21]).ToString() + "\t***" + Count[20][21].ToString();
				if (Count[21][22]>0)Message->Text += "\r\n" + "21->22: " + int(Q[21][22] / Count[21][22]).ToString() + "\t***" + Count[21][22].ToString();
				if (Count[22][23]>0)Message->Text += "\r\n" + "22->23: " + int(Q[22][23] / Count[22][23]).ToString() + "\t***" + Count[22][23].ToString();
				*/

				if(i<iterations-1)Reset();
			}

		}
		void Reset(){
			xxx = 0;
		//	DD->Location = Point(44, 461);
			/*
			lb0->BackColor = SystemColors::ActiveCaption;
			lb1->BackColor = SystemColors::ActiveCaption;
			lb2->BackColor = SystemColors::ActiveCaption;
			lb3->BackColor = SystemColors::ActiveCaption;
			lb4->BackColor = SystemColors::ActiveCaption;
			lb5->BackColor = SystemColors::ActiveCaption;
			lb6->BackColor = SystemColors::ActiveCaption;
			lb7->BackColor = SystemColors::ActiveCaption;
			lb8->BackColor = SystemColors::ActiveCaption;
			lb9->BackColor = SystemColors::ActiveCaption;
			lb10->BackColor = SystemColors::ActiveCaption;
			lb11->BackColor = SystemColors::ActiveCaption;
			lb12->BackColor = SystemColors::ActiveCaption;
			lb13->BackColor = SystemColors::ActiveCaption;
			lb14->BackColor = SystemColors::ActiveCaption;
			lb15->BackColor = SystemColors::ActiveCaption;
			lb16->BackColor = SystemColors::ActiveCaption;
			lb17->BackColor = SystemColors::ActiveCaption;
			lb18->BackColor = SystemColors::ActiveCaption;
			lb19->BackColor = SystemColors::ActiveCaption;
			lb20->BackColor = SystemColors::ActiveCaption;
			lb21->BackColor = SystemColors::ActiveCaption;
			lb22->BackColor = SystemColors::ActiveCaption;
			lb23->BackColor = SystemColors::ActiveCaption;
			lb25->BackColor = SystemColors::ActiveCaptionText;
			lb26->BackColor = SystemColors::ActiveCaptionText;
			lb27->BackColor = SystemColors::ActiveCaptionText;
			lb28->BackColor = SystemColors::ActiveCaptionText;
			lb29->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
				*/
			lb0->Text = "";
			lb1->Text = "";
			lb2->Text = "";
			lb3->Text = "";
			lb4->Text = "";
			lb5->Text = "";
			lb6->Text = "";
			lb7->Text = "";
			lb8->Text = "";
			lb9->Text = "";
			lb10->Text = "";
			lb11->Text = "";
			lb12->Text = "";
			lb13->Text = "";
			lb14->Text = "";
			lb15->Text = "";
			lb16->Text = "";
			lb17->Text = "";
			lb18->Text = "";
			lb19->Text = "";
			lb20->Text = "";
			lb21->Text = "";
			lb22->Text = "";
			lb23->Text = "";
			lb25->Text = "";
			lb26->Text = "";
			lb27->Text = "";
			lb28->Text = "";
			lb29->Text = "";
		}
		int randS(int currentState)
		{
			int n = 0;
			int X[4];
			for (int i = 0; i < qSize; i++)	if (Move_State[currentState][i] != -2 && x[i] == 0) X[n++] = i;
			if (n == 0) return -1;
			return X[rand() % n];
		}
		int maxS(int currentState)
		{
			float maxQ;
			int n = 0;
			int s = currentState;
			for (int i = 0; i < qSize; i++)
			if (Move_State[currentState][i] != -2 && x[i] == 0)
			{
				n++;
				if (s == currentState || Q[currentState][i] / Count[currentState][i] >maxQ)
				{
					s = i;
					maxQ = Q[currentState][i] / Count[currentState][i];
				}
			}
			if (n == 0) return -1;
			return s;
		}
		double episode(int currentState, int step)
		{
			double r = 0;
			int X[4];
			int n = 0;
			int nextState = -1;
			if (currentState == 29){ r = 500; run(currentState, nextState); }
			else if (currentState == 28 || currentState == 27 || currentState == 26 || currentState == 25){ r = -100; run(currentState, nextState); }
			else
			{
			for (int i = 0; i < qSize; i++)	if (Move_State[currentState][i] != -2 && Count[currentState][i] == 0 && x[i] == 0) X[n++] = i;
			if (n >= 1) nextState = X[rand() % n];
				else //n=0 
				{

					if (rand()*1.0 / RAND_MAX >0.95) nextState = randS(currentState);
					else nextState = maxS(currentState);
				}
				if (nextState == -1) { r = -30; }
				else
					{
						run(currentState, nextState);
						x[nextState] = 1;
						//r = R[currentState][nextState] + episode(nextState, step + 1) - 5;
						r = episode(nextState, step + 1) - 5;
						Count[currentState][nextState]++;
						Q[currentState][nextState] += r;
						Q2[currentState][nextState] += r * r;
					}
				}
			TCount[currentState]++;
			V[currentState] += r;
			V2[currentState] += (r * r);
			return r;
		}
		void initialize()
		{
			Reset();
			srand((unsigned)time(NULL));
			//srand(100);
			rand();
			for (int i = 0; i < qSize; i++)
			{
				 TCount[i]=V[i]=V2[i]=0;
				 for (int j = 0; j < qSize; j++)  Q[i][j] = Q2[i][j] = Count[i][j] = 0;
			}
			
		}
#pragma endregion
	public: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				
				button1->Enabled = false;
				iterations = int::Parse(input->Text);
				Samples = int::Parse(this->Number_Samples->Text);
				mean = int::Parse(this->M->Text);
				sigma = int::Parse(this->S->Text);
				StartTest();
				button1->Enabled = true;
	}


};
}

