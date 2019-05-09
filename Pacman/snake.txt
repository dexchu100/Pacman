/*
Problem: Pacman Assignment
Description: This is the program that will let you play a game called snake.
Name: Eric Chu, Alex Bakos, James Haberman
ID:
Class:COMSCI 110
Date: 8/29/14
*/

#include <iostream>
#include "gotoxy.h"
#include "windows.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct pSymbol
{
int x = 1;
int y = 1;
};

void printSnake(int x, int y, vector<string>& gamemap, vector<pSymbol>& snake)
{
    if (snake.size() > 1)
    {
        for (int i = snake.size()-1; i > 0; i--)
        {
            snake[i].y = snake[i - 1].y;
            snake[i].x = snake[i - 1].x;
        }
    }

    snake[0].y = y;
    snake[0].x = x;

    for (int i = 0; i < snake.size(); i++)
    {
        gamemap[snake[i].y][snake[i].x] = '@';
    }
}

bool cHeck(int x, int y, vector<string>& gamemap, int& food, vector<pSymbol>& snake, bool& gameend)
{
    pSymbol pacman;
    bool result = true;
    if (snake.size() > 1 && x == snake[1].x && y == snake[1].y) //This is so that the snake head cannot move backwords
    {
        result = false;
    }

    else if (gamemap[y][x] == '@' || gamemap[y][x] == '#')
    {
        gameend = false;
    }

    else
    {
        if (gamemap[y][x] == 'x')
        {
            food++;
            snake.push_back(pacman);
        }
        else
        {
            gamemap[snake[food].y][snake[food].x] = ' ';
        }
    }

return result;
}

int main()
{
    ifstream mapFile;
    string filename, out;
    vector <string> gamemap;
    vector <pSymbol> snake;
    pSymbol pacman;
    int food = 0;
    bool game_running = true;

    snake.push_back(pacman);
    cout << "Welcome to the Snake Game!\n" << endl;
    cout << "The Game will end if snake touches itself or hits the walls of the map.\n\n";

    cout << "Enter the map file you want to use: ";
    getline(cin, filename);
    mapFile.open(filename);
        if(mapFile)
        {
            while(getline(mapFile,out))
            {
                gamemap.push_back(out);
            }
        }
        else
        {
            cout << "error";
        }

system("cls");

do{
    gotoxy(0,0);

    for(int i = 0;i<gamemap.size();i++)
    {
        cout << gamemap[i] << endl;
    }

    cout <<"Score: "<< food <<endl;
    cout << "If you want to end the game press esc";

    system("pause>nul");

    if(GetAsyncKeyState(VK_DOWN) && cHeck(snake[0].x, snake[0].y+1, gamemap, food, snake, game_running))
        {
            printSnake(snake[0].x, snake[0].y+1, gamemap, snake);
        }
    else if(GetAsyncKeyState(VK_UP) && cHeck(snake[0].x, snake[0].y-1, gamemap, food, snake, game_running))
        {
            printSnake(snake[0].x, snake[0].y-1, gamemap, snake);
        }
    else if(GetAsyncKeyState(VK_RIGHT) && cHeck(snake[0].x+1, snake[0].y, gamemap, food, snake, game_running))
        {
            printSnake(snake[0].x+1, snake[0].y, gamemap, snake);
        }
    else if(GetAsyncKeyState(VK_LEFT) && cHeck(snake[0].x-1, snake[0].y, gamemap, food, snake, game_running))
        {
            printSnake(snake[0].x-1, snake[0].y, gamemap, snake);
        }
    else if(GetAsyncKeyState(VK_ESCAPE))
        {
            game_running = false;
        }
} while(game_running == true);

system("cls");

cout<< "GAME OVER" <<endl;
cout << "Score: " << food <<endl;

return 0;
}
