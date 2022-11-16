#include "chess.hpp"
#include <iostream>

void ChessSimple::init(){

    board[0][0] = wRook;
    board[1][0] = wKnight;
    board[2][0] = wBishop;
    board[3][0] = wQueen;
    board[4][0] = wKing;
    board[5][0] = wBishop;
    board[6][0] = wKnight;
	board[7][0] = wRook;

    for(int i = 0; i<8; i++)
    {
        board[i][1] = wPawn;
    }

    for(int i = 2; i<=5; i++){
        for(int j =0; j<=7; j++){
            if((j+i)%2)
                board[j][i] = wEmpty;
            else
                board[j][i] = bEmpty;
        }
    }

    for(int i = 0; i<8; i++)
    {
        board[i][6] = bPawn;
    }

    board[0][7] = bRook;
    board[1][7] = bKnight;
    board[2][7] = bBishop;
    board[3][7] = bQueen;
    board[4][7] = bKing;
    board[5][7] = bBishop;
    board[6][7] = bKnight;
	board[7][7] = bRook;

	return;
}

chesspiece ChessSimple::getPiece(int x, int y){
	return board[x][y];
}

char ChessSimple::convert(chesspiece p){
	switch(p){
		case wPawn: return 'B';
		case wRook: return 'T';
		case wKnight: return 'S';
		case wBishop: return 'L';
		case wQueen: return 'D';
		case wKing: return 'K';

		case bPawn: return 'b';
		case bRook: return 't';
		case bKnight: return 's';
		case bBishop: return 'l';
		case bQueen: return 'd';
		case bKing: return 'k';

		case wEmpty: return ' ';
		case bEmpty: return '#';
		default: throw string("can't convert");
	}
	return '\0';
}

ChessSimple::ChessSimple()
{
	init();
}
void ChessSimple::execTurn(int sx,int sy, int zx, int zy){
  	if(isValid(sx,sy,zx,zy)){
		board[zx][zy] = board[sx][sy];
		if  ((sx+sy)%2)
			board[sx][sy] = wEmpty;
		else
			board[sx][sy] = bEmpty;
	}else{

		cout << "invalid move" << endl;
	}
	//checkState(); // to be decided if this should be in this function
    return;
}
void ChessSimple::checkState(){
	for(chesspiece c = wPawn; c<=bKing; c++){
		int counter = 0;
		for(int i=0; i<8; i++){
			for(int k=0; k<8; k++){
				if(!isW(board[i][k]) && !isB(board[i][k]) && !isEmptySpace(board[i][k]))
					throw string("#FATAL ERROR# undefined board contents");
				counter += board[i][k] == c;
				
			}
		}
		if((c==wPawn)||(c==bPawn)){
			if(counter > 8)
				throw string("#FATAL ERROR# too many instances of a chesspiece");
		}else if((c==wQueen)||(c==bQueen)||(c==wKing)||(c==bKing)){
			if(counter > 1)
				throw string("#FATAL ERROR# too many instances of a chesspiece");
		}else{
			if(counter > 2)
				throw string("#FATAL ERROR# too many instances of a chesspiece");
		}
		if((c == wKing)||(c==bKing))
			if(counter < 1)  
				throw string("#FATAL ERROR# crucial chesspiece missing");
	}
	return;
}
				
bool ChessSimple::isValid(int sx, int sy, int zx, int zy){
    if(sx < 0 || sx >7 || zx <0 || zx >7) return false;
    if(sy < 0 || sy >7 || zy <0 || zy >7) return false;
	return true;
}

bool ChessSimple::isB(chesspiece a){
	if((a<bPawn)||(a>bKing))
		return false;
	return true;
}

bool ChessSimple::isW(chesspiece a){
    if((a<wPawn)||(a>wKing))
        return false;
    return true;
}

bool ChessSimple::isEmptySpace(chesspiece a){
    if(a == wEmpty) return true;
    if(a == bEmpty) return true;
    return false;
}

bool ChessEngine::isValid(int sx, int sy, int zx, int zy){
    if(ChessSimple::isValid(sx,sy,zx,zy)){
		if(isEmptySpace(board[sx][sy])) return false;

		if(player_){
			if(player_ != isW(board[sx][sy])){
				return false;
			}
		}
		else{
			if(player_ == isB(board[sx][sy]) )
				return false;
		}

	// Use of XOR in parentheses. Statement is true when the color of the chesspiece doesnt match the player
	// Notice that this statement can also be false if the chesspiece was empty
	// Therefore you have to first make sure that the chesspiece isnt an empty space

		if(isW(board[zx][zy])!= player_ || isB(board[zx][zy]) == player_){

			switch(board[sx][sy]){
				case wPawn: case bPawn:	return checkPawn( sx,  sy,  zx,  zy);
					break;
				case wRook: case bRook: return checkNESW( sx,  sy,  zx,  zy);
					break;
				case wBishop: case bBishop: return checkDiagonal( sx,  sy,  zx,  zy);
					break;
				case wKnight: case bKnight: return checkKnight( sx,  sy,  zx,  zy);
					break;
				case wQueen: case bQueen:	return(checkDiagonal( sx,  sy,  zx,  zy)||checkNESW( sx,  sy,  zx,  zy));
					break;
				case wKing: case bKing: return checkArea( sx,  sy,  zx,  zy);
					break;
				default: throw(string("ERROR"));
					break;
			}

		}
	}
	return false;
}

void ChessEngine::execTurn(int sx, int sy, int zx, int zy){
	if (board[zx][zy]== wKing) throw string("Spieler2 hat gewonnen.");
	if (board[zx][zy]== wKing) throw string("Spieler1 hat gewonnen.");
	ChessSimple::execTurn(sx, sy, zx, zy);
	return;
}
//void ChessEngine::run(){
//	int sy,zy;
//	char sx,zx;	
//	while(1){
//		do{
//			cout << "Eingabe Startkoordinaten:";
//			
//			cin >> sx >> sy;
//			if(cin.fail()){
//				cin.clear();
//				cout << "FEHLER" << endl;
//				cin.ignore(1000,'\n');
//				continue;
//			}
//
//			cout << "Eingabe Zielkoordinaten:";
//			cin >> zx >> zy;
//			if(cin.fail()){
//				cin.clear();
//				cout << "FEHLER" << endl;
//				cin.ignore(1000,'\n');
//				continue;
//			}
//			if(!isValid(((int)sx)-61,sy-1,((int)zx)-61,zy-1))
//				cout << "ungültiger Zug" << endl;
//		}while(!isValid(((int)sx)-61,sy-1,((int)zx)-61,zy-1));
//		execTurn(((int)sx)-61,sy-1,((int)zx)-61,zy-1);
//	}
//	return;
//}	
//test
