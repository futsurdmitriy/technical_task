// AI_Maze_Runner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

int mazeHight, mazeWidth, 
startPosX, startPosY,
EndPosX, EndPosY, 
iterations;

string Maze = "Maze: ";
const char Wall ='#';
const char Free =' ';
const char AI = '*';

bool AIMovement(int, int, char **);
void readFrom(string, const char *);
void printMaze(char **);


 class COORD
{
public:
	int X, Y;
	COORD(int x = 0, int y = 0) {
		X = x; Y = y;
	}
	COORD(const COORD &coord) {
		X = coord.X; Y = coord.Y;
	}
	
};

void readFrom(string Maze,const char * MazeSize) {

	fstream MazeFile(Maze);
	FILE * mazeSize = fopen(MazeSize, "rt");
	
	
	if (MazeFile.is_open() && fopen(MazeSize,"rt") )
	{
		fscanf(mazeSize, "%d %d %d %d %d %d", &mazeHight, &mazeWidth, &startPosX, &startPosY, &EndPosX, &EndPosY);
		
		char **mazeArray = new char*[mazeWidth];
		for (int i = 0; i < mazeHight; i++)
		{
			mazeArray[i] = new char[mazeWidth];
		}

		for (int i = 0; i < mazeHight; i++)
		{
			for (int j = 0; j < mazeWidth; j++)
			{
				MazeFile.get(mazeArray[i][j]);
			}
		}
		MazeFile.close();
		fclose(mazeSize);

		COORD StartingPoint(startPosX, startPosY);

		if (AIMovement(StartingPoint.X, StartingPoint.Y, mazeArray)) {
			
		}
		else {
			printf("Something went wrong :( \n");
			_getch();
		}

	}
	else cout << "Unable to open file";
	
	
}

void printMaze(char **mazeArray) {
	cout << endl;
	for (int i = 0; i<mazeHight; i++)
	{
		for (int j = 0; j<mazeWidth; j++)
		{			
			cout << mazeArray[i][j];
		}
	}
	cout << endl;
}

bool AIMovement(int X,int Y, char **mazeArray) {
	
	COORD EndingPoint(EndPosX, EndPosY);
	
	mazeArray[Y][X] = AI;	
	printMaze(mazeArray);
	//If you want to see step by step solution 
	//please uncomment that.
    //cout << "To see next step press any key..." << endl;	
	//_getch();

	iterations++;

	if (X == EndingPoint.X && Y == EndingPoint.Y)	{
		cout << endl;
		cout << "***************Congrats!!!*****************" << endl;
		cout << "AI done " << iterations << " steps." << endl;
		iterations = 0;
		Maze = "Maze: ";

		return true;
	}

	if (X > 0 && mazeArray[Y][X - 1] == Free && AIMovement(X - 1, Y,mazeArray))	{
		return true;
	}

	if (X < mazeWidth && mazeArray[Y][X + 1] == Free && AIMovement(X + 1, Y, mazeArray)) {
		return true;
	}

	if (Y > 0 && mazeArray[Y - 1][X] == Free && AIMovement(X, Y - 1, mazeArray)) {
		return true;
	}

	if (Y < mazeHight && mazeArray[Y + 1][X] == Free && AIMovement(X, Y + 1, mazeArray)) {
		return true;
	}

	mazeArray[Y][X] = Free;
	
	//If you want to see step by step solution 
	//please uncomment that.	
	//printMaze(mazeArray);
	//_getch();
	
	return false;
}

int main()	{
	
	char choseMaze;
	
	cout << "This is demonstration of simple AI Maze Runner  " << endl << "Info:" << endl << "Wall = "<< Wall << endl
		 <<"AI = "<< AI << endl << "Choose one of the suggested mazes: " << endl << "1) Maze #1 = 1;" << endl 
		 <<"2) Maze #2 = 2;" << endl << "3) Maze #3 = 3;" << endl << "4) Exit = e." << endl;	

	do {
		cout << Maze;
		cin >> choseMaze;

		switch (choseMaze)
		{
		case '1':
			readFrom("maze1.txt", "maze1size.txt");
			break;
		case '2':
			readFrom("maze2.txt", "maze2size.txt");
			break;
		case '3':
			readFrom("maze3.txt", "maze3size.txt");
			break;
		case 'e':
			return 0;
			break;
		default:
			Maze = "Please re-enter your choose: ";
			//cout << Maze << endl;
			break;
		}

	} 
	while ((choseMaze != '1' || choseMaze != '2' || choseMaze != '3' ) || isdigit(choseMaze));
	_getch();
	return 0;
}

