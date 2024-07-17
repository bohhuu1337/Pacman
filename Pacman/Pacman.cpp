#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

bool gameover;
const int shirota = 21;
const int visota = 20;
enum put { STOP, LEFT, RIGHT, UP, DOWN, EXIT };
enum ghost_move { STOP1, LEFT1, RIGHT1, UP1, DOWN1 };
put button;

char map[visota][shirota] = {
    "####################",
    "#@.................#",
    "#..................#",
    "#..###...#..#..#...#",
    "#..###...#..#..#...#",
    "#..###...#..#..#...#",
    "#..................#",
    "#..................#",
    "#..##...##...###...#",
    "#..##...##...###...#",
    " .................. ",
    "#..##...##...###...#",
    "#..##...##...###...#",
    "#..................#",
    "#..................#",
    "#..#####...#####...#",
    "#..#####...#####...#",
    "#..................#",
    "#&................&#",
    "####################"
};
char pred = ' ', sled = ' ', pred1 = ' ', sled1 = ' ';
int score = 0;
int shet = 0;
int x = 1;
int y = 1;
int ghostx = 18;
int ghosty = 18;
int ghostx1 = 18;
int ghosty1 = 1;

//первоначальные настройки
static void setup() {
    gameover = false;
    button = STOP;
    score = 0;
    srand(time(0)); 
}

//функция отрисовки карты и вывода счета
void draw() {
    system("cls");
    for (int i = 0; i < visota; i++) {
        for (int j = 0; j < shirota; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

//функция ввода влево, враво, вниз, вперед, выйти
void input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            button = LEFT;
            break;
        case 'd':
            button = RIGHT;
            break;
        case 'w':
            button = UP;
            break;
        case 's':
            button = DOWN;
            break;
        case 'x':
            button = EXIT;
            break;
        }
    }
}

//логика передвижения игрока
void logic() {
    switch (button) {
    case LEFT:
        if (x > 0 && map[y][x - 1] != '#') {
            if (x == 1 && y == 10) {
                map[y][x] = ' ';
                x = 18; y = 10;
                map[y][x] = '@';
            }
            else {
                if (map[y][x - 1] == '.') {
                    score = score + 1;
                }
                map[y][x - 1] = '@';
                map[y][x] = ' ';
                x = x - 1;
            }
        }
        button = STOP;
        break;
    case RIGHT:
        if (x < shirota - 1 && map[y][x + 1] != '#') {
            if (x == 18 && y == 10) {
                map[y][x] = ' ';
                y = 10; x = 1;
                map[y][x] = '@';
            }
            else {
                if (map[y][x + 1] == '.') {
                    score = score + 1;
                }
                map[y][x + 1] = '@';
                map[y][x] = ' ';
                x = x + 1;
            }
        }
        button = STOP;
        break;
    case UP:
        if (y > 0 && map[y - 1][x] != '#') {
            if (map[y - 1][x] == '.') {
                score = score + 1;
            }
            map[y - 1][x] = '@';
            map[y][x] = ' ';
            y = y - 1;
        }
        button = STOP;
        break;
    case DOWN:
        if (y < visota - 1 && map[y + 1][x] != '#') {
            if (map[y + 1][x] == '.') {
                score = score + 1;
            }
            map[y + 1][x] = '@';
            map[y][x] = ' ';
            y = y + 1;
        }
        button = STOP;
        break;
    case EXIT:
        gameover = true;
        break;
    }
    if ((y == ghosty && x == ghostx) || (y == ghosty1 && x == ghostx1)) {
        gameover = true;
        cout << "You died\t";
    }
}

//функция подсчета всей еды на карте и проверка на их отсутствие
void win() {
    for (int i = 0; i < visota; i++) {
        for (int j = 0; j < shirota; j++) {
            if (map[i][j] == '.') {
                shet = shet + 1;
            }
        }
    }
    if (shet == 0) {
        gameover = true;
        cout << "\tYou win";
    }
    shet = 0;
}

//функция логики движения 1 призрака
void ghostLogic() {
    int direction = (rand() % 4) + 1;
    switch (direction) {
    case LEFT1:
        if (ghosty1 > 0 && map[ghostx1][ghosty1 - 1] != '#' && map[ghostx1][ghosty1 - 1] != '&') {
            pred1 = sled1;
            sled1 = map[ghostx1][ghosty1 - 1];
            map[ghostx1][ghosty1 - 1] = '&';
            map[ghostx1][ghosty1] = pred1;
            ghosty1--;
        }
        break;
    case RIGHT1:
        if (ghosty1 < shirota - 1 && map[ghostx1][ghosty1 + 1] != '#' && map[ghostx1][ghosty1 + 1] != '&') {
            pred1 = sled1;
            sled1 = map[ghostx1][ghosty1 + 1];
            map[ghostx1][ghosty1 + 1] = '&';
            map[ghostx1][ghosty1] = pred1;
            ghosty1++;
        }
        break;
    case UP1:
        if (ghostx1 > 0 && map[ghostx1 - 1][ghosty1] != '#' && map[ghostx1 - 1][ghosty1] != '&') {
            pred1 = sled1;
            sled1 = map[ghostx1 - 1][ghosty1];
            map[ghostx1 - 1][ghosty1] = '&';
            map[ghostx1][ghosty1] = pred1;
            ghostx1--;
        }
        break;
    case DOWN1:
        if (ghostx1 < visota - 1 && map[ghostx1 + 1][ghosty1] != '#' && map[ghostx1 + 1][ghosty1] != '&') {
            pred1 = sled1;
            sled1 = map[ghostx1 + 1][ghosty1];
            map[ghostx1 + 1][ghosty1] = '&';
            map[ghostx1][ghosty1] = pred1;
            ghostx1++;
        }
        break;
    }
    if (y == ghosty1 && x == ghostx1) {
        gameover = true;
        cout << "You died\t";
    }
}

//функция логики движения 2 призрака
void ghost() {
    int direction = (rand() % 4) + 1;
    switch (direction) {
    case LEFT1:
        if (ghosty > 0 && map[ghostx][ghosty - 1] != '#' && map[ghostx][ghosty - 1] != '&') {
            pred = sled;
            sled = map[ghostx][ghosty - 1];
            map[ghostx][ghosty - 1] = '&';
            map[ghostx][ghosty] = pred;
            ghosty--;
        }
        break;
    case RIGHT1:
        if (ghosty < shirota - 1 && map[ghostx][ghosty + 1] != '#' && map[ghostx][ghosty + 1] != '&') {
            pred = sled;
            sled = map[ghostx][ghosty + 1];
            map[ghostx][ghosty + 1] = '&';
            map[ghostx][ghosty] = pred;
            ghosty++;
        }
        break;
    case UP1:
        if (ghostx > 0 && map[ghostx - 1][ghosty] != '#' && map[ghostx - 1][ghosty] != '&') {
            pred = sled;
            sled = map[ghostx - 1][ghosty];
            map[ghostx - 1][ghosty] = '&';
            map[ghostx][ghosty] = pred;
            ghostx--;
        }
        break;
    case DOWN1:
        if (ghostx < visota - 1 && map[ghostx + 1][ghosty] != '#' && map[ghostx + 1][ghosty] != '&') {
            pred = sled;
            sled = map[ghostx + 1][ghosty];
            map[ghostx + 1][ghosty] = '&';
            map[ghostx][ghosty] = pred;
            ghostx++;
        }
        break;
    }
    if (y == ghosty && x == ghostx) {
        gameover = true;
        cout << "You died\t";
    }
}

int main() {
    setup();
    while (!gameover) {
        draw();
        input();
        logic();
        ghost();
        ghostLogic();
        win();
    }
    return 0;
}
