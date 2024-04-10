#include<iostream>
#include<conio.h>
#include<windows.h>
#include <vector>
using namespace std;

const int width = 80;
const int height = 25;

int snakeX, snakeY;
int fruitX, fruitY;

int playerScore;
int snakeTailX[100];
int snakeTailY[100];
int snakeLen;

enum snakeDirection{STOP = 0, LEFT, RIGHT, UP, DOWN};
snakeDirection sDir;

bool isGameOver;

// initialized the game
void gameInit(){
    isGameOver = false;
    snakeX = width / 2;
    snakeY = height / 2;
    sDir = STOP;
    fruitX = rand() % width;
    fruitY = rand() % height;
    playerScore = 0;
}

// render the game board for playing
void GameRender(string playerName) 
{ 
    system("cls"); 
  
    for (int i = 0; i < width + 2; i++) 
        cout << "-"; 
    cout << endl; 
  
    for (int i = 0; i < height; i++) { 
        for (int j = 0; j <= width; j++) { 
            if (j == 0 || j == width) 
                cout << "|"; 
            if (i == snakeY && j == snakeX) 
                cout << "O"; 
            else if (i == fruitY && j == fruitX) 
                cout << "#"; 
            else { 
                bool prTail = false; 
                for (int k = 0; k < snakeLen; k++) { 
                    if (snakeTailX[k] == j 
                        && snakeTailY[k] == i) { 
                        cout << "o"; 
                        prTail = true; 
                    } 
                } 
                if (!prTail) 
                    cout << " "; 
            } 
        } 
        cout << endl; 
    } 
  
    for (int i = 0; i < width + 2; i++) 
        cout << "-"; 
    cout << endl; 
  
    cout << playerName << "'s Score: " << playerScore 
         << endl; 
} 

void updateGame(){
    //save snake head next in prev and replace snake head next with head. 

    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = snakeX;
    snakeTailY[0] = snakeY;

        //Move snake ahead by one position

    for(int i = 0; i < snakeLen; i++){
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir)
    {
    case LEFT:
        snakeX--;
        break;
    
    case RIGHT:
        snakeX++;
        break;
    case UP:
        snakeY--;
        break;
    case DOWN:
        snakeY++;
        break;
    }

    if(snakeX >= width || snakeX < 0 || snakeY >= height || snakeY < 0){
        isGameOver = true;
    }

    for(int i = 0; i < snakeLen; i++){
        if(snakeX == snakeTailX[i] && snakeY == snakeTailY[i]){
            isGameOver = true;
        }
    }

    if(snakeX == fruitX && snakeY == fruitY){
        playerScore += 10;
        snakeLen++;
        fruitX = rand() % width;
        fruitY = rand() % height;
    }
}

void userInput(){
    if(_kbhit()){
        switch (_getch())
        {
        case 'w':
            sDir = UP;
            break;
        case 'a':
            sDir = LEFT;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'd':
            sDir = RIGHT;      
        default:
            break;
        }
    }
}

int main(){
    string name;
    cout << "Enter Player1 Name : ";
    cin >> name;

    gameInit();
    while(!isGameOver){
        GameRender(name);
        userInput();
        updateGame();
    }
    
    return 0;
}