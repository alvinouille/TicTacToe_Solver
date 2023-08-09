#include "Board.hpp"

Board::Board() 
{
    for (int i = 0 ; i < 9 ; i++)
        this->_tab[i] = '.';
}

Board::~Board() {}

void Board::display()const
{
    int j = 0;
    std::cout << std::endl;
    for (j = 0 ; j < 3 ; j++)
    {
        for (int i = 0 ; i < 3 ; i++)
            std::cout << this->_tab[(j * 3) + i] << " ";
        std::cout << std::endl;
    }
}

bool Board::isFull()const
{
    for (int i = 0 ; i < 9 ; i++)
    {
        if (this->_tab[i] == '.')
            return (false);
    }
    return (true);
}

bool Board::checkLine(char p)const
{
    for (int i = 0; i < 7 ; i += 3)
    {
        if (_tab[i + 0] == p && _tab[i + 1] == p && _tab[i + 2] == p)
            return (true);
    }
    return (false);
}

bool Board::checkCol(char p)const
{
    for (int i = 0; i < 3 ; i++)
    {
        if (_tab[i + 0] == p && _tab[i + 3] == p && _tab[i + 6] == p)
            return (true);
    }
    return (false);
}

bool Board::checkDiag(char p)const
{
    if (_tab[0] == p && _tab[4] == p && _tab[8] == p)
        return (true);
    if (_tab[2] == p && _tab[4] == p && _tab[6] == p)
        return (true);
    return (false);
}

bool Board::checkWin(char p)const
{
    if (checkLine(p))
        return (true);
    else if (checkCol(p))
        return (true);
    else if (checkDiag(p))
        return (true);
    else
        return (false);
}

bool Board::isWon(char p1, char p2)const
{
    if (checkWin(p1) || checkWin(p2))
        return (true);
    return (false);
}

void Board::setCell(int pos, char symbol)
{
    this->_tab[pos] = symbol;
}

char Board::getCell(int pos)const
{
    return (this->_tab[pos]);
}

void Board::setState(char player)
{
    if (player == HUMAN)
        this->_state = DESAVANTAGE;
    else
        this->_state = AVANTAGE;
}

int Board::getState()
{
    return (this->_state);
}

int Board::getFinalScore(int depth)
{
    if (isWon(HUMAN, AI))
    {
        if (checkWin(AI))
            return (10 - depth);
        return (-10 + depth);
    }
    return (0);
}

