#ifndef BOARD_H
# define BOARD_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

# define HUMAN 'X'
# define AI 'O'

# define AVANTAGE 0
# define DESAVANTAGE 1

# define WIN 1
# define TIE 0
# define LOSS -1

void makingCross(int pos, SDL_Renderer *ren);
void initDraw(SDL_Renderer *ren);
void makingCircle(int pos, SDL_Renderer *ren);
int whereClick(int posX, int posY);
void initGraphic(SDL_Window **win, SDL_Renderer **ren);
void destroyGraphic(SDL_Window *win, SDL_Renderer *ren);
void quitCheck(SDL_Event *event, SDL_Window *win, SDL_Renderer *ren);

class Board
{
    public:
        Board();
        ~Board();

        void display()const;
        bool isFull()const;
        bool isWon(char p1, char p2)const;
        bool checkLine(char p)const;
        bool checkCol(char p)const;
        bool checkDiag(char p)const;
        bool checkWin(char p)const;
        void setCell(int pos, char player);
        char getCell(int pos)const;
        void setState(char player);
        int getState();
        int getFinalScore(int depth);
    
    private:
        char _tab[9];
        int _state;
};

#endif