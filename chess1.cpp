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
        return false;
    return true;
}
bool Schachbrett::isW(char piece){
    if(piece<='A'|| piece>='Z')
        return false;
    return true;
}
bool Schachbrett::isEmptySpace(char piece){
    if(piece == ' ') return true;
    if(piece == '#') return true;
    return false;
}
bool Schachspiel::isValid(int sx, int sy, int zx, int zy){
	if(startx < 0 || startx >7 || zielx <0 || zielx >7){
		cout << "ERROR: coordinates out of range." << endl;
	   	return false;
	}
    if(starty < 0 || starty >7 || ziely <0 || ziely >7) return false;
    
	if(isEmptySpace(board[sx][sy])) return false;
	if(isW(board[sx][sy])^player_) return false;
// Use of XOR in parentheses. Statement is true when the color of the piece doesnt match the player
// Notice that this statement can also be false if the piece was empty
// Therefore you have to first make sure that the piece isnt an empty space
	switch(board[sx][sy]){
		case 'b': case 'B':	return checkPawn( sx,  sy,  zx,  zy);
			break;
		case 't': case 'T': return checkNESW( sx,  sy,  zx,  zy);
			break;
		case 'l': case 'L': return checkDiagonal( sx,  sy,  zx,  zy);
			break;
		case 's': case 'S': return checkKnight( sx,  sy,  zx,  zy);
			break;
		case 'd': case 'D':	return(checkDiagonal( sx,  sy,  zx,  zy)||checkNESW( sx,  sy,  zx,  zy));
			break;
		case 'k': case 'K': return checkArea( sx,  sy,  zx,  zy);
			break;
		default: throw(string("ERROR"));
			break;
	}
	return false;
}

void Schachspiel::execTurn(int startx, int starty, int zielx, int ziely){
	if (board[zielx][ziely]== 'K') throw string("Spieler2 hat gewonnen.");
	if (board[zielx][ziely]== 'k') throw string("Spieler1 hat gewonnen.");
	Schachbrett::execTurn(startx, starty, zielx, ziely);
	return;
}
void Schachspiel::run(){
	int sy,zy;
	char sx,zx;	
	while(1){
		do{
			cout << "Eingabe Startkoordinaten:";
			
			cin >> sx >> sy;
			if(cin.fail()){
				cin.clear();
				cout << "FEHLER" << endl;
				cin.ignore(1000,'\n');
				continue;
			}

			cout << "Eingabe Zielkoordinaten:";
			cin >> zx >> zy;
			if(cin.fail()){
				cin.clear();
				cout << "FEHLER" << endl;
				cin.ignore(1000,'\n');
				continue;
			}
			if(!isValid(((int)sx)-61,sy-1,((int)zx)-61,zy-1))
				cout << "ungültiger Zug" << endl;
		}while(!isValid(((int)sx)-61,sy-1,((int)zx)-61,zy-1));
		execTurn(((int)sx)-61,sy-1,((int)zx)-61,zy-1);
	}
	return;
}	
