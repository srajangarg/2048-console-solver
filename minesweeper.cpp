#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define UNCLICKEDCHAR 35
#define BOMBCHAR 153
#define FLAGCHAR 157
#define CLICKEDBUTZERO 48
#define BOMB 9
#define FLAG 8
#define CORRECT 251
#define WRONG 88
using namespace std;


void SetColor(int value);
void clickPos(int bombgrid[][20],int grid[][20],int N,int x,int y,bool &flaggameover);//main part of the program
int searchValidNeighbours(int bombgrid[][20],int grid[][20],int N,int x,int y); //searches valid neighbors and returns number of bombs
void placeBombs(int bombgrid[][20],int Nbomb,int N);                     //placing Nbomb bombs on the bombgrid
int GetRandomNumber(int n);
void printGrid(int grid[][20],int N);                       //printing the minesweeper grid
bool WinCondition(int bombgrid[][20],int grid[][20],int N); //checking if all unbombed location have been clicked
bool displayBombs(int bombgrid[][20],int grid[][20],int N);


int main()
{
    char unclicked=UNCLICKEDCHAR,bomb=BOMBCHAR,clickzero=CLICKEDBUTZERO,flag=FLAGCHAR,correct=CORRECT,wrong=WRONG;
    int bombgrid[20][20];
    bool flaggameover=false;
    int grid[20][20];                             //grid is the grid seen by the user
    int N,Nbomb,currentstatus,numberofturns=0;
    int i,j,k,x,y,xflag,yflag;
    cout<<"Welcome to MineSweeper! "<<endl<<endl;
    cout<<"Instructions:\nFill in the coordinates in 'xcoordinate *space* ycordinate' \n(without the quote marks)\nUse negative coordinates '-x -y' to flag location(x y).\nUse the same to unflag a flagged location.\n\nSymbols:"<<endl;
    SetColor(2);cout<<unclicked<<"-->Unclicked part of grid"<<endl;
    SetColor(12);cout<<bomb<<"-->Bombs!"<<endl;
    SetColor(6);cout<<clickzero<<"-->Indicates no bombs in surroundings. Same as blank pressed tile."<<endl;
    SetColor(12);cout<<flag<<"-->Flags!"<<endl;
    SetColor(10);cout<<correct<<"-->Correctly flagged bomb"<<endl;
    SetColor(12);cout<<wrong<<"-->Incorrectly flagged tile"<<endl;SetColor(7);

    cout<<"\nEnter N for NxN grid(max 20):";cin>>N;
    if(N>20){cout<<"Invalid N;";return -1;}

    cout<<"No. of bombs?:";cin>>Nbomb;
    if(Nbomb>(N*N)){cout<<"Invalid number of bombs!"; return -1;}   //if bombs> total spaces

     for(i=0;i<N;i++)
        for(j=0;j<N;j++)                                            //intializing all elements in bombgrid to 0
            bombgrid[i][j]=0;                                       //0 represents no bomb, on the grid, 1 represents a bomb

    for(i=0;i<N;i++)
        for(j=0;j<N;j++)                                            //intializing all elements in grid to -1 (meaning unclicked)
            grid[i][j]=-1;


    placeBombs(bombgrid,Nbomb,N);
    printGrid(grid,N);
    while(!WinCondition(bombgrid,grid,N) && !flaggameover)                  //main loop which keeps iterating till user clicks on bomb, or wins
    {
        cout<<"\nEnter coordinates to click (x,y)(x is horizontal):";cin>>y>>x;

        if(x>(N-1) || y>(N-1))
        {
            cout<<"\nInvalid Coordinates";
            continue;
        }
        if((x<0 && (y==0||y<0))||((x==0||x<0) && y<0))
        {
            if(grid[-x][-y]==FLAG){grid[-x][-y]=-1;printGrid(grid,N);}
            else{grid[-x][-y]=FLAG;
                    printGrid(grid,N);}                                      //changing value of that particular location to FLAG
        }
        else
        {
            clickPos(bombgrid,grid,N,x,y,flaggameover);
            numberofturns++;
            printGrid(grid,N);
        }

    }

    if(WinCondition(bombgrid,grid,N))
    {
        cout<<"\n\nYOU WIN!!\n\nYou did it in "<<numberofturns<<" turns!"<<endl;    //the loop ended in two cases, have to check
    }
    system("PAUSE");
    cout<<endl;                                                                             //if he lost or won
    return 0;

}

bool displayBombs(int bombgrid[][20],int grid[][20],int N)
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            if(bombgrid[i][j]==1){if(grid[i][j]==FLAG){grid[i][j]=CORRECT;}else{grid[i][j]=BOMB;}}
        }
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            if(grid[i][j]==FLAG){grid[i][j]=WRONG;}
        }
    return true;
}

void clickPos(int bombgrid[][20],int grid[][20],int N,int x,int y,bool &flaggameover)
{
    int n,x1=x-1,y1=y-1,x2=x+1,y2=y+1;
    n=searchValidNeighbours(bombgrid,grid,N,x,y);

    if(grid[x][y]!=-1){return;}
    else if(bombgrid[x][y]==1)
    {
        flaggameover=displayBombs(bombgrid,grid,N);
        cout<<"\n\nYou clicked on a BOMB! GAME OVER!!\n";
        return;
    }
    else
    {
        if(n!=0){grid[x][y]=n;}
        else //0 bombs in surroundings
        {
            grid[x][y]=0;
            if(y1>=0)           {clickPos(bombgrid,grid,N,x,y1,flaggameover);}               //checking if adjacent cells are valid or not and clicking them
            if(y1>=0 && x2<N)   {clickPos(bombgrid,grid,N,x2,y1,flaggameover);}              //if no bombs are present in any of them
            if(x2<N)            {clickPos(bombgrid,grid,N,x2,y,flaggameover);}
            if(y2<N && x2<N)    {clickPos(bombgrid,grid,N,x2,y2,flaggameover);}
            if(y2<N)            {clickPos(bombgrid,grid,N,x,y2,flaggameover);}
            if(y2<N && x1>=0)   {clickPos(bombgrid,grid,N,x1,y2,flaggameover);}
            if(x1>=0)           {clickPos(bombgrid,grid,N,x1,y,flaggameover);}
            if(x1>=0 && y1>=0)  {clickPos(bombgrid,grid,N,x1,y1,flaggameover);}
        }
        return;
    }

}
int searchValidNeighbours(int bombgrid[][20],int grid[][20],int N,int x,int y)
{
        int countBomb=0,y1=y-1,y2=y+1,x1=x-1,x2=x+1;

        if(y1>=0)           {if(bombgrid[x][y1]==1){countBomb++;}}
        if(y1>=0 && x2<N)   {if(bombgrid[x2][y1]==1){countBomb++;}}
        if(x2<N)            {if(bombgrid[x2][y]==1){countBomb++;}}
        if(y2<N && x2<N)    {if(bombgrid[x2][y2]==1){countBomb++;}}
        if(y2<N)            {if(bombgrid[x][y2]==1){countBomb++;}}
        if(y2<N && x1>=0)   {if(bombgrid[x1][y2]==1){countBomb++;}}
        if(x1>=0)           {if(bombgrid[x1][y]==1){countBomb++;}}
        if(x1>=0 && y1>=0)  {if(bombgrid[x1][y1]==1){countBomb++;}}

        return countBomb;
}
void printGrid(int grid[][20],int N)
{
    char unclicked=UNCLICKEDCHAR,bomb=BOMBCHAR,clickzero=CLICKEDBUTZERO,flag=FLAGCHAR,correct=CORRECT,wrong=WRONG;
    cout<<endl<<"   ";
    for(int i=0;i<N;i++){SetColor(9);cout<<i;SetColor(7);if(i<10){cout<<"  ";}else{cout<<" ";}}

    cout<<endl;
    for(int i=0;i<N;i++)
    {

        SetColor(9);cout<<i;SetColor(7);if(i<10){cout<<"  ";}else{cout<<" ";}
        for(int j=0;j<N;j++)
        {
            if(grid[i][j]==-1){SetColor(2);cout<<unclicked<<"  ";SetColor(7);}
            else if (grid[i][j]==0){SetColor(6);cout<<clickzero<<"  ";SetColor(7);}
            else if (grid[i][j]==BOMB){SetColor(12);cout<<bomb<<"  ";SetColor(7);}
            else if (grid[i][j]==FLAG){SetColor(12);cout<<flag<<"  ";SetColor(7);}
            else if (grid[i][j]==CORRECT){SetColor(10);cout<<correct<<"  ";SetColor(7);}
            else if (grid[i][j]==WRONG){SetColor(12);cout<<wrong<<"  ";SetColor(7);}
            else {SetColor(15);cout<<grid[i][j]<<"  ";SetColor(7);}
        }
        cout<<endl;
    }
}
void SetColor(int value)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  value);
}
bool WinCondition(int bombgrid[][20],int grid[][20],int N)
{
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(bombgrid[i][j]==0)
            {
                if(grid[i][j]==-1){return false;}
            }
    return true;
}

void placeBombs(int bombgrid[][20],int Nbomb,int N)
{
    int x,y;
    srand(time(0));
    for(int i=0;i<Nbomb;)
    {
        x=GetRandomNumber(N-1);
        y=GetRandomNumber(N-1);
        if(bombgrid[x][y]==1){continue;}
        else{bombgrid[x][y]=1;i++;}

    }

}

int GetRandomNumber(int n)
{
    return (rand() % (n + 1));
}
