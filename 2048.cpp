#include<iostream>
#include<windows.h>
#include <time.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;
#define N 4
bool LossCondition(int maingrid[N][N]);
int twopower(int n);
void print2048(int maingrid[N][N],long int playerscore);
void SetColor(int colourno);
void combineElements(int maingrid[N][N],int input,long int &playerscore);
void moveElements(int maingrid[N][N],int input,int &flagchange);
void placeNewNumber(int maingrid[N][N]);
void gotoxy(int x, int y);
int GetRandomNumber(int n);



int main()
{
    srand(time(0));
    int maingrid[N][N]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    long int playerscore=0;
    int input,flagchange;

    placeNewNumber(maingrid);
    placeNewNumber(maingrid);
    print2048(maingrid,playerscore);
    while(!LossCondition(maingrid))
    {
        //cout<<"Next move?(1left 2down 3right 4up):";
        flagchange=0;
        getch();
        if (kbhit())
        {
            char ch = getch();
            if(ch==75){input=1;}
            else if(ch==72){input=4;}
            else if(ch==77){input=3;}
            else if(ch==80){input=2;}

            combineElements(maingrid,input,playerscore);

            moveElements(maingrid,input,flagchange);

            system("cls");

            if(flagchange==1){placeNewNumber(maingrid);}
            print2048(maingrid,playerscore);

        }

    }
    gotoxy(0,17);cout<<"              ";
    gotoxy(0,19);cout<<"You lost! Final Score:"<<playerscore<<endl;
    getch();
    system("pause");


    return 0;
}

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };
  SetConsoleCursorPosition(h,c);
}
bool LossCondition(int maingrid[N][N])
{
    int row,col;
    bool flag1,flag2;

    for(col=0;col<N;col++)
    {
      for(row=0;row<N-1;row++)
      {
          if(maingrid[row][col]==maingrid[row+1][col]){return false;}
      }

    }
    for(row=0;row<N;row++)
    {
      for(col=0;col<N-1;col++)
      {
          if(maingrid[row][col]==maingrid[row][col+1]){return false;}
      }

    }
    for(col=0;col<N;col++)
    {
      for(row=0;row<N;row++)
      {
          if(maingrid[row][col]==0){return false;}
      }

    }
    return true;

}
int twopower(int n)
{
    int p=1;
    for(int i=0;i<n;i++)
    {
        p=2*p;
    }
    return p;
}
void SetColor(int colourno)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  colourno);
}
void print2048(int maingrid[N][N],long int playerscore)
{
     //main grid
    SetColor(15);
   gotoxy(1,0);{for(int i=1;i<28;i++){cout<<"_";}}

   for(int i=0;i<29;i=i+7)
   {
       for(int j=1;j<17;j++)
       {
           gotoxy(i,j);
           cout<<"|";
       }
   }

    for(int j=4;j<17;j=j+4)
    {
           gotoxy(1,j);
           cout<<"______";
           gotoxy(8,j);
           cout<<"______";
           gotoxy(15,j);
           cout<<"______";
           gotoxy(22,j);
           cout<<"______";
    }
   SetColor(7);
   cout<<endl;
    //end main grid
    for(int row=0;row<4;row++)
    {
      for(int col=0;col<4;col++)
      {
          if(maingrid[row][col]==0){continue;}
          else
          {
                switch(maingrid[row][col])
                {
                    case 1:SetColor(6);break;
                    case 2:SetColor(14);break;
                    case 3:SetColor(5);break;
                    case 4:SetColor(13);break;
                    case 5:SetColor(1);break;
                    case 6:SetColor(9);break;
                    case 7:SetColor(2);break;
                    case 8:SetColor(10);break;
                    case 9:SetColor(3);break;
                    case 10:SetColor(11);break;
                    case 11:SetColor(12);break;
                    case 12:SetColor(15);break;
                }
                gotoxy(1+(7*row),1+(4*col));cout<<" ____ ";
                gotoxy(1+(7*row),2+(4*col));cout<<"|";
                if(maingrid[row][col]<4){cout<<" "<<twopower(maingrid[row][col])<<"  |";}
                else if(maingrid[row][col]<7){cout<<" "<<twopower(maingrid[row][col])<<" |";}
                else if(maingrid[row][col]<10){cout<<" "<<twopower(maingrid[row][col])<<"|";}
                else{cout<<twopower(maingrid[row][col])<<"|";}

                gotoxy(1+(7*row),3+(4*col));cout<<"|____|";SetColor(7);

          }
      }
    }
    gotoxy(0,17);
    cout<<"Score:"<<playerscore;
    gotoxy(0,19);cout<<"Play with arrow keys!";

}
void combineElements(int maingrid[N][N],int input,long int &playerscore)
{
    int row,col,savedn=-1,savedncol=-1,savednrow=-1;

    if(input==1)//up
    {
        for(col=0;col<N;col++)
        {
            savedn=-1;savednrow=-1;
            for(row=0;row<N;row++)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[savednrow][col]++;
                    playerscore=playerscore+twopower(maingrid[savednrow][col]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savednrow=-1;

                }
                else
                {
                    savednrow=row;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==3)//down
    {
        for(col=0;col<N;col++)
        {
            savedn=-1;savednrow=-1;
            for(row=N-1;row>=0;row--)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[savednrow][col]++;
                    playerscore=playerscore+twopower(maingrid[savednrow][col]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savednrow=-1;

                }
                else
                {
                    savednrow=row;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==4)//left
    {
        for(row=0;row<N;row++)
        {
            savedn=-1;savedncol=-1;
            for(col=0;col<N;col++)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[row][savedncol]++;
                    playerscore=playerscore+twopower(maingrid[row][savedncol]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savedncol=-1;

                }
                else
                {
                    savedncol=col;
                    savedn=maingrid[row][col];
                }
            }
        }
    }
    else if(input==2)//right
    {
        for(row=0;row<N;row++)
        {
            savedn=-1;savedncol=-1;
            for(col=N-1;col>=0;col--)
            {
                if(maingrid[row][col]==0){continue;}

                else if(maingrid[row][col]==savedn)
                {
                    maingrid[row][savedncol]++;
                    playerscore=playerscore+twopower(maingrid[row][savedncol]);
                    maingrid[row][col]=0;
                    savedn=-1;
                    savedncol=-1;

                }
                else
                {
                    savedncol=col;
                    savedn=maingrid[row][col];
                }
            }
        }
    }


}
void moveElements(int maingrid[N][N],int input,int &flagchange)
{
    int row,col,zerorow,zerocol;

    if(input==1)//UP
    {
        for(col=0;col<N;col++)
        {
            for(row=1;row<N;row++)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerorow=row-1 ; maingrid[zerorow][col]==0 && (zerorow>=0);zerorow--){}
                    zerorow++;
                    if(zerorow==row){continue;}
                    else
                    {
                        maingrid[zerorow][col]=maingrid[row][col];
                        flagchange=1;
                        maingrid[row][col]=0;
                    }
                }
            }
        }
    }

    if(input==3)//DOWN
    {
        for(col=0;col<N;col++)
        {
            for(row=N-2;row>=0;row--)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerorow=row+1 ; maingrid[zerorow][col]==0 && (zerorow<N);zerorow++){}
                    zerorow--;
                    if(zerorow==row){continue;}
                    else
                    {
                        maingrid[zerorow][col]=maingrid[row][col];
                        maingrid[row][col]=0;
                        flagchange=1;
                    }
                }
            }
        }
    }

    if(input==4)//LEFT
    {
        for(row=0;row<N;row++)
        {
            for(col=1;col<N;col++)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerocol=col-1 ; maingrid[row][zerocol]==0 && (zerocol>=0);zerocol--){}
                    zerocol++;
                    if(zerocol==col){continue;}
                    else
                    {
                        maingrid[row][zerocol]=maingrid[row][col];
                        maingrid[row][col]=0;
                        flagchange=1;
                    }
                }
            }
        }
    }

    if(input==2)//right
    {
        for(row=0;row<N;row++)
        {
            for(col=N-2;col>=0;col--)
            {
                if(maingrid[row][col]==0){continue;}
                else
                {
                    for(zerocol=col+1 ; maingrid[row][zerocol]==0 && (zerocol<N);zerocol++){}
                    zerocol--;
                    if(zerocol==col){continue;}
                    else
                    {
                        maingrid[row][zerocol]=maingrid[row][col];
                        maingrid[row][col]=0;
                        flagchange=1;
                    }
                }
            }
        }
    }
}
int GetRandomNumber(int n)
{
    return (rand() % (n+1));
}
void placeNewNumber(int maingrid[N][N])
{
    int row,col,probfactor;
    do{
        row=GetRandomNumber(3);
        col=GetRandomNumber(3);
    }while(maingrid[row][col]!=0);

    probfactor=GetRandomNumber(4);
    if(probfactor==4)
    {
        maingrid[row][col]=2;
    }
    else
    {
        maingrid[row][col]=1;
    }

}

