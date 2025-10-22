#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
// ===== Enums ===========================================
enum enOperationType { Add = 1, Sub, Multi, Divide, MixOp };
enum enQuestionLevel { Easy = 1, Mid, Hard, Mix };

// ===== Structs ==========================================
struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enQuestionLevel QuestionLevel;
	enOperationType OpType;
	short PlayerAnswer;
	short RightAnswer;
	bool IsAnswerResult = true;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	enQuestionLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfQuestions = 0;
	short RightAnswers = 0;
	short WrongAnswers = 0;
	bool IsPass = true;
};

// ===== Utilities =======================================
int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); // Green for correct answers.
	else
	{
		system("color 4F"); // Red for incorrect answers.
		cout << "\a"; // Plays an alert sound.
	}
}

void ResetScreen()
{
	system("cls");
	system("color 0f");
}

// ===== Input Functions =================================
short ReadHowManyQuestion()
{
	short Questions = 0;
	do
	{
		cout << "\nEnter How many qusetions you want to test [ 1 to 10 ] ? > ";
		cin >> Questions;
	} while (Questions <= 0 || Questions > 10);

	return Questions;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "\nEnter your Questions Level : [1] Easy, [2] Mid, [3] Hard , [4] Mix ? >  ";
		cin >> QuestionLevel;
	} while (QuestionLevel <= 0 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}
enOperationType ReadOpType()
{
	short OpType = 0;
	do
	{
		cout << "\nEnter Operation Type : [1] Add, [2] Sub, [3] Multi , [4] Divide , [5] Mix ? > ";
		cin >> OpType;
	} while (OpType <= 0 || OpType > 5);

	return (enOperationType)OpType;
}

// ===== Helper Conversion Functions =====================
string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Multi:
		return "x";
	case enOperationType::Divide:
		return "/";
	default:
		return "Mix";
	}
}

string GetResults(bool True)
{
	if (True)
		return "Pass :-)";
	else
		return "Fail :-( ";
}
string GetQuestionLevel(enQuestionLevel QuestinLevel)
{
	string Arr[4] = { "Easy","Mid","Hard","Mix" };
	return Arr[QuestinLevel - 1];
}
// ===== Project Logic ===================================

int SimpleCalculater(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Multi:
		return Number1 * Number2;
	case enOperationType::Divide:
		return Number1 / Number2;
	default:
		return  Number1 + Number2;
	}
}
stQuestion GenerateQuestion(enOperationType OperationType, enQuestionLevel QuestionLevel)
{
	stQuestion Question;
	if (OperationType == enOperationType::MixOp)
		OperationType = (enOperationType)RandomNumber(1, 4);

	if (QuestionLevel == enQuestionLevel::Mix)
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);

	Question.OpType = OperationType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.RightAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionLevel;

		return Question;

	case enQuestionLevel::Mid:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.RightAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionLevel;

		return Question;
	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.RightAnswer = SimpleCalculater(Question.Number1, Question.Number2, Question.OpType);
		Question.QuestionLevel = QuestionLevel;

		return Question;

	}
}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.OpType, Quizz.QuestionLevel);
	}
}


void PrintTheQuestions(stQuizz Quizz, short QuestionNumber)
{
	cout << "\nQuestion ["<< QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n \n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OpType);
	cout << "\n-------------" << endl;
}
int ReadPlayerAnswer()
{
	int Answer;
	cin >> Answer;

	return Answer;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].RightAnswer)
	{
		Quizz.QuestionList[QuestionNumber].IsAnswerResult = false;
		Quizz.WrongAnswers++;
		cout << "Wrong Answer :-( \n";
		cout << "The Right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].RightAnswer << endl;
		cout << "=================" << endl;
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].IsAnswerResult = true;
		Quizz.RightAnswers++;

		cout << "Right Answer :-)\n \n";
		cout << "=================" << endl;

	}

	SetScreenColor(Quizz.QuestionList[QuestionNumber].IsAnswerResult);
}


void AskAndCorrectQuestions(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestions(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}
	Quizz.IsPass = (Quizz.RightAnswers > Quizz.WrongAnswers);
}

void PrintQuizzResult(stQuizz& Quizz)
{
	cout << "\n______________________________\n" << endl;;
	cout << " Final Results is " << GetResults(Quizz.IsPass) << endl;
	cout << "\n______________________________\n";
	cout << endl;
	cout << "Number OF Questions    : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level         : " << GetQuestionLevel(Quizz.QuestionLevel) << endl;
	cout << "Operatin Type          : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answers: " << Quizz.RightAnswers << endl;
	cout << "Number Of Wrong Answers: " << Quizz.WrongAnswers;
	cout << "\n______________________________\n";
}

void playMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestion();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);

	AskAndCorrectQuestions(Quizz);

	PrintQuizzResult(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		playMathGame();
		cout << endl << "Wanna Play Again (Y/N)";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}