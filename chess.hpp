#ifndef CHESS_HPP_INCLUDED
#define CHESS_HPP_INCLUDED

#define PLAYER1 1
#define PLAYER2 0

#include <iostream>
using namespace std;


class Schachbrett{

protected:
    char board[8][8];

public:
    Schachbrett();
// F�llt das 2-dimensionale Feld sodass es dem Ausgangspunkt des Spiels entspricht.


    void print();
// Gibt den aktuellen Zustand des Bretts auf dem Bildschirm aus.
// m�gliches Aussehen :
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
// zu beachten hierbei ist, dass das Feld r�ckw�rts ausgegeben wird.
// Die Nummerierungen sind nicht Teil des Feldes.


    void execTurn(int startx, int starty, int zielx, int ziely);
// �berschreibt das Element in der Zielposition mit dem Inhalt der Startposition
// Das Startfeld wird zur "leeren" Kachel


    bool isW(char piece);
//�berpr�ft ob es sich bei dem char um eine wei�e Figur handelt.


    bool isB(char piece);
//�berpr�ft ob es sich bei dem char um eine schwarze Figur handelt.


    bool isEmptySpace(char piece);
//�berpr�ft ob es sich bei dem char um eine leere Kachel handelt.

};

class Schachspiel : protected Schachbrett{
private:
    bool player_ = PLAYER1;

// Die folgenden Funktionen Testen jeweils ob sich das Zielfeld mithilfe
// der jeweiligen Zugoptionen erreichen l�sst.
// Dabei muss darauf geachtet werden ob m�glicherweise eine Figur im Weg zum Zielfeld steht.

    bool checkDiagonal(int sx, int sy, int zx, int zy);
    bool checkNESW(int sx, int sy, int zx, int zy);
    bool checkArea(int sx, int sy, int zx, int zy);
    bool checkKnight(int sx, int sy, int zx, int zy);
    bool checkPawn(int sx, int sy, int zx, int zy);
	

    bool isValid(int sx, int sy, int zx, int zy);
// Hier wird erst gepr�ft ob board[sx][sy] eine Figur ist und ob sie von dem jeweiligen
// Spieler bewegt werden darf. 
// Trifft das obige zu dann wird je nach Figur die richtige 'check-Methode'
// ausgef�hrt.

	void execTurn(int startx, int starty, int zielx, int ziely) throw(string);
// wirft wenn das Zielfeld ein K�nig ist eine Nachricht welcher Spieler gewonnen hat.

public:
	void run();
// F�hrt das Spiel aus und k�mmert sich um die Benutzereingabe.

};

#endif // CHESS_HPP_INCLUDED
