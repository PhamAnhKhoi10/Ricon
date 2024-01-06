#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <Windows.h>


#define TOP_WALL 3
#define BOTTOM_WALL 23
#define LEFT_WALL 3
#define RIGHT_WALL 83
#define LOSE false
#define WIN 10
#define KEY_NONE -1

typedef struct
{
    int x;
    int y;
}
coordinate;

coordinate place_eat_me(void);
int inputKey();
bool lose(coordinate pacman);
void gotoXY(int x, int y);
void change_direction(coordinate* cursor_pacman);
void print_pacman(void);
void point(void);
void print_wall(void);
void print_gate(coordinate gate);
void teleport(coordinate *cursor_pacman);
void noCursorType();

int pts = 0;
int sentinel = 1;

coordinate gate1;
coordinate gate2;
coordinate gate3;
coordinate gate4;


int main(void)
{ 	
    SetConsoleOutputCP(CP_UTF8);
    gate1.x = LEFT_WALL + 4;
    gate1.y = BOTTOM_WALL - 3;

    gate2.x = RIGHT_WALL - 4;
    gate2.y = TOP_WALL + 3;

    gate3.x = LEFT_WALL + 4;
    gate3.y = TOP_WALL + 3;

    gate4.x = RIGHT_WALL - 4;
    gate4.y = BOTTOM_WALL - 3;

    //Tọa độ ban đầu của pacman
    coordinate pacman;
    pacman.x = 43;
    pacman.y = 13;

    //Xóa màn hình cho gọn
    system("cls");

    //In tường
    print_wall();

    //In điểm
    point();

    //In lần đầu;
    gotoXY(pacman.x, pacman.y);
    print_pacman();

    coordinate eat_me = place_eat_me();
    gotoXY(eat_me.x, eat_me.y);
    printf("\033[0;36m");
    printf("●");

    print_gate(gate1);
    print_gate(gate2);
    print_gate(gate3);
    print_gate(gate4);

    while (sentinel == 1)
    {
        noCursorType();
        //Chuyển hướng & di chuyển
        change_direction(&pacman);
        teleport(&pacman);

        //In mồi mới & update điểm
        if (pacman.x == eat_me.x && pacman.y == eat_me.y)
        {
            pts++;
            point();

            eat_me = place_eat_me();
            gotoXY(eat_me.x, eat_me.y);
            printf("\033[0;36m");
    		printf("●");
        }

        //Xử lý thua
        if (lose(pacman) == LOSE)
        {
            system("cls");
            printf("GAME OVER\n");
            return 1;
        }

        //Phá đảo màn
        if (pts == WIN)
        {
            pts = 0;
            sentinel = 2;
        }
    }

    system("cls");

    //ENTER để qua màn
    printf("CONGRATULATION\n");
    printf("Completed round 1, enter to play round 2\n");
    
    char press;
    scanf("%c", press);

    system("cls");

    /* Màn 2
    while(sentinel == 2)
    {

    }

    Màn 3
    while(sentinel == 3)
    {

    }*/
}


void print_gate(coordinate gate)
{	printf("\033[0;32m");
    gotoXY(gate.x, gate.y);
    printf("▓");
}

void _case_(coordinate pacman)
{
    if(gate1.x == pacman.x && gate1.y == pacman.y)
    {
        print_gate(gate1);
    }

    if(gate2.x == pacman.x && gate2.y == pacman.y)
    {
        print_gate(gate2);
    }

    if(gate3.x == pacman.x && gate3.y == pacman.y)
    {
        print_gate(gate3);
    }

    if(gate4.x == pacman.x && gate4.y == pacman.y)
    {
        print_gate(gate4);
    }
}

void teleport(coordinate *cursor_pacman)
{
    if(cursor_pacman->x == gate1.x && cursor_pacman->y == gate1.y)
    {
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        printf(" ");
        _case_(*cursor_pacman);

        cursor_pacman->x = gate2.x + 1;
        cursor_pacman->y = gate2.y;

        gotoXY(cursor_pacman->x, cursor_pacman->y);
        print_pacman();
    }

    if(cursor_pacman->x == gate2.x && cursor_pacman->y == gate2.y)
    {
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        printf(" ");
        _case_(*cursor_pacman);

        cursor_pacman->x = gate3.x + 1;
        cursor_pacman->y = gate3.y;

        gotoXY(cursor_pacman->x, cursor_pacman->y);
        print_pacman();
    }

    if(cursor_pacman->x == gate3.x && cursor_pacman->y == gate3.y)
    {
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        printf(" ");
        _case_(*cursor_pacman);

        cursor_pacman->x = gate4.x + 1;
        cursor_pacman->y = gate4.y;

        gotoXY(cursor_pacman->x, cursor_pacman->y);
        print_pacman();
    }

    if(cursor_pacman->x == gate4.x && cursor_pacman->y == gate4.y)
    {
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        printf(" ");
        _case_(*cursor_pacman);

        cursor_pacman->x = gate1.x + 1;
        cursor_pacman->y = gate1.y;

        gotoXY(cursor_pacman->x, cursor_pacman->y);
        print_pacman();
    }
}

void block(void)
{
}

void print_wall(void)
{
   printf("\033[0;34m");
    //draw TOP_WALL
    for(int i=LEFT_WALL+1; i<= (RIGHT_WALL-1); i++){
        gotoXY(i,TOP_WALL);
        printf("═");
        gotoXY(i,BOTTOM_WALL);
        printf("═");
    }
    //draw LEFT_WALL
    for(int j=TOP_WALL+1; j<=(BOTTOM_WALL-1);j++){
        gotoXY(LEFT_WALL,j);
        printf("║\n");
        gotoXY(RIGHT_WALL,j);
        printf("║\n");
    }
    gotoXY(LEFT_WALL,TOP_WALL);
    printf("╔");
    gotoXY(LEFT_WALL,BOTTOM_WALL);
    printf("╚");
    gotoXY(RIGHT_WALL,BOTTOM_WALL);
    printf("╝");
    gotoXY(RIGHT_WALL,TOP_WALL);
    printf("╗");
}


coordinate place_eat_me(void)
{
    coordinate eat_me;

    srand(time(NULL));
    eat_me.x = LEFT_WALL + 1 + rand() % (RIGHT_WALL - LEFT_WALL - 1);
    eat_me.y = TOP_WALL + 1 + rand() % (BOTTOM_WALL - TOP_WALL - 1);

    return eat_me;
}

void point(void)
{
    gotoXY(3, 26);
    printf("POINTS: %i", pts);
}

void print_pacman(void)
{
	noCursorType();
    printf("\033[0;33m");
    printf("♛");
}

bool lose(coordinate pacman)
{
    if (pacman.x == LEFT_WALL || pacman.x == RIGHT_WALL || pacman.y == TOP_WALL || pacman.y == BOTTOM_WALL)
    {
        return false;
    }
    return true;
}

void change_direction(coordinate* cursor_pacman)
{
   int key = tolower(inputKey());
    if (key == 'a')
    {
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        printf(" ");

        cursor_pacman->x--;

        //In pacman mới
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        print_pacman();

    }
    else if (key == 'd')
    {
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        printf(" ");

        cursor_pacman->x++;

        //In pacman mới
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        print_pacman();

    }
    else if (key == 'w')
    {
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        printf(" ");

        cursor_pacman->y--;

        //In pacman mới
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        print_pacman();

    }
    else if (key == 's')
    {
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        printf(" ");

        cursor_pacman->y++;

        //In pacman mới
        gotoXY(cursor_pacman->x, cursor_pacman->y);
        print_pacman();

    }

}


int inputKey()
{
    if (_kbhit())
    {
        int key = _getch();

        if (key == 224)
        {
            key = _getch();
            return key + 1000;
        }

        return key;
    }
    else
    {
        return KEY_NONE;
    }

    return KEY_NONE;
}


void gotoXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void noCursorType()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 20;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void setTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}




