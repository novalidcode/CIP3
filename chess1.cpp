#include "chess.hpp"
#include <iostream>

Schachbrett::Schachbrett()
{
    board[0][0] = 'T';
    board[1][0] = 'S';
    board[2][0] = 'L';
    board[3][0] = 'D';
    board[4][0] = 'K';
    board[5][0] = 'L';
    board[6][0] = 'S';
    board[7][0] = 'T';

    for(int i = 0; i<8; i++)
    {
        board[i][1] = 'B';
    }
    for(int i = 2; i<=5; i++){
        for(int j =0; j<=7; j++){
            if((j+i)%2)
                board[j][i] = ' ';
            else
                board[j][i] = '#';
        }
    }
    for(int i = 0; i<8; i++)
    {
        board[i][6] = 'b';
    }
    board[0][7] = 't';
    board[1][7] = 's';
    board[2][7] = 'l';
    board[3][7] = 'd';
    board[4][7] = 'k';
    board[5][7] = 'l';
    board[6][7] = 's';
    board[7][7] = 't';

}
void Schachbrett::execTurn(int startx,int starty, int zielx, int ziely){
    if(startx < 0 || startx >7 || zielx <0 || zielx >7) throw string("array out of bounds");
    if(starty < 0 || starty >7 || ziely <0 || ziely >7) throw string("array out of bounds");
    board[zielx][ziely] = board[startx][starty];
    if  ((startx+starty)%2)
        board[startx][starty] = ' ';

        else board[startx][starty] = '#';
    return;
}
bool Schachbrett::isB(char piece){
    if(piece<='a'|| piece>='z')
        return false
    return true;
}
bool Schachbrett::isW(char piece){
    if(piece<='A'|| piece>='Z')
        return false
    return true;
}
bool Schachbrett::isEmptySpace(char piece){
    if(piece == ' ') return true;
    if(piece == '#') return true;
    return false;
}
