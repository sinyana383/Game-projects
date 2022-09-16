#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;

// player
int x, y;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
bool movement = false;

class Map
{
public:
	const static int width = 20;  
	const static int height = 20;
 
	Map() 
	{
		srand(time(0));
		mapToDraw = new int*[height];
		for (int i = 0; i < height; ++i)
			mapToDraw[i] = new int[width];

		mapLogic = new int* [height];
		for (int i = 0; i < height; ++i)
			mapLogic[i] = new int[width];

		SetNulls(mapToDraw);
		SetNulls(mapLogic);

		xGoal = rand() % width;
		yGoal = rand() % height;
	};
	~Map() 
	{
		
		for (int i = 0; i < height; ++i)
			delete [] mapToDraw[i];
		delete [] mapToDraw;

		for (int i = 0; i < height; ++i)
			delete[] mapLogic[i];
		delete[] mapLogic;
	};

	int GetElementFromMapLogic(int x, int y) { return mapLogic[x][y]; }
	int GetElementFromMapToDraw(int x, int y) { return mapToDraw[x][y]; }
	int GetXGoal() { return xGoal; }
	int GetYGoal() { return yGoal; }

	void SetElementToMapToDraw(int x, int y, int element) { mapToDraw[x][y] = element; }
	void SetElementToMapLogic(int x, int y, int element) { mapLogic[x][y] = element; }

	void DrawLogicMap();
	void DrawMap();
	void SetMines();
	void SetNumbers();
	void SetNulls(int **map) 
	{
		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				map[i][j] = 0;
	}

private:
	int **mapToDraw;
	int **mapLogic;
	int xGoal, yGoal;
};

 void Map::DrawMap()
{
	system("cls");
	for (int i = 0; i < Map::width + 2; ++i)
		cout << "-";
	cout << endl;

	for (int i = 0; i < Map::height; ++i)	// высота
	{
		cout << "|";
		for (int j = 0; j < Map::width; ++j) // ширина
		{
			if (y == i && x == j)
				cout << "@";
			else if (GetElementFromMapToDraw(i, j) == 100)
				cout << '!';
			else if (GetElementFromMapToDraw(i, j) == -1)
				cout << '.';
			else if (GetElementFromMapToDraw(i, j) == 0)
				cout << '*';
			else if (GetElementFromMapToDraw(i, j) > 0 && GetElementFromMapToDraw(i, j) < 9)
				cout << GetElementFromMapToDraw(i, j);
			else if (GetElementFromMapToDraw(i, j) == 9)
				cout << 'X';
		}
		cout << "|";
		cout << endl;
	}

	for (int i = 0; i < Map::width + 2; ++i)
		cout << "-";
	cout << endl;
}
 void Map::SetMines()
{
	SetElementToMapLogic(xGoal, yGoal, 100); // установили, чтобы мина не попала на это место
	for (int i = 0; i < Map::height; ++i)
	{
		for (int j = 0; j < Map::width; ++j)
		{
			if (rand() % 5 == 0 && i != xGoal && j != yGoal)
				SetElementToMapLogic(i, j, 9);
		}
	}

	for (int i = 0; i < 2; ++i) 
	{
		for (int j = 0; j < 2; ++j)
		{
			if (i != xGoal && j != yGoal)
				SetElementToMapLogic(i, j, 0);
		}
	}
}
 void Map::SetNumbers()
{
	for (int i = 0; i < Map::height; ++i)
	{
		for (int j = 0; j < Map::width; ++j)
		{
			if (GetElementFromMapLogic(i, j) == 9)
				continue;
			int countMinas = 0;
			//up
			if (i - 1 >= 0)
				if (GetElementFromMapLogic(i - 1, j) == 9) { ++countMinas; }
			if (i - 1 >= 0 && j + 1 < Map::width)
				if (GetElementFromMapLogic(i - 1, j + 1) == 9) { ++countMinas; }
			if (i - 1 >= 0 && j - 1 >= 0)
				if (GetElementFromMapLogic(i - 1, j - 1) == 9) { ++countMinas; }
			//sides
			if (j + 1 < Map::width)
				if (GetElementFromMapLogic(i, j + 1) == 9) { ++countMinas; }
			if (j - 1 >= 0)
				if (GetElementFromMapLogic(i, j - 1) == 9) { ++countMinas; }
			//down
			if (i + 1 < Map::height)
				if (GetElementFromMapLogic(i + 1, j) == 9) { ++countMinas; }
			if (i + 1 < Map::height && j + 1 < Map::width)
				if (GetElementFromMapLogic(i + 1, j + 1) == 9) { ++countMinas; }
			if (i + 1 < Map::height && j - 1 >= 0)
				if (GetElementFromMapLogic(i + 1, j - 1) == 9) { ++countMinas; }

			SetElementToMapLogic(i, j, countMinas);
		}
	}
	SetElementToMapLogic(xGoal, yGoal, 100);
}
 void Map::DrawLogicMap()
{
	for (int i = 0; i < Map::height; ++i)
	{
		for (int j = 0; j < Map::width; ++j)
		{
			cout << GetElementFromMapLogic(i, j);
		}
		cout << endl;
	}
}

//class Player
//{
//public:
//	Player();
//	~Player();
//  int Input();
//  void Logic();
//
//private:
//	int x, y;
//	eDirection dir;
//	bool movement = false;
//  static int gameOver;
//}

int gameOver;



// Map
void SetUpPlayerAndMapCharacteristics(Map *map) 
{
	srand(time(0));	// каждый раз разные значения
	gameOver = false;

	// ForPlayer
	dir = STOP;
	x = 0;
	y = 0;

	// ForMap
	(*map).SetElementToMapToDraw((*map).GetXGoal(), (*map).GetYGoal(), 100);
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
void Logic(Map* map)
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
		if (x < Map::width - 1)
			++x;
		movement = true;
		break;
	case UP:
		if(y > 0)
			--y;
		movement = true;
		break;
	case DOWN:
		if (y < Map::height - 1)
			++y;
		movement = true;
		break;
	default:
		break;
	}
	dir = STOP;
	if ((*map).GetElementFromMapLogic(y, x) > 0 && (*map).GetElementFromMapLogic(y, x) < 9)
		(*map).SetElementToMapToDraw(y, x, (*map).GetElementFromMapLogic(y, x));
	else if ((*map).GetElementFromMapLogic(y, x) == 0)
		(*map).SetElementToMapToDraw(y, x, -1);
	else if ((*map).GetElementFromMapLogic(y, x) == 9)
	{
		(*map).SetElementToMapToDraw(y, x, 9);
		gameOver = 1;
	}
	else if ((*map).GetElementFromMapLogic(y, x) == 100)
	{
		gameOver = 2;
	}
}
// Logic

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
void Start(Map* map)
{
	system("cls");
	cout << "\nStart?\n";
	while (!_kbhit());

	SetUpPlayerAndMapCharacteristics(map);
	(*map).SetMines();
	(*map).SetNumbers();
}
void Game(Map* map)
{
	Start(map);
	(*map).DrawMap();
	while (!gameOver)
	{
		if (movement)
		{
			(*map).DrawMap();
			movement = false;
		}
		Input();
		Logic(map);
		if (gameOver == 2) 
		{
			(*map).DrawMap();
			return;
		}
	}
	(*map).DrawMap();
	while (!Input());
	Logic(map);
	(*map).DrawMap();
}

int main()
{
	int resume = 13;
	Map map;
	while (resume == 13) 
	{
		Game(&map);
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