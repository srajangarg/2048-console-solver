#include<iostream>
#include <time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<bits/stdc++.h>


using namespace std;
#define N 4
bool LossCondition(int maingrid[N][N]);
int twopower(int n);
void print2048(int maingrid[N][N],long int playerscore);
void SetColor(int colourno);
void combineElements(int maingrid[N][N],int input,long int &playerscore);
void moveElements(int maingrid[N][N],int input);
void placeNewNumber(int maingrid[N][N]);
void gotoxy(int x, int y);
int GetRandomNumber(int n);
bool gridchange(int initgrid[N][N],int finalgrid[N][N]);//return true if grid has changed
//made for solving
void initGrid(int grid1[N][N],int grid2[N][N]);
long int playGridTillEnd(int maingrid[N][N],long int inscore); //plays a complete random game from current position , and returns score after game end
long int playGridTillEndv2(int maingrid[N][N],long int inscore);
int bestPlay(int maingrid[N][N],long int inscore); //return most favorable direction
int bestPlayv2(int maingrid[N][N],long int inscore);


int main2()
{
    srand(time(0));
    int maingrid[N][N]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int tempgrid[N][N];
    long int playerscore=0;
    int input,flagchange;

    placeNewNumber(maingrid);
    placeNewNumber(maingrid);

    print2048(maingrid,playerscore);

    return 0;
}

int main()
{
    srand(time(0));
    int maingrid[N][N]={{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    int tempgrid[N][N];
    long int playerscore=0;
    int input,flagchange;

    placeNewNumber(maingrid);
    placeNewNumber(maingrid);

    cout << "\033[2J\033[1;1H";
    print2048(maingrid,playerscore);

    while(!LossCondition(maingrid))
    {
        input=bestPlay(maingrid,playerscore);

        // cout<<endl<<input<<endl;
        initGrid(tempgrid,maingrid);

        combineElements(maingrid,input,playerscore);
        moveElements(maingrid,input);

        if(gridchange(tempgrid,maingrid)){placeNewNumber(maingrid);}

        cout << "\033[2J\033[1;1H";
        print2048(maingrid,playerscore);
        // usleep(0.5*1e6);
    }

    // 
    // {
        
    //     // getchar();
    //     // if (kbhit())
    //     // {
    //     //     char ch = getchar();
    //     //     if(ch==75){input=1;}
    //     //     else if(ch==72){input=4;}
    //     //     else if(ch==77){input=3;}
    //     //     else if(ch==80){input=2;}

    //     //     initGrid(tempgrid,maingrid);
    //     //     combineElements(maingrid,input,playerscore);
    //     //     moveElements(maingrid,input);

    //     //     cout << "\033[2J\033[1;1H";

    //     //     if(gridchange(tempgrid,maingrid)){placeNewNumber(maingrid);}
    //     //     print2048(maingrid,playerscore);
    //     //     gotoxy(0,21);
    //     //     switch(bestPlay(maingrid,playerscore))
    //     //     {
    //     //         case 1: cout<<"Best move: Left ";break;
    //     //         case 2: cout<<"Best move: Down ";break;
    //     //         case 3: cout<<"Best move: Right";break;
    //     //         case 4: cout<<"Best move: Up   ";break;
    //     //     }

    //     // }

        
    //     // combineElements(maingrid,input,playerscore);
    //     // moveElements(maingrid,input);

    //     // cout << "\033[2J\033[1;1H";
    //     // placeNewNumber(maingrid);

    //     // print2048(maingrid,playerscore);
    //     // sleep(1);
    // }
    //print2048(maingrid,playerscore);
    // gotoxy(0,17);cout<<"              ";
    // gotoxy(0,19);cout<<"You lost! Final Score:"<<playerscore<<endl;
    // getchar();

    return 0;
}

void gotoxy(int col, int row)
{
  std::cout << "\033[" << row+1<< ";" << col+1 << "H";
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
    // cout<<"\033[" + to_string(colourno)+ ";47m";
    // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  colourno);
}
void print2048(int maingrid[N][N],long int playerscore)
{
    cout << "\033[2J\033[1;1H";
     //main grid
    SetColor(15);
   gotoxy(1,0);{for(int i=1;i<28;i++){cout<<"_";}}

   for(int i=0;i<29;i=i+7)
   {
       for(int j=1;j<17;j++)
       {
           gotoxy(i, j);
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
    gotoxy(0,19);cout<<"Play with arrow keys!"<<endl;

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
void moveElements(int maingrid[N][N],int input)
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
bool gridchange(int initgrid[N][N],int finalgrid[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(initgrid[i][j]!=finalgrid[i][j])
            {
                return true;
            }
        }
    }

    return false;
}
void initGrid(int grid1[N][N],int grid2[N][N])
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            grid1[i][j]=grid2[i][j];
        }
    }

}

long int playGridTillEnd(int maingrid[N][N],long int inscore)
{
    int copygrid[N][N],tempgrid[N][N];
    int movedir,flagchange;
    initGrid(copygrid,maingrid);

    while(!LossCondition(copygrid))
    {
        flagchange=0;
        movedir=GetRandomNumber(3)+1;
        initGrid(tempgrid,copygrid);

        combineElements(copygrid,movedir,inscore);
        moveElements(copygrid,movedir);

        if(gridchange(tempgrid,copygrid)){placeNewNumber(copygrid);}
    }

    return inscore;
}
int bestPlay(int maingrid[N][N],long int inscore)
{
    long int inscoreog=inscore,inscoreafterdir;
    int flagchange,dir=1;
    int copygrid[N][N],tempgrid[N][N];
    long long int totalscore[5]={0};


    for(dir=1;dir<5;dir++)
    {
        inscore=inscoreog;
        initGrid(copygrid,maingrid);
        initGrid(tempgrid,copygrid);

        combineElements(copygrid,dir,inscore);
        moveElements(copygrid,dir);

        if(gridchange(tempgrid,copygrid)){placeNewNumber(copygrid);}
        else{continue;}

        inscoreafterdir=inscore;

        if(LossCondition(copygrid)){continue;}

        for(int i=0;i<200;i++)
        {
            inscore=inscoreafterdir;
            totalscore[dir]=totalscore[dir]+playGridTillEnd(copygrid,inscore);

        }
    }

    long long int bestscore=totalscore[1];
    int bestdir=1;

    for(int i=1; i<5;i++)
    {
        if(totalscore[i]>bestscore)
        {
            bestscore=totalscore[i];
            bestdir=i;
        }
        // cout<<totalscore[i]<<endl;
    }

    return bestdir;

}
//up 4
//left 1
//right 3
//down 2
long int playGridTillEndv2(int maingrid[N][N],long int inscore)
{
    int copygrid[N][N],tempgrid[N][N],temp2grid[N][N];
    int movedir,flagchange;
    initGrid(copygrid,maingrid);
    long int inscoreog=inscore;


    while(!LossCondition(copygrid))
    {


        bool flagup=false,flagleft=false,flagright=false;

        //up change
        initGrid(tempgrid,copygrid);

        combineElements(tempgrid,4,inscore);
        moveElements(tempgrid,4);
        if(gridchange(tempgrid,copygrid)){flagup=true;}

        initGrid(tempgrid,copygrid);
        inscore=inscoreog;

        //left change
        combineElements(tempgrid,1,inscore);
        moveElements(tempgrid,1);
        if(gridchange(tempgrid,copygrid)){flagleft=true;}

        initGrid(tempgrid,copygrid);
        inscore=inscoreog;

        //right change
        combineElements(tempgrid,3,inscore);
        moveElements(tempgrid,3);
        if(gridchange(tempgrid,copygrid)){flagright=true;}


        inscore=inscoreog;

        if(flagup==true && flagleft==true)
        {
            int flag=GetRandomNumber(1);
            if(flag==0)
            {
                movedir=1;
            }
            else{movedir=4;}
        }
         else{
         if(flagup==true)
        {
            movedir=4;
        }
        if(flagleft==true)
        {
            movedir=1;
        }

        if(flagup==false && flagleft==false)
        {
            if(flagright==true)
            {
                movedir=3;
            }
            else
            {
                movedir=2;
            }
        }}
        //movedir=GetRandomNumber(3)+1;

        initGrid(temp2grid,copygrid);

        combineElements(copygrid,movedir,inscore);
        moveElements(copygrid,movedir);

        if(gridchange(temp2grid,copygrid)){placeNewNumber(copygrid);}
    }

    return inscore;
}
int bestPlayv2(int maingrid[N][N],long int inscore)
{

    bool flagup=false,flagleft=false,flagright=false;
    int flag4end=0,flag1end=0;
    long int inscoreafterdir;
    int copygrid[N][N],tempgrid[N][N];
    long int inscoreog=inscore;
    long long int totalscore4,totalscore1;

    initGrid(copygrid,maingrid);
    initGrid(tempgrid,copygrid);

    //up change
    combineElements(tempgrid,4,inscore);
    moveElements(tempgrid,4);
    if(gridchange(tempgrid,maingrid)){flagup=true;}

    initGrid(tempgrid,copygrid);
    inscore=inscoreog;

    //left change
    combineElements(tempgrid,1,inscore);
    moveElements(tempgrid,1);
    if(gridchange(tempgrid,maingrid)){flagleft=true;}

    initGrid(tempgrid,copygrid);
    inscore=inscoreog;

    //right change
    combineElements(tempgrid,3,inscore);
    moveElements(tempgrid,3);
    if(gridchange(tempgrid,maingrid)){flagright=true;}

    initGrid(tempgrid,copygrid);
    inscore=inscoreog;

    if(flagup== true &&flagleft==true)
    {

        combineElements(copygrid,4,inscore);
        moveElements(copygrid,4);

        inscoreafterdir=inscore;

        for(int i=0;i<20000;i++)
        {
            inscore=inscoreafterdir;
            totalscore4=totalscore4 +playGridTillEnd(copygrid,inscore);

        }

        inscore=inscoreog;
        initGrid(copygrid,maingrid);
        initGrid(tempgrid,copygrid);

        combineElements(copygrid,1,inscore);
        moveElements(copygrid,1);

        inscoreafterdir=inscore;

        for(int i=0;i<2000;i++)
        {
            inscore=inscoreafterdir;
            totalscore1=totalscore1 +playGridTillEnd(copygrid,inscore);

        }

        if(totalscore1>totalscore4)
        {
            return 1;
        }
        else
        {
            return 4;
        }

    }
    if(flagup==true)
    {
        return 4;
    }
    if(flagleft==true)
    {
        return 1;
    }

    if(flagup==false &&flagleft==false)
    {
        if(flagright==true)
        {
            return 3;
        }
        else
        {
            return 2;
        }
    }

}
