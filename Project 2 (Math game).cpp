#include<iostream>
#include <cstdlib>
using namespace std;

enum enQsLevel { Easy = 1, Med = 2, Hard = 3, MixL = 4 };
enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };


struct stQuestionInfo
{

	short QuestionNumber;
	short Number1;
	short Number2;
	char OpChar;
	enQsLevel Level;
	enOpType QOpType;
	short RightAnswer;
	short UserAnswer;
	bool RightOrWrong;



};

struct stQuizzInfo
{

	stQuestionInfo arrQuestions[100];
	short HowManyQuestions = 0;
	enQsLevel QuestionsLevel;
	enOpType OpType;
	bool isPass;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;

};

short ReadNumberOfQs();
enQsLevel ReadQuestonsLevel();
stQuestionInfo FillQuestionInfo(stQuestionInfo);
int RandomNumber(int, int);
void GetNumbersAccordingToLevel(stQuestionInfo&);
char GetOpChar(enOpType);
int GetOperationResult(stQuestionInfo);
int UserAnswer();
void ShowPassOrFailHeader(bool);
string GetPassOrFailText(bool);
string GetLevelText(enQsLevel);





enQsLevel ReadQuestonsLevel()
{
	int L;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> L;

	} while (L < 1 || L>4);

	return (enQsLevel)L;
}

enOpType ReadOpType()
{
	int T;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> T;


	} while (T < 1 || T>5);


	return (enOpType)T;



}

short ReadNumberOfQs()
{
	short Qs;

	cout << "How Many Questions do you want to answer ? ";
	cin >> Qs;

	return Qs;

}

int RandomNumber(int From, int To)
{

	return rand() % (To - From + 1) + From;

}


void GetNumbersAccordingToLevel(stQuestionInfo& Question)
{

	if (Question.Level == enQsLevel::MixL)
	{

		Question.Level = (enQsLevel)RandomNumber(1, 3);

	}

	switch (Question.Level)
	{
	case enQsLevel::Easy:

		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;

	case enQsLevel::Med:

		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;


	case enQsLevel::Hard:

		Question.Number1 = RandomNumber(100, 1000);
		Question.Number2 = RandomNumber(100, 1000);
		break;

	default:

		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;


	}


}


int GetOperationResult(stQuestionInfo QInfo)
{


	switch (QInfo.OpChar)
	{
	case '+':
		return QInfo.Number1 + QInfo.Number2;
		break;

	case '-':
		return QInfo.Number1 - QInfo.Number2;
		break;

	case '*':
		return QInfo.Number1 * QInfo.Number2;
		break;

	case '/':
		return QInfo.Number1 / QInfo.Number2;
		break;

	default:
		QInfo.Number1 + QInfo.Number2;
		break;


	}

}


char GetOpChar(enOpType OpType)
{
	if (OpType == enOpType::MixOp)
	{
		OpType = (enOpType)RandomNumber(1, 4);

	}

	switch (OpType)
	{
	case enOpType::Add:
		return '+';

	case enOpType::Sub:
		return '-';

	case enOpType::Mul:
		return '*';

	case enOpType::Div:
		return '/';

	default:
		return '+';


	}




}

int UserAnswer()
{
	int Number;
	cin >> Number;
	return Number;


}


void ShowQuestion(stQuestionInfo QInfo)
{
	cout << QInfo.Number1 << endl;
	cout << QInfo.Number2 << " " << QInfo.OpChar;
	cout << "\n-----------------\n";


}



void SetScreenColor(bool isPass)
{
	if (isPass)
	{
		system("color 2F");

	}

	else
	{
		cout << "\a";
		system("color 4F");

	}


}


bool isPass(short NumberOfRightAnswers, short NumberOfWrongAnswer)
{
	if (NumberOfRightAnswers >= NumberOfWrongAnswer)
		return true;
	else
		return false;


}


string GetPassOrFailText(bool isPass)
{
	if (isPass)
		return "PASS";
	else
		return "Fail";


}

string GetLevelText(enQsLevel Level)
{
	string arrLevel[4] = { "Easy" , "Mid" ,"Hard","Mix" };

	return arrLevel[Level - 1];


}

string GetOpTypeText(enOpType OpType)
{
	string arrOpType[5] = { "Add","Sub","Mul","Div","Mix" };
	return arrOpType[OpType - 1];

}


void ShowPassOrFailHeader(bool isPass)
{
	cout << "\n------------------------------------\n\n";
	cout << "\tFinal Result is " << GetPassOrFailText(isPass);
	cout << "\n\n------------------------------------\n\n";


}


void ShowFinalResult(stQuizzInfo QuizzInfo)
{
	QuizzInfo.isPass = isPass(QuizzInfo.NumberOfRightAnswers, QuizzInfo.NumberOfWrongAnswers);

	ShowPassOrFailHeader(QuizzInfo.isPass);

	cout << "Number Of Questions    : " << QuizzInfo.HowManyQuestions << endl;
	cout << "Questions Level        : " << GetLevelText(QuizzInfo.QuestionsLevel) << endl;
	cout << "Operation Type         : " << GetOpTypeText(QuizzInfo.OpType) << endl;
	cout << "Number Of Right Answers: " << QuizzInfo.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers: " << QuizzInfo.NumberOfWrongAnswers << endl;
	cout << "\n------------------------------------\n\n";

}



void StartQuizz(stQuizzInfo& QuizzInfo)
{

	short NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;

	for (int i = 0; i < QuizzInfo.HowManyQuestions; i++)
	{
		cout << "\nQeustion [" << i + 1 << "/" << QuizzInfo.HowManyQuestions << "]\n\n";

		QuizzInfo.arrQuestions[i].Level = QuizzInfo.QuestionsLevel;
		QuizzInfo.arrQuestions[i].QOpType = QuizzInfo.OpType;
		QuizzInfo.arrQuestions[i].OpChar = GetOpChar(QuizzInfo.arrQuestions[i].QOpType);
		GetNumbersAccordingToLevel(QuizzInfo.arrQuestions[i]);
		ShowQuestion(QuizzInfo.arrQuestions[i]);
		QuizzInfo.arrQuestions[i].UserAnswer = UserAnswer();
		QuizzInfo.arrQuestions[i].RightAnswer = GetOperationResult(QuizzInfo.arrQuestions[i]);


		if (QuizzInfo.arrQuestions[i].UserAnswer == QuizzInfo.arrQuestions[i].RightAnswer)
		{

			cout << "Right Answer :-)\n\n";
			system("color 2F");
			NumberOfRightAnswers++;
		}

		else
		{
			cout << "Wrong Answer :-(\n";
			cout << "The Right Answer is : " << QuizzInfo.arrQuestions[i].RightAnswer << endl;;
			cout << "\a";
			system("color 4F");
			NumberOfWrongAnswers++;

		}



	}

	QuizzInfo.NumberOfRightAnswers = NumberOfRightAnswers;
	QuizzInfo.NumberOfWrongAnswers = NumberOfWrongAnswers;



}


void RestScreen()
{
	system("cls");

	system("color 0F");

}



void StartMathGame()
{
	char PlayAgain = 'y';

	do
	{
		RestScreen();

		stQuizzInfo QuizzInfo;

		QuizzInfo.HowManyQuestions = ReadNumberOfQs();
		QuizzInfo.QuestionsLevel = ReadQuestonsLevel();
		QuizzInfo.OpType = ReadOpType();

		StartQuizz(QuizzInfo);
		ShowFinalResult(QuizzInfo);

		cout << "Do you want to play again? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');


}



int main()
{
	srand((unsigned)time(NULL));

	StartMathGame();

	return 0;
}