
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

enum enChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber;
    enChoice PlayerChoice;
    enChoice ComputerChoice;
    enWinner RoundWinner;
    string WinnerName;
};

struct stGameResult
{
    short GameRounds = 0;
    short PlayerWinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner Winner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    int RandNum;
    RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

enChoice ReadPlayerChoice()
{
    short PlayerChoice;
    do {
        cout << "Your Choice: [1]: Stone, [2]: Paper, [3]: Scissors? ";
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice > 3);
    return (enChoice)PlayerChoice;
}

enChoice GetComputerChoice()
{
    short ComputerChoice;
    ComputerChoice = RandomNumber(1, 3);
    return (enChoice)ComputerChoice;
}

string ChoiceName(enChoice Choice)
{
    string Choices[3] = { "Stone", "Paper", "Scissors" };
    return Choices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string Names[3] = { "Player1", "Computer", "Draw" };
    return Names[Winner - 1];
}

enWinner RoundWinner(stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.PlayerChoice)
    {
    case enChoice::Stone:
        return (RoundInfo.ComputerChoice == enChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enChoice::Paper:
        return (RoundInfo.ComputerChoice == enChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enChoice::Scissors:
        return (RoundInfo.ComputerChoice == enChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }
}

enWinner GameWinner(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
        return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i <= NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case Player1:
        system("color 2F");
        break;
    case Computer:
        system("color 4F");
        cout << "\a";
        break;
    case Draw:
        system("color 6F");
        break;
    }
}

void PrintRoundResult(stRoundInfo RoundInfo)
{
    cout << "\n__________Round [" << RoundInfo.RoundNumber << "]__________\n\n";
    cout << "Player1 Choice  : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner    : [" << RoundInfo.WinnerName << "]" << endl;
}

stGameResult FillGameResult(short GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
    stGameResult GameResult;

    GameResult.GameRounds = GameRounds;
    GameResult.PlayerWinTimes = Player1WinTimes;
    GameResult.ComputerWinTimes = ComputerWinTimes;
    GameResult.DrawTimes = DrawTimes;
    GameResult.Winner = GameWinner(Player1WinTimes, ComputerWinTimes);
    GameResult.WinnerName = WinnerName(GameResult.Winner);

    return GameResult;
}

stGameResult PlayGame(short RoundsNumber)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
    for (short i = 1; i <= RoundsNumber; i++)
    {
        cout << "\n\nRound [" << i << "] Begins: \n";
        RoundInfo.RoundNumber = i;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = RoundWinner(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

        if (RoundInfo.RoundWinner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.RoundWinner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;
        SetWinnerScreenColor(RoundInfo.RoundWinner);
        PrintRoundResult(RoundInfo);
    }
    return FillGameResult(RoundsNumber, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

void PrintGameOver()
{
    cout << endl << Tabs(2) << "===================================\n\n";
    cout << Tabs(2) << "           ++GAME OVER++             \n\n";
    cout << Tabs(2) << "=====================================\n";
}

short ReadHowManyRounds()
{
    short RoundsNumber;
    do {
        cout << "How many rounds do you want to play? ";
        cin >> RoundsNumber;
    } while (RoundsNumber > 10 || RoundsNumber < 1);
    return RoundsNumber;
}


void ShowFinalGameResults(stGameResult GameResult)
{
    cout << Tabs(2) << "_____________[Game Results]_____________\n";
    cout << Tabs(2) << "Game Rounds       : " << GameResult.GameRounds << endl;
    cout << Tabs(2) << "Player 1 Won Times: " << GameResult.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer Won Times: " << GameResult.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw Times        : " << GameResult.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner      : " << GameResult.WinnerName << endl;
    cout << Tabs(2) << "________________________________________\n";

    SetWinnerScreenColor(GameResult.Winner);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        stGameResult GameResult = PlayGame(ReadHowManyRounds());
        PrintGameOver();
        ShowFinalGameResults(GameResult);

        cout << endl << Tabs(2) << "Do you want to play again ? Y/N ? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}


