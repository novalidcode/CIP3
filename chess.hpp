#ifndef CHESS_HPP_INCLUDED
#define CHESS_HPP_INCLUDED

#define PLAYER1 true
//PLAYER1 controlls the white chesspieces
#define PLAYER2 false
//PLAYER2 controlls the black chesspieces

#include <iostream>

using namespace std;

enum chesspiece : short{
	wPawn = 1,
	wRook,
	wKnight,
	wBishop,
	wQueen,
	wKing,

	bPawn,
	bRook,
	bKnight,
	bBishop,
	bQueen,
	bKing,

	wEmpty,
	bEmpty

};
	
class IChess{
public:
	chesspiece getPiece(int x, int y) = 0;
	virtual void print() = 0;
	virtual void checkState() = 0;	
	virtual bool isValid(int sx, int sy, int zx, int zy) = 0;
	virtual void init() = 0;
	virtual void execTurn(int startx, int starty, int zielx, int ziely) = 0;
	virtual string getState() = 0;
	virtual void setState(string state) = 0;
	virtual bool isW(chesspiece a) = 0;
	virtual bool isB(chesspiece a) = 0;
	virtual bool isEmptySpace(chesspiece a) = 0;
};

class ChessSimple : public IChess{

protected:
    chesspiece board[8][8];
	char convert(chesspiece);
public:
    ChessSimple();
// Fuellt das 2-dimensionale Feld sodass es dem Ausgangspunkt des Spiels entspricht.

	void init();

    void print();
// Gibt den aktuellen Zustand des Bretts auf dem Bildschirm aus.
// moegliches Aussehen :
//		Grossbuchstaben -> weiß
//		Kleinbuchstaben -> schwarz
//
//			8  t s l d k l s t
//			7  b b b b b b b b
//			6    #   #   #   #
//			5  #   #   #   #  
//			4    #   #   #   #
//			3  #   #   #   #   
//			2  B B B B B B B B
//			1  T S L D K L S T
//			
//			   a b c d e f g h
//
// zu beachten hierbei ist, dass dass Feld rueckwaerts ausgegeben wird.
// Die Nummerierungen sind nicht Teil des Feldes.


    void execTurn(int startx, int starty, int zielx, int ziely);
// ueberschreibt das Element in der Zielposition mit dem Inhalt der Startposition
// Das Startfeld wird zur "leeren" Kachel

	void checkState();

    bool isValid(int sx, int sy, int zx, int zy);
	
    bool isW(chesspiece p);
//ueberprueft ob es sich bei dem char um eine wei�e Figur handelt.


    bool isB(chesspiece p);
//ueberprueft ob es sich bei dem char um eine schwarze Figur handelt.


    bool isEmptySpace(chesspiece p);
//ueberprueft ob es sich bei dem char um eine leere Kachel handelt.

};

class ChessEngine : public ChessSimple{
protected:
    bool player_ = PLAYER1;

// Die folgenden Funktionen Testen jeweils ob sich das Zielfeld mithilfe
// der jeweiligen Zugoptionen erreichen laesst.
// Dabei muss darauf geachtet werden ob moeglicherweise eine Figur im Weg zum Zielfeld steht.

    bool checkDiagonal(int sx, int sy, int zx, int zy);
    bool checkNESW(int sx, int sy, int zx, int zy);
    bool checkArea(int sx, int sy, int zx, int zy);
    bool checkKnight(int sx, int sy, int zx, int zy);
    bool checkPawn(int sx, int sy, int zx, int zy);
	

public:
    bool isValid(int sx, int sy, int zx, int zy);
// Hier wird erst geprueft ob board[sx][sy] eine Figur ist und ob sie von dem jeweiligen
// Spieler bewegt werden darf. 
// Trifft das obige zu dann wird je nach Figur die richtige 'check-Methode'
// ausgefuehrt.

	void execTurn(int startx, int starty, int zielx, int ziely) throw(string);
// wirft wenn das Zielfeld ein Koenig ist eine Nachricht welcher Spieler gewonnen hat.


};

#endif // CHESS_HPP_INCLUDED
