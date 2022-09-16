#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// map
const int width = 20;
const int height = 20;
int x, y;
int mapToDraw[height][width] = { 0 };
int xGoal, yGoal;
// move
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
bool movement = false;
// Logic Map
// 9 - mina
// 0-8 - count around
int mapLogic[height][width] = { 0 };
// Game over
int gameOver;



// Map
void Setup() 
{
	//srand(time(0));	// каждый раз разные значения
	gameOver = false;
	dir = STOP;
	x = 0;  
	y = 0;
	xGoal = rand() % 20;
	yGoal = rand() % 20;
	mapToDraw[xGoal][yGoal] = 100;
}
void Draw() 
{
	system("cls");
	for (int i = 0; i < width + 2; ++i)
		cout << "-";
	cout << endl;

	for (int i = 0; i < height; ++i)	// высота
	{
		cout << "|";
		for (int j = 0; j < width; ++j) // ширина
		{
			if (y == i && x == j)
				cout << "@";
			else if (mapToDraw[i][j] == 100)
				cout << '!';
			else if (mapToDraw[i][j] == -1)
				cout << '.';
			else if (mapToDraw[i][j] == 0)
				cout << '*';
			else if (mapToDraw[i][j] > 0 && mapToDraw[i][j] < 9)
				cout << mapToDraw[i][j];
			else if (mapToDraw[i][j] == 9)
				cout << 'X';
		}
		cout << "|";
		cout << endl;
	}

	for (int i = 0; i < width + 2; ++i)
		cout << "-";
	cout << endl;
}
void SetMinas()
{
	mapLogic[xGoal][yGoal] = 100;	// установили, чтобы мина не попала на это место
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (rand() % 5 == 0 && i != xGoal && j != yGoal)
				mapLogic[i][j] = 9;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (i != xGoal && j != yGoal)
				mapLogic[i][j] = 0;
		}
	}
}
void SetNumbers()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (mapLogic[i][j] == 9)
				continue;
			int countMinas = 0;
			//up
			if (i - 1 >= 0)
				if (mapLogic[i - 1][j] == 9) { ++countMinas; }
			if (i - 1 >= 0 && j + 1 < width)
				if (mapLogic[i - 1][j + 1] == 9) { ++countMinas; }
			if (i - 1 >= 0 && j - 1 >= 0)
				if (mapLogic[i - 1][j - 1] == 9) { ++countMinas; }
			//sides
			if (j + 1 < width)
				if (mapLogic[i][j + 1] == 9) { ++countMinas; }
			if (j - 1 >= 0)
				if (mapLogic[i][j - 1] == 9) { ++countMinas; }
			//down
			if (i + 1 < height)
				if (mapLogic[i + 1][j] == 9) { ++countMinas; }
			if (i + 1 < height && j + 1 < width)
				if (mapLogic[i + 1][j + 1] == 9) { ++countMinas; }
			if (i + 1 < height && j - 1 >= 0)
				if (mapLogic[i + 1][j - 1] == 9) { ++countMinas; }

			mapLogic[i][j] = countMinas;
		}
	}
	mapLogic[xGoal][yGoal] = 100; //сохранить место
}
// Move
int Input() 
{
	if (_kbhit()) //keyboard hit
	{
		switch (_getch()) 	// get askii char
		{
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		default:
			return 0;
			break;
		}
		return 1;
	}
	return 0;
}
void Logic() 
{
	switch (dir)
	{
	case STOP:
		break;
	case LEFT:
		if(x > 0)
			--x;
		movement = true;
		break;
	case RIGHT:
		if (x < width - 1)
			++x;
		movement = true;
		break;
	case UP:
		if(y > 0)
			--y;
		movement = true;
		break;
	case DOWN:
		if (y < height - 1)
			++y;
		movement = true;
		break;
	default:
		break;
	}
	dir = STOP;
	if (mapLogic[y][x] > 0 && mapLogic[y][x] < 9)
		mapToDraw[y][x] = mapLogic[y][x];
	else if (mapLogic[y][x] == 0)
		mapToDraw[y][x] = -1;
	else if (mapLogic[y][x] == 9) 
	{
		mapToDraw[y][x] = 9;
		gameOver = 1;
	}
	else if (mapLogic[y][x] == 100) 
	{
		gameOver = 2;
	}
}
// Logic
void DrawLogic()
{
	for (int i = 0; i < height; ++i) 
	{
		for (int j = 0; j < width; ++j) 
		{
			cout << mapLogic[i][j];
		}
		cout << endl;
	}
}

//Game
int	GameOver() 
{
	if(gameOver == 1)
		cout << "You lose\n";
	else
		cout << "You won\n";
	cout << "quit? - esc\n";
	char a = _getch();
	while (a != 27)
		a = _getch();
	return (a);
}
void Start() 
{
	system("cls");
	cout << "\nStart?\n";
	while (!_kbhit());
	Setup();
	SetMinas();
	SetNumbers();
}
void Game() 
{
	Start();
	Draw();
	while (!gameOver)
	{
		if (movement)
		{
			Draw();
			movement = false;
		}
		Input();
		Logic();
		if (gameOver == 2) 
		{
			Draw();
			return;
		}
	}
	Draw();
	while (!Input());
	Logic();
	Draw();
}

int main()
{
	int resume = 13;
	while (resume == 13) 
	{
		Game();
		resume = GameOver();	// Пока нельзя продолжить
	}
}

/*
	Доработать:
	!! Иногда без махинаций ввод не работает !!
	1. Взрывать/Обезвредить мины? Чтобы пройти через них 
	2. У игрока есть три минёра, которые будут сменять друг друга
	!! Счётчик времени !!
	4. Все время новая карта не нужна
	- Взрыв когда сходишь с мины
*/