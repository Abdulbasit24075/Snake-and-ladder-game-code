#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string> 
using namespace std;

void hideConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)//this is used to go to certain pint on a console
{
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOutput, scrn);
}

void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}
// Function to draw a grid on the console
void daba(int  onerowboxdim, int onecolboxdim, int rows, int cols, char sym = -37)//
{
    for (int ri = 0; ri <= rows; ri++)
    {
        for (int ci = 0; ci <= cols; ci++)
        {

            if (ri % onerowboxdim == 0 || ci % onecolboxdim == 0) // Draw grid boundaries
            {
                gotoRowCol(ri, ci);
                cout << sym;

            }
        }
    }
}
// Function to print numbers in the grid
void printing_numbers_in_grid(int row, int col, int rowboxdim, int colboxdim,char sym) {
    int prnum;
    int num = 1;
    for (int i = 0; i < row; i += rowboxdim) {

        for (int k = 0; k < col; k += colboxdim) {

            gotoRowCol((rowboxdim/2.0)+i, (colboxdim/2.0)+k);
            prnum = 101 - num;// Calculate the number for the cell actually console strat from top left so there we start to need numbering from 100 and then go till 1 
            cout << prnum;// Print the number
                num++;
                if (i == 0 && k == 0) {
                    gotoRowCol(((rowboxdim / 2.0) + i)+0.2, (colboxdim / 2.0) + k -0.5);
                    cout << "Win ";
                }
                

        }
    }

}
// Function to initialize the positions of snakes and ladders
void initaializationofsnake_and_ladder(int snkstart[], int snkend[],int ladstart[],int ladend[]) {

    snkstart[0]=22, snkstart[1]=57, snkstart[3]=94, snkstart[2] = 71;
    snkend[0] = 11, snkend[1] = 42, snkend[3] = 64, snkend[2] = 55;
    ladstart[0] = 5, ladstart[1] = 26, ladstart[3] = 62, ladstart[2] =50 ;
    ladend[0] = 12, ladend[1] = 46, ladend[3] = 85, ladend[2] = 81;

}
// Function to draw the dice box on the screen
void draw_a_box(int row,int col) {

    gotoRowCol(row,col);
    cout << "|ROLLING DICE|";
    gotoRowCol(row+4, col);
    cout << "$------------$";
    



}
// Function to simulate rolling a dice
//As the function also perform one more function of that if (6) comes then player will take turn again until 3 times (6) comes
int roll_a_dice(int  row,int col) {
    int RD,sd,gd;
    int rand();
    int clickRowofdice, clickColofdice;
    int t = 0;
    srand(time(0));
    gotoRowCol(row+2 , col-1);
    cout << "PRESS (R) = ";
    char l;
    do
    {
       
        cin >> l;

    } while (l!='R');
    gotoRowCol(row + 2, col-1);
    cout << "             ";
    int val;
        while (t < 100) {


            RD = (rand() % 6) + 1;// Generate random dice roll,as it have range from (1 to 5)

            gotoRowCol(row + 2, col + 5);
            cout << RD;
            Sleep(100);


            t += rand() % 11;

           
        }
        t= 0;
        val = RD;
        if (RD == 6) {// Check for consecutive rolls on dice roll 6

            gotoRowCol(row + 2, col + 5);
            cout << " ";
            while (t < 100) {


                RD = (rand() % 6) + 1;

                gotoRowCol(row + 2, col + 5);
                cout << RD;
                Sleep(100);


                t += rand() % 12;
               


            }
            val = val + RD;
        }
        t = 0;
        if (RD == 6) {

            gotoRowCol(row + 2, col + 5);
            cout << " ";
            while (t < 100) {


                RD = (rand() % 6) + 1;

                gotoRowCol(row + 2, col + 5);
                cout << RD;
                Sleep(100);


                t += rand() % 9;



            }
            val = val + RD;
        }
        if (val == 18)// Prevent infinite loop for three consecutive 6s
            return 0;
        
        
   
    return val;
}
void draw_a_line(int p1c, int p1r, int p2c, int p2r, char sym = -37) { 
    int cind = 0, rind = 0;
    for (float xaxis = 0; xaxis <= 1; xaxis += 0.01)
    {
        cind = round(p1c * xaxis + p2c * (1 - xaxis));
        rind = round(p1r * xaxis + p2r * (1 - xaxis));
        gotoRowCol(rind, cind);
        cout << sym;
    }




}
void  snake_ladder_display() // AS on console screen it became really poor to make snakes and ladder it look so dirty ,so i use ( gotoRowCol) function to point out position on console   
{//and then write postion in table    
    {
  
    draw_a_line(72, 14, 98, 14, -37);
    gotoRowCol(17, 74);
    cout << "SNAKES POS";
    gotoRowCol(17, 87);
    cout << "lADDER POS";
    gotoRowCol(23, 74);
    cout<<"1:" << "22 to 11";
    gotoRowCol(29, 74);
    cout << "2:" << "57 to 42";
    gotoRowCol(35, 74);
    cout << "3:" << "71 to 55";
    gotoRowCol(41, 74);
    cout << "4:" << "94 to 64";
    gotoRowCol(23, 87);
    cout << "1:" << "5 to 12";
    gotoRowCol(29, 87);
    cout << "2:" << "26 to 46";
    gotoRowCol(35, 87);
    cout << "3:" << "50 to 81";
    gotoRowCol(41, 87);
    cout << "4:" << "62 to 85";
    draw_a_line(72, 14, 72, 44, -37);
    draw_a_line(98, 14, 98, 44, -37);
    draw_a_line(72, 44, 98, 44, -37);
    draw_a_line(85, 14, 85, 44, -37);//half of col
    draw_a_line(72, 20, 98, 20, -37);//adjustment as by row
    
    
}
int main()
{
    gotoRowCol(2, 23);
 
   int ply;

    cout << "***SNAKE AND LADDER GAME PRESENTED BY BASIT***";// starting of game
    gotoRowCol(6, 30);
    cout << "How many players want to play = ";// No of player
    cin >> ply;
    gotoRowCol(9, 34);
    const int total_ply_names = 4;
    string playerNames[total_ply_names];
    switch (ply) {// Selection accorting to number of players

    case 1:
        {
            cout << "Enter PLAYER Name ";

        }
        break;

    case 2 :
        {
            cout << "Enter Two PLAYERS Names ";

        }
        break;
    case 3:
        {
            cout << "Enter Three PLAYERS Names ";

        }
        break;
    case 4:
        {
            cout << "Enter Four PLAYERS Names ";

        }
        break;
    }
    
    for (int i = 0; i < ply; i++) {

        gotoRowCol(11+i, 40);
        cout << i + 1<<": ";
        cin  >> playerNames[i];
    }
    gotoRowCol(17, 36);
    cout << "   LETS START ";
    gotoRowCol(19, 36);
    cout << "  PLEASE WAIT ---";
    
  
    switch (ply) {

    case1:
        {
          const int   player_array_size = 1;
        }
        break;
    case2:
        {
          const int   player_array_size = 2;
        }
        break;
    case3:
        {
           const int  player_array_size = 3;
        }
        break;


    }
 
    Sleep(3000);
    // it is used to show loading 
    for (int i = 0; i < ply; i++) {

        gotoRowCol(11 + i, 40);
        cout << "                   ";

    }

    gotoRowCol(2, 23);

    cout << "                                               ";
    gotoRowCol(6, 30);
    cout << "                                        ";
    gotoRowCol(9, 34);
    cout << "                              ";
    gotoRowCol(17, 36);
   
    cout << "                  ";
    gotoRowCol(19, 36);
    cout << "                     ";
    const int cap = 10;

    int playerpos[cap] = { 0 };

    int Rolling;
    const int R = 70;
    const int C = 70;
    const int onerowboxdim = R / 10;
    const int onecolboxdim = C / 10;
    char sym = -37;
    daba(onerowboxdim, onecolboxdim, R, C);
    printing_numbers_in_grid(R, C, R / 10, C / 10, -37);
    draw_a_box(0, 71);
    snake_ladder_display();


    const int snakesize = 4, laddersize = 4;
    int snkstart[snakesize], snkend[snakesize];
    int ladstart[laddersize], ladend[laddersize];
    initaializationofsnake_and_ladder(snkstart, snkend, ladstart, ladend);
    hideConsoleCursor();
    int PREVR[4]={100,100,100,100}, PREVC[4]={100,100,100,100};
    int PTurn = 0;
    bool GD = false;
    int EXTRAVAR1 ;
    for (int i = 0; i < ply ; i++) {

        gotoRowCol(8 + i*2, 71);
        cout <<"PLAYER " <<i+1<<" is "<< playerNames[i];
        
    }
   
    while (!GD)
    {
        gotoRowCol(6, 71);
        cout << "@ PLAYER " << PTurn + 1 << " Its YOUR TURN";// this will display player name according to turn 
        Rolling = roll_a_dice(0, 72);

        playerpos[PTurn] += Rolling;
        Sleep(3500);
       
        for (int i = 0; i < snakesize; i++)
        {
            if (playerpos[PTurn ] == snkstart[i])  {
                playerpos[PTurn] = snkend[i]; 
            }
        }
        for (int i = 0; i < laddersize; i++)
        {
            if (playerpos[PTurn] == ladstart[i]) {
                playerpos[PTurn] = ladend[i]; 
            }
        } 
        
        EXTRAVAR1 = 0;
        EXTRAVAR1 = 100 - playerpos[PTurn];
        int rowofplayer = EXTRAVAR1 / 10;
        int colofplayer= EXTRAVAR1 % 10;
      
            gotoRowCol(onerowboxdim * rowofplayer + onerowboxdim * 3 / 4, onecolboxdim * colofplayer + onecolboxdim / 2);
           

        if (PTurn == 0) {
            gotoRowCol(PREVR[0], PREVC[0]);//now we are watching turns ,that is some specific turn come then we show the position of players at secific postion     
            cout << "  ";

            gotoRowCol(onerowboxdim * rowofplayer + onerowboxdim * 3 / 4, onecolboxdim * colofplayer + onecolboxdim / 2);
            Sleep(100);
            cout << "P1";
            Sleep(100);
            PREVR[0] = onerowboxdim * rowofplayer + onerowboxdim * 3 / 4, PREVC[0] = onecolboxdim * colofplayer + onecolboxdim / 2;//and then previous position is stored in array at specific address to remove the output 
        }// of array and next time that address of spcific array is used to remove the symbol
        else if (PTurn == 1) {
            gotoRowCol(PREVR[1], PREVC[1]);
            cout << "  ";

            gotoRowCol(onerowboxdim * rowofplayer + onerowboxdim * 3 / 4, onecolboxdim * colofplayer + onecolboxdim / 2);
            Sleep(100);
            cout << "P2";
            Sleep(100);
            PREVR[1] = onerowboxdim * rowofplayer + onerowboxdim * 3 / 4, PREVC[1] = onecolboxdim * colofplayer + onecolboxdim / 2;

        }
        else if (PTurn == 2) {
            gotoRowCol(PREVR[2], PREVC[2]);
            cout << "  ";

            gotoRowCol(onerowboxdim * rowofplayer + onerowboxdim * 3 / 4, onecolboxdim * colofplayer + onecolboxdim / 2);
            Sleep(100);
            cout << "P3";
            Sleep(100);
            PREVR[2] = onerowboxdim * rowofplayer + onerowboxdim * 3 / 4, PREVC[2] = onecolboxdim * colofplayer + onecolboxdim / 2;

        }
        else if (PTurn == 3) {
            gotoRowCol(PREVR[3], PREVC[3]);
            cout << "  ";

            gotoRowCol(onerowboxdim* rowofplayer + onerowboxdim * 3 / 4, onecolboxdim* colofplayer + onecolboxdim / 2);
            Sleep(100);
            cout << "P4";
            Sleep(100);
            PREVR[3] = onerowboxdim * rowofplayer + onerowboxdim * 3 / 4, PREVC[3] = onecolboxdim * colofplayer + onecolboxdim / 2;
        }


        if (playerpos[PTurn] >= 100){// if player of i turn reach position 100 safely than we say that player of pturn win 
            gotoRowCol(46, 73);
            cout << "Player " << PTurn + 1 << " wins!" << endl;
            gotoRowCol(49, 73);
            cout << "CONGRAGULATION " << playerNames[PTurn ];
            GD = true;
        }
        else
        {
           
            PTurn = (PTurn + 1) % ply;
            GD = false;
        }

        
    }
    _getch();


    
    return 0;
}