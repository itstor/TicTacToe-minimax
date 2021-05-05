#include <graphics.h>
#include <iostream>

using namespace std;

void drawBoard(){
    int x = getmaxx();
    int y = getmaxy();

    for (int i = 1; i<3; i++){
        line(x/3*i, 0, x/3*i, getmaxy());
        line(0 ,y/3*i, getmaxx(), y/3*i);
    }
}

void drawX(int x, int y){
    int width = getmaxx()/3;
    int height = getmaxy()/3;

    line(x, y, x+width, y+height);
    line(x+width, y, x, y+height);
}

void drawO(int x, int y){
    int radius = getmaxx()/3;
    int offset = getmaxx()/6;

    circle(x+offset, y+offset, radius/2);
}

bool check3(int a, int b, int c){
    return (a == b && b == c && a > 0 && b > 0 && c > 0);
}

int checkWinner(int arr[3][3]){
    int coutZero = 0;
    for (int i = 0; i<3; i++){
        for (int j = 0; j<3; j++){
            if (arr[i][j] > 0){
                coutZero++;
            }

            //vertical
            if (check3(arr[0][i], arr[1][i], arr[2][i])){
                return arr[0][i];
            }
            //horizontal
            else if (check3(arr[j][0], arr[j][1], arr[j][2])){
                return arr[j][0];
            }
            else if (check3(arr[0][0], arr[1][1], arr[2][2]) || check3(arr[2][0], arr[1][1], arr[0][2])){
                return arr[1][1];
            } else if(coutZero == 9){
                return 3;
            }
        }
    }
}

void drawPlayer(int available[3][3]){
    for (int i=0; i<3; i++){
        for (int j=0; j<3; j++){
            int pointer = available[j][i];
            //cout << pointer;
            if (pointer == 1){
                drawO(getmaxx()/3*i, getmaxy()/3*j);
            } else if (pointer == 2){
                drawX(getmaxx()/3*i, getmaxy()/3*j);
            }
        }
        //cout << endl;
    }
}

int getPosition(int x, int y, int *xpos, int *ypos){
    int width = getmaxx()/3;
    int height = getmaxy()/3;

    for (int i = 1; i<=3; i++){
        for (int j = 1; j<=3; j++){
            if(x<=width*j && y<=height*i){
                *xpos = j;
                *ypos = i;
                return 0;
            }
        }
    }
}


int main(){
    initwindow(300, 300);
    int available[3][3] = {{0,0,0},
                           {0,0,0},
                           {0,0,0}};
    int xPos, yPos;
    int currentPlayer = 1;
    int winner = 0;


    while (true){
        drawBoard();
        drawPlayer(available);
        winner = checkWinner(available);
        if (winner > 0){
            switch(winner){
            case 1: cout << "O Win"; break;
            case 2: cout << "X Win"; break;
            case 3: cout << "Tie"; break;
            }
            break;
        }
        if(ismouseclick(WM_LBUTTONDOWN)){
            getPosition(mousex(), mousey(), &yPos, &xPos);
            if (available[xPos-1][yPos-1] == 0)
                available[xPos-1][yPos-1] = currentPlayer;
            currentPlayer = currentPlayer==1?2:1;
            clearmouseclick(WM_LBUTTONDOWN);
        }
        delay(5);
        cleardevice();
    }

    getch();
}
