/*
 * chess.hpp
 *
 *  Created on: 09.11.2022
 *      Author: ANT
 */

/**
 *
 * \file chess.hpp
 *
 * \brief Contains Interface IChess & Abstract Class: ChessSimple ChessEngine & Class: ChessSpecial
 * of check sum calculation.
 *
 */
#ifndef CHESS_HPP_INCLUDED
#define CHESS_HPP_INCLUDED


#define PLAYER1 true
//PLAYER1 controlls the white chesspieces
#define PLAYER2 false
//PLAYER2 controlls the black chesspieces

#include <iostream>
#include <string>

using namespace std;


enum chesspiece : short
{
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

///
///
///\class IChess
///
/// \brief Interface class for ChessSimple ChessEngine ChessSpecial.
///
///

class IChess
{
public:
	
///
///
///\brief get Piece of the board
///
///\param x int pos x of the board
///
///\param y int pos y of the board
///
///\return chesspiece
///
///
    virtual chesspiece getPiece(int x, int y) = 0;
	
///
///\brief output the board
///
///
    virtual void print() = 0;
	
///
///
///\brief checkState of the board
///
///
    virtual void checkState() = 0;
	
///
///
/// \brief is the turn valid
///
/// \param sx int XPos of the Figure
///
/// \param sy int YPos of the Figure
///
/// \param zx int XPos of move Pos
///
/// \param zy int YPos of move Pos
///
/// \return true when the move is valid
///
    virtual bool isValid(int sx, int sy, int zx, int zy) = 0;
///
///
/// \brief initialize the board
///
////
    virtual void init() = 0;
///
///
/// \brief execute the Turn of the player
///
/// \param sx int XPos of the Figure
///
/// \param sy int YPos of the Figure
///
/// \param zx int XPos of move Pos
///
/// \param zy int YPos of move Pos
///
///
///
    virtual void execTurn(int sx, int sy, int zx, int zy) = 0;
///
///
/// \brief return the board or the turn as string
///
///
/// \return string
///
///
///
    virtual string getState() = 0;
///
/// \brief check if chesspiece is white
///
/// \param a chesspiece
///
/// \return true if piece is white, false otherwise
////
    virtual bool isW(chesspiece a) = 0;
///
///
/// \brief check if the figure is  black
///
/// \param a chesspiece
///
/// \return true when it's a black figure
///
///
    virtual bool isB(chesspiece a) = 0;
///
///
/// \brief check if the chesspiece is Empty
///
/// \param a chesspiece
///
/// \return true when it's empty
///
///
    virtual bool isEmptySpace(chesspiece a) = 0;
};


///
///
///\class ChessSimple
///
/// \brief Abstract Class Simple inherit IChess
///
///

class ChessSimple : public IChess
{

protected:
    chesspiece board[8][8];
///
///
///\brief convert chesspiece to char
///
///\param a chesspiece
///
///\return char coverted chesspiece
///
///
    char convert(chesspiece a);

public:
	
    chesspiece getPiece(int x, int y);
    /**
	 *
	 * \brief constructor
	 *
	 */
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


    void execTurn(int sx, int sy, int zx, int zy);
// ueberschreibt das Element in der zposition mit dem Inhalt der sposition
// Das sfeld wird zur "leeren" Kachel

    void checkState();

    bool isValid(int sx, int sy, int zx, int zy);

    bool isW(chesspiece p);
//ueberprueft ob es sich bei dem char um eine wei�e Figur handelt.


    bool isB(chesspiece p);
//ueberprueft ob es sich bei dem char um eine schwarze Figur handelt.


    bool isEmptySpace(chesspiece p);
//ueberprueft ob es sich bei dem char um eine leere Kachel handelt.

};

///
///
///\class ChessEngine
///
/// \brief Abstract Class ChessEngine inherit ChessSimple
///
///
class ChessEngine : public ChessSimple
{
protected:

	bool player_ = PLAYER1;
// Die folgenden Funktionen Testen jeweils ob sich das zfeld mithilfe
// der jeweiligen Zugoptionen erreichen laesst.
// Dabei muss darauf geachtet werden ob moeglicherweise eine Figur im Weg zum zfeld steht.
///
/// \brief check method for bishop
/// \param sx int X-Pos figure
///
/// \param sy int Y-Pos figure
///
/// \param zx int X-Pos move to
///
/// \param zy int Y-Pos move to
/// \return true if destination can be reached with diagonal movement
    virtual bool checkDiagonal(int sx, int sy, int zx, int zy);
    virtual bool checkNESW(int sx, int sy, int zx, int zy);
    virtual bool checkArea(int sx, int sy, int zx, int zy);
    virtual bool checkKnight(int sx, int sy, int zx, int zy);
    virtual bool checkPawn(int sx, int sy, int zx, int zy);



public:
    ChessEngine() : ChessSimple(){};
	void init();
    bool isValid(int sx, int sy, int zx, int zy);
// Hier wird erst geprueft ob board[sx][sy] eine Figur ist und ob sie von dem jeweiligen
// Spieler bewegt werden darf.
// Trifft das obige zu dann wird je nach Figur die richtige 'check-Methode'
// ausgefuehrt.

    void execTurn(int sx, int sy, int zx, int zy) ;
// wirft wenn das zfeld ein Koenig ist eine Nachricht welcher Spieler gewonnen hat.


};

/**
 *
 * \class ChessSpecial
 *
 *	\brief Abstract Class ChessSpecial inherit ChessEngine
 *
 */
class ChessSpecial : public ChessEngine
{
protected:
    bool bCC_[6];	//CastlingCheck 0 2 3 5 => Rook
    //string sState_; //to be determined if used
    int enpassant_;
    //pos and color which should get checked
    //check if the Field is attacked
    /**
	 *
	 * \brief check if the Field is attacked
	 *
	 * \param fx int X-Pos attacked field
	 *
	 * \param fy int Y-Pos attacked field
	 *
	 * \param color bool which player attack field ( 0 / 1)
	 *
	 * \return bool true when it's under attack false when not
	 *
	 */
    bool isFieldAttacked(int fx, int fy, bool color);
    /**
	 *
	 * \brief check Area of the King
	 *
	 * \param sx int X-Pos figure
	 *
	 * \param sy int Y-Pos figure
	 *
	 * \param zx int X-Pos move to
	 *
	 * \param zy int Y-Pos move to
	 *
	 * \return bool true when it's valid false when not
	 *
	 */
    bool checkArea(int sx, int sy, int zx, int zy);
    /**
	 *
	 * \brief Promotion: Pawn at the enemie line?
	 *
	 * \param y int
	 *
	 * \param color bool the player
	 *
	 * \return bool true when pawn at enemie line
	 *
	 */
    bool checkPromotion( int y, bool color);
    /**
	 *
	 * \brief Promotion: Pawn promot to Queen, Rook, Knight or Bishop
	 *
	 * \param x int Figure Pos
	 *
	 * \param y int Figure Pos
	 *
	 * \param color bool the player
	 *
	 * \return bool true when right choose of Promotion
	 *
	 */
    bool Promotion(int x, int y, bool color);
    /**
   	 *
   	 * \brief check move of the Pawn
   	 *
   	 * \param sx int X-Pos figure
   	 *
   	 * \param sy int Y-Pos figure
   	 *
   	 * \param zx int X-Pos move to
   	 *
   	 * \param zy int Y-Pos move to
   	 *
   	 * \return bool true when it's valid false when not
   	 *
   	 */
    bool checkPawn(int sx, int sy, int zx, int zy);
public:
    /**
   	 *
   	 * \brief constructor
   	 *
   	 */
    ChessSpecial() : ChessEngine()
    {
        init();
        enpassant_ =0;
    };
    string getState();
    void init()
    {
		ChessEngine::init();
        for(int i=0; i<6; i++)
            bCC_[i]=true;
        enpassant_=0;
    };
    chesspiece getPiece(int x, int y)
    {
        return board[x][y];
    };
    bool isValid(int sx, int sy,int zx, int zy);





};




#endif // CHESS_HPP_INCLUDED




