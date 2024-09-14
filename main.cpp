#include <iostream>
#include <iomanip>  //for kbhit
#include <ctime>
#include <conio.h>
#include <windows.h>


using namespace std;

int width=90;
int height=36;
int x,y,foodX,foodY,score;
bool over;
int nTail; //length of snake tail;
int tailX[100],tailY[100];
enum Direction{STOP=0, LEFT,RIGHT,DOWN,UP};
Direction dir;

void setup(){
    over=false;
    score=0;
    y=height/2;
    x=width/2;
    srand(time(0));
    foodY=rand() % (height-1);
    foodX=rand() % (width-1);
    dir=STOP;
}


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw()
{
    gotoxy(0,0); // Clear the console
    // Creating top walls with '-'

    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            // Creating side walls with '|'
            if (j == 0 || j == width)
                cout << "|";
            // Creating snake's head with 'O'
            if (i == y && j == x)
                cout << "O";
            // Creating the sanke's food with '#'
            else if (i == foodY && j == foodX)
                cout << "F";
            // Creating snake's head with 'O'
            else {
                bool prTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j
                        && tailY[k] == i) {
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

    // Creating bottom walls with '-'
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;
}


void input()
{
    if(_kbhit()){ //detects keys input
        switch(_getch()){
        case 'a':
            dir=LEFT;
            break;
        case 'w':
            dir=UP;
            break;
        case 'd':
            dir=RIGHT;
            break;
        case 's':
            dir=DOWN;
            break;
        case 'x':
            over=true;
            break;
        }
    }
}



void logic(string username)
{
    //save previous head position
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    //for movement of tail along with the head
    for(int i=1;i<nTail;i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }

    switch(dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    //if snake hit boundary
    if(x==0  || x>=width || y==0 || y>=height)
    {
        over=true;
    }

    //foodCollision
    if(x==foodX && y==foodY)
    {
        score+=10;
        foodY=rand() % (height-1);
        foodX=rand() % (width-1);
        nTail++;

    }


    //collison with its own tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            over = true;
    }
    cout<<"username:"<<username<<endl;
    cout<<"SCORE: "<<score;

}


int main()
{
    setup();
    cout<<"PlayerName: "<<endl;
    string s;
    cin>>s;
    cout<<"select difficulty"<<endl;
    cout<<"1.easy  2.medium  3.difficult"<<endl;
    char c;
    cin>>c;
    int diff;
    switch(c)
    {
    case '1':
        diff=100;
        break;
    case '2':
        diff=50;
        break;
    case '3':
        diff=10;
        break;
    default:
        cout<<"Wrong INPUT"<<endl;
        break;
    }

    while(!over)
    {
        draw();
        input();
        logic(s);
        Sleep(diff);
    }

    return 0;
}
