#include "intro.h"
#define SCREEN_WIDTH 102 // user defined function= 8
#define SCREEN_HEIGHT 25 // struct= 1
void colorit(int col)    // condition= if-else only
{

    HANDLE hstdout;
    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout, col); // to set console coordinates
}

struct Letter // a structure containing alphabets drop,x and y axis coordinates.
{
    char alpha;
    int x_cord;
    int y_cord;
};

int score = 0; // number increases after a successful character is entered

void Level(int level) // number of level showing currently playing
{
    gotoxy(SCREEN_WIDTH + 5, 2);
    printf("LEVEL: %d", level);
}
void PrintScore(int score) // to print current score while playing game
{
    gotoxy(SCREEN_WIDTH + 5, 5);
    printf("SCORE: %d", score);
}

int sequenceCompleted(struct Letter *l, int count) // how many times the letter dropping sequence should go on
{
    for (int i = 0; i < count; i++)
    {
        if (l[i].y_cord <= SCREEN_HEIGHT)
        {
            return 0;
        }
    }
    return 1;
}

void generateRandomLetters(struct Letter *l, int letInseq) // to generate alphabets randomly not in sequence
{
    srand(time(NULL));
    int i;
    for (i = 0; i < letInseq; i++)
    {

        l[i].y_cord = rand() % 9 * -1;
        l[i].alpha = 'a' + rand() % 26;
    }
    int deviation;
    for (i = 0; i < letInseq; i++)
    {
        if (rand() % 2)
        {
            l[i].x_cord = (SCREEN_WIDTH / 2) + rand() % (SCREEN_WIDTH / 2); // how much deviation
        }
        else
        {
            l[i].x_cord = (SCREEN_WIDTH / 2) - rand() % (SCREEN_WIDTH / 2);
        }
    }
}

void printBorders() // to print borders of * on the sides for good look
{
    int i;
    for (i = 0; i <= SCREEN_WIDTH; i++)
    {
        gotoxy(i, 0);
        putch('*');
        gotoxy(i, SCREEN_HEIGHT + 1);
        putch('*');
    }

    for (i = 0; i <= SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH, i);
        putch('*');
        gotoxy(0, i);
        putch('*');
    }
}

int generateLevel(int level) // move on to next level if the player is going on successfuly
{
    int key = 0, index = 0;
    int i, j, MaxSequences = 6;
    int letInSeq = level; // LetInSeq is to how many letters drop in one sequence
    char playerInput;
    struct Letter l[letInSeq];
    int SleepDuration = (400) / level;
    for (i = 0; i < MaxSequences; i++)
    {
        generateRandomLetters(l, letInSeq);
        while (!sequenceCompleted(l, letInSeq))
        {
            for (j = 0; j < letInSeq; j++)
            {
                if (l[j].y_cord >= 2 && l[j].y_cord <= SCREEN_HEIGHT)
                {
                    gotoxy(l[j].x_cord, l[j].y_cord);
                    putch(l[j].alpha);
                }
            }
            Sleep(130);
            if (kbhit())
            {
                playerInput = getch(); // to get a character input from the user
                for (j = 0; j < letInSeq; j++)
                {
                    if (playerInput == l[j].alpha)
                    {
                        gotoxy(l[j].x_cord, l[j].y_cord);
                        putch(' ');
                        l[j].y_cord = SCREEN_HEIGHT + 1;
                        score++;
                        PrintScore(score);
                    }
                }
            }
            for (j = 0; j < letInSeq; j++)
            {
                if (l[j].y_cord >= 2 && l[j].y_cord <= SCREEN_HEIGHT)
                {
                    gotoxy(l[j].x_cord, l[j].y_cord);
                    putch(' ');
                }
                if (l[j].y_cord == SCREEN_HEIGHT)
                {
                    system("color 0C");
                    system("cls");
                    gotoxy(30, 9);
                    printf("\t\t\t\tGAME OVER\n\n\n\n\n\n\n\n\n\n\n\n");
                    gotoxy(30, 11);
                    printf("\t\t\t\tSCORE: %d\n\n\n\n\n\n\n\n\n\n\n\n", score);
                    printf("\n");
                    gotoxy(70, 12);
                    printf("\t\t\t\t      MADE BY\n\n\n\n\n\n\n\n\n\n\n\n");
                    gotoxy(70, 13);
                    printf("\t\t\t\t-------------------\n\n\n\n\n\n\n\n\n\n\n\n");
                    gotoxy(70, 14);
                    printf("\t\t\t\t|    ALI RAZA     |\n\n\n\n\n\n\n\n\n\n\n\n");
                    gotoxy(70, 15);
                    printf("\t\t\t\t|   HARIS JAMAL   |\n\n\n\n\n\n\n\n\n\n\n\n");
                    gotoxy(70, 16);
                    printf("\t\t\t\t|ABDUL ALEEM AHMED|\n\n\n\n\n\n\n\n\n\n\n\n");
                    gotoxy(70, 17);
                    printf("\t\t\t\t-------------------\n\n\n\n\n\n\n\n\n\n\n\n");
                    colorit(10);
                    while (key != 13)
                    {
                        if (index == 1)
                        {
                            colorit(10);
                        }

                        gotoxy(15, 15);

                        printf("\t\t\t\t\t\tPlay Again");

                        colorit(15);

                        if (index == 2)
                        {
                            colorit(10);
                        }
                        gotoxy(15, 17);

                        printf("\t\t\t\t\t\tExit");

                        colorit(15);

                        key = getch();

                        if (key == 80)
                        {
                            index++;
                        }
                        else if (key == 72)
                        {
                            index--;
                        }

                        if (index == 3)
                        {
                            index = 1;
                        }

                        if (index == 0)
                        {
                            index = 2;
                        }
                    }

                    if (index == 1)
                    {
                        score = 0;
                        system("cls");
                        system("color F4");
                        PrintScore(score);
                        printBorders();
                        int level;
                        for (level = 1; level <= 5; level++)
                        {
                            Level(level);
                            if (generateLevel(level) == 0)
                            {
                                break;
                            }
                        }
                        if (level > 4)
                        {
                            system("cls");
                            gotoxy(30, 11);
                            printf("\t\t\t\tWell Played!\n\n\n\n\n\n\n\n\n\n\n\n");
                            gotoxy(30, 13);
                            printf("\t\t\t\tSCORE: %d\n\n\n\n\n\n\n\n\n\n\n\n", score);
                            gotoxy(20, 20);
                        }
                    }
                    else if (index == 2)

                    {

                        system("taskkill/IM ConsolePauser.exe");
                    }
                    return 0;
                }
                l[j].y_cord++;
            }
        }
    }
    return 1;
}

void showmenu() // the main menu
{
    system("COLOR 0C");
    int index = 1;

    int key = 0;

    system("cls");

    for (int i = 1; i <= 100; i++)
    { // for horizontal border
        gotoxy(i, 0);
        putch('*'); // for upper
        gotoxy(i, 25 + 1);
        putch('*'); // for lower
    }
    for (int i = 1; i <= 25; i++)
    { // for vertical border
        gotoxy(100, i);
        putch('*'); // right line
        gotoxy(1, i);
        putch('*'); // left line
    }

    while (key != 13)
    {

        gotoxy(1, 8);

        colorit(15);

        printf("\t\t\t\t\t\t============");

        gotoxy(1, 9);

        colorit(15);

        printf("\t\t\t\t\t\tTYPING TUTOR");

        gotoxy(1, 10);

        printf("\t\t\t\t\t\t============");

        gotoxy(1, 13);

        colorit(15);

        if (index == 1)
        {
            colorit(12);
        }

        printf("\t\t\t\t\t\tSTART GAME");

        gotoxy(1, 15);

        colorit(15);

        if (index == 2)
        {
            colorit(12);
        }

        printf("\t\t\t\t\t\tHELP");

        gotoxy(1, 17);

        colorit(15);

        if (index == 3)
        {
            colorit(12);
        }

        printf("\t\t\t\t\t\tEXIT");

        gotoxy(1, 8);

        colorit(15);

        /////////////UP=224/72 Down=224/80 Enter=13

        key = getch();

        if (key == 80)
        {
            index++;
        }
        else if (key == 72)
        {
            index--;
        }

        if (index == 4)
        {
            index = 1;
        }

        if (index == 0)
        {
            index = 3;
        }
    }

    if (index == 1)

    {

        system("cls");
        system("color F4");
        PrintScore(score);
        printBorders();
        int level;
        for (level = 1; level <= 5; level++)
        {
            Level(level);
            if (generateLevel(level) == 0)
            {
                break;
            }
        }
        if (level > 4)
        {
            system("cls");
            gotoxy(30, 11);
            printf("\t\t\t\tWell Played!\n\n\n\n\n\n\n\n\n\n\n\n");
            gotoxy(30, 13);
            printf("\t\t\t\tSCORE: %d\n\n\n\n\n\n\n\n\n\n\n\n", score);
            gotoxy(20, 20);
        }
    }
    else if (index == 2)

    {

        system("cls");
        colorit(10);
        for (int i = 1; i <= 80; i++)
        { // for horizontal border
            gotoxy(i, 0);
            putch('*'); // for upper
            gotoxy(i, 25 + 1);
            putch('*'); // for lower
        }
        for (int i = 1; i <= 25; i++)
        { // for vertical border
            gotoxy(80, i);
            putch('*'); // right line
            gotoxy(1, i);
            putch('*'); // left line
        }
        colorit(15);
        gotoxy(10, 4);
        printf("Use the UP and DOWN arrow keys to navigate through the options\t\n\n");
        gotoxy(10, 6);
        printf("The user must enter that particular word dropping on the screen");
        gotoxy(20, 10);
        printf("Words will be dropped from the above border\t\n\n");
        gotoxy(20, 12);
        printf("The user must enter that particular word");
        gotoxy(20, 14);
        printf("before it hits the lower bottom");
        gotoxy(20, 18);
        printf("It will help to improve the typing spped\t\n\n");
        gotoxy(20, 20);
        printf("of the player in a fun way, giving advantages");
        gotoxy(20, 22);
        printf("for real life applications");
        colorit(12);
        gotoxy(85, 13);
        printf("PRESS ANY KEY");
        gotoxy(85,15);
		printf("TO GO BACK TO MAIN MENU...");
        getch();

        showmenu();
    }
    else if (index == 3)

    {

        system("taskkill/IM ConsolePauser.exe");
    }
}

int main()

{
    system("COLOR 0C"); // the background and font color settings

    Intro(); // animation at the starting of program

    showmenu(); // to go to main menu
}


