#include <iostream>
#include "gotoxy.h"
#include "windows.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void clearScreen(void)
{
  system("cls");
}

struct gSymbol
{
    char pac = '@';
    int x = 1;
    int y = 1;
};


bool chEck(int x, int y, vector<string>& gamemap)
{
    bool tf = true;
    string line = gamemap[y];
    if(line[x] == '#')
    {
        tf = false;
    }

    return (tf);
}


int main()
{

    vector<string>gamemap;
    gSymbol pacman;
    vector<gSymbol>snake;
    int x=1;
    int y=1;
    bool game_running = true;

    ifstream mapFile;
    string filename, out;

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

    clearScreen();

    for(int i = 0; i < 3; i++)
    {
        snake.push_back(pacman);
    }

    do{
        gotoxy(0,0);
        int i = 0;


            cout << gamemap[i] << endl;

        cout << "Press esc to end game";

        system("pause>nul");

        for(int i =0; i < snake.size(); i++)
        {
        if(GetAsyncKeyState(VK_DOWN) && chEck(snake[i].x, (snake[i].y + 1), gamemap) ){
        gamemap[snake[i].y][snake[i].x] = ' ';
        snake[i].y += 1;
        gamemap[snake[i].y][snake[i].x]= snake[i].pac;
        }

        if(GetAsyncKeyState(VK_UP) &&  chEck(snake[i].x, (snake[i].y - 1), gamemap)){
        gamemap[snake[i].y][snake[i].x] = ' ';
        snake[i].y -= 1;
        gamemap[snake[i].y][snake[i].x]= snake[i].pac;
        }

        if(GetAsyncKeyState(VK_RIGHT) && chEck((snake[i].x + 1), snake[i].y, gamemap)){
        gamemap[snake[i].y][snake[i].x] = ' ';
        snake[i].x += 1;
        gamemap[snake[i].y][snake[i].x]= snake[i].pac;
        }

        if(GetAsyncKeyState(VK_LEFT) &&  chEck((snake[i].x - 1), snake[i].y, gamemap)){
        gamemap[snake[i].y][snake[i].x] = ' ';
        snake[i].x -= 1;
        gamemap[snake[i].y][snake[i].x]= snake[i].pac;
        }

        if(GetAsyncKeyState(VK_ESCAPE)){
            game_running = false;
        }
        }
    }while(game_running == true);

    system("cls");
    cout << "GAME OVER";

    return 0;
}
