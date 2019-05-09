#include <iostream>
#include "gotoxy.h"
#include "windows.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct pSymbol
{
int x;
int y;
};

bool MoveTo(int x2, int y2, vector<string>& gamemap, int& food, vector<pSymbol>& snake, bool& gamerun){
bool result = true;
pSymbol pacmen;
if (gamemap[y2][x2] == '#' ||(snake.size() > 1 && x2 == snake[1].x && y2 == snake[1].y))
result = false; //Prevents user from moving directly backwards.
else if (gamemap[y2][x2] == '@')
gamerun = false; //Ends game if hits self.
else{
if (gamemap[y2][x2] == 'X' || gamemap[y2][x2] == 'x'){
food++;
snake.push_back(pacmen);
} else gamemap[snake.back().y][snake.back().x] = ' ';

if (snake.size() > 1){
for (int i = snake.size()-1; i > 0; i--){
snake[i].y = snake[i-1].y;
snake[i].x = snake[i-1].x;
}
}
snake[0].y = y2;
snake[0].x = x2;
for (int i = 0; i < snake.size(); i++){
gamemap[snake[i].y][snake[i].x] = '@';
}
result = true;
}
return result;
}

int main()
{
ifstream mapFile;
string filename, out;
int food = 0;
vector <string> gamemap;
bool game_running = true;
vector <pSymbol> snake;
pSymbol pacmen;
pacmen.x = 1;
pacmen.y = 1;

snake.push_back(pacmen);

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
//file stuff

system("cls");

do{
gotoxy(0,0);

for(int i = 0;i<gamemap.size();i++)
cout << gamemap[i] << endl;
cout<< "Score: " << food << endl;

system("pause>nul"); //waits for key to be touched

//should these be ifs? or else ifs? I think Amr said that they should be else ifs.
if(GetAsyncKeyState(VK_DOWN) && MoveTo(snake[0].x, snake[0].y+1, gamemap, food, snake, game_running)){

}
else if(GetAsyncKeyState(VK_UP) && MoveTo(snake[0].x, snake[0].y-1, gamemap, food, snake, game_running)){

}
else if(GetAsyncKeyState(VK_RIGHT) && MoveTo(snake[0].x+1, snake[0].y, gamemap, food, snake, game_running)){

}
else if(GetAsyncKeyState(VK_LEFT) && MoveTo(snake[0].x-1, snake[0].y, gamemap, food, snake, game_running)){
}
else if(GetAsyncKeyState(VK_ESCAPE)){
game_running = false;
}
} while(game_running == true);

system("cls");
cout<< " GAME OVER" <<endl
<< "\nFinal Score: "<< food <<endl;
return 0;
}
