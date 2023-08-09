#include "Board.hpp"

void initGraphic(SDL_Window **win, SDL_Renderer **ren)
{
    *win = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    *ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    initDraw(*ren);
    SDL_RenderPresent(*ren);
}

void destroyGraphic(SDL_Window *win, SDL_Renderer *ren)
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

void quitCheck(SDL_Event *event, SDL_Window *win, SDL_Renderer *ren)
{
    if (event->type == SDL_QUIT || (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE))
    {
        destroyGraphic(win, ren);
        exit(0);
    }
}

void makingCross(int pos, SDL_Renderer *ren)
{
    if (pos >= 0 && pos <= 2)
    {
        SDL_RenderDrawLine(ren, (pos * 200) + 50, 50, (pos * 200) + 150, 150);
        SDL_RenderDrawLine(ren, (pos * 200) + 150, 50, (pos * 200) + 50, 150);
    }
    else if (pos >= 3 && pos <= 5)
    {
        SDL_RenderDrawLine(ren, ((pos - 3) * 200) + 50, 250, ((pos - 3) * 200) + 150, 350);
        SDL_RenderDrawLine(ren, ((pos - 3) * 200) + 150, 250, ((pos - 3) * 200) + 50, 350);
    }
    else
    {
        SDL_RenderDrawLine(ren, ((pos - 6) * 200) + 50, 450, ((pos - 6) * 200) + 150, 550);
        SDL_RenderDrawLine(ren, ((pos - 6) * 200) + 150, 450, ((pos - 6) * 200) + 50, 550);
    }
}

void initDraw(SDL_Renderer *ren)
{
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderDrawLine(ren, 200, 0, 200, 600);
    SDL_RenderDrawLine(ren, 400, 0, 400, 600);
    SDL_RenderDrawLine(ren, 0, 200, 600, 200);
    SDL_RenderDrawLine(ren, 0, 400, 600, 400);
}

static void SDL_RenderDrawCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y) {
        // Dessiner les huit points symétriques
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);

        y++;
        if (radiusError < 0) {
            radiusError += 2 * y + 1;
        } else {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
}

void makingCircle(int pos, SDL_Renderer *ren)
{
    if (pos >= 0 && pos <= 2)
        SDL_RenderDrawCircle(ren, (pos * 200) + 100, 100, 50);
    else if (pos >= 3 && pos <= 5)
        SDL_RenderDrawCircle(ren, ((pos - 3) * 200) + 100, 300, 50);
    else
        SDL_RenderDrawCircle(ren, ((pos - 6) * 200) + 100, 500, 50);
}

int whereClick(int posX, int posY)
{
    int x = posX / 200;
    int y = posY / 200;
    return (x + (y * 3));
}