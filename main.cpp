#include "Board.hpp"
#include <cmath>
#include <thread>

int minimax(Board &board, int depth, bool isMaximising)
{
    int score;
    int bestScore = INT8_MIN;
    int worstScore = INT8_MAX;

    if (board.isFull() || board.checkWin(AI) || board.checkWin(HUMAN))
        return (board.getFinalScore(depth));
    if (isMaximising)
    {
        for (int i = 0 ; i < 9 ; i++)
        {
            if (board.getCell(i) == '.')
            {
                board.setCell(i, AI);
                score = minimax(board, depth + 1, false);
                board.setCell(i, '.');
                bestScore = std::max(score, bestScore);
            }
        }
        return (bestScore);
    }
    else
    {
        for (int i = 0 ; i < 9 ; i++)
        {
            if (board.getCell(i) == '.')
            {
                board.setCell(i, HUMAN);
                score = minimax(board, depth + 1, true);
                board.setCell(i, '.');
                worstScore = std::min(score, worstScore);
            }
        }
        return (worstScore);
    }
}


int AIMove(Board &board)
{
    int score, bestPos;
    int bestScore = INT8_MIN;

    for (int i = 0 ; i < 9 ; i++)
    {
        if (board.getCell(i) == '.')
        {
            board.setCell(i, AI);
            score = minimax(board, 0, false);
            board.setCell(i, '.');
            if (score > bestScore)
            {
                bestScore = score;
                bestPos = i;
            }
        }
    }
    return (bestPos);
}

void game(char curr[1], Board &board, SDL_Renderer *ren, SDL_Event event)
{
    int pos = 0;

    if (*curr == HUMAN)
    {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            pos = whereClick(event.button.x, event.button.y);
            if (board.getCell(pos) != '.')
                return ;
            else
            {
                board.setCell(pos, *curr);
                makingCross(pos, ren);
                SDL_RenderPresent(ren);
                *curr = AI;
            } 
        }
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        pos = AIMove(board);
        board.setCell(pos, *curr);
        makingCircle(pos, ren);
        SDL_RenderPresent(ren);
        *curr = HUMAN;
    }
}


int main()
{
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Event event;
    Board board;
    char curr[1];
    char res;

    *curr = HUMAN;
    initGraphic(&win, &ren);

    while (!board.isFull() && !board.isWon(HUMAN, AI))
    {
        while (SDL_PollEvent(&event))
        {
            game(curr, board, ren, event);
            quitCheck(&event, win, ren);
        }
    }
    res = board.isWon(HUMAN, AI);
    if (res)
        std::cout << (board.checkWin(HUMAN) == true ? "Human" : "AI") << " has won !";
    else
        std::cout << "It is a tie !" << std::endl;

    destroyGraphic(win, ren);
}