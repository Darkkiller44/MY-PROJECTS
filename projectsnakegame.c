#include <stdio.h>
#include <conio.h>
#include <windows.h>

int gameover, score;
int x, y, fruitX, fruitY, height = 20, width = 40;
int tailX[100], tailY[100], nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

void setup() {
    gameover = 0;
    dir = STOP;
    x = height / 2;
    y = width / 2;
    fruitX = rand() % height;
    fruitY = rand() % width;
    score = 0;
}

void draw() {
    system("cls");
    for (int i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                printf("#");
            if (i == x && j == y)
                printf("O");
            else if (i == fruitX && j == fruitY)
                printf("F");
            else {
                int printTail = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == i && tailY[k] == j) {
                        printf("o");
                        printTail = 1;
                    }
                }
                if (printTail == 0)
                    printf(" ");
            }
            if (j == width - 1)
                printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < width + 2; i++)
        printf("#");
    printf("\n");
    printf("Score:%d", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        y--;
        break;
    case RIGHT:
        y++;
        break;
    case UP:
        x--;
        break;
    case DOWN:
        x++;
        break;
    default:
        break;
    }

    if (x >= height) x = 0; else if (x < 0) x = height - 1;
    if (y >= width) y = 0; else if (y < 0) y = width - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = 1;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % height;
        fruitY = rand() % width;
        nTail++;
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        Sleep(10); // sleep for 10 milliseconds
    }
    return 0;
}
