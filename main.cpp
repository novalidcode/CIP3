#include <iostream>
#include "chess.hpp"



using namespace std;

void testgame(int *ab, IChess * a, int turns);
void rungame(IChess *a);
int main()
{
    ChessSpecial a;

    int test[] =
    {
        1,1,1,2,
        5,6,5,4,
        4,1,4,3,
        5,4,4,3,
        5,1,5,3,		// move 2
        4,3,5,2,		//en passant
        0,1,0,3,
        5,2,6,1,
        0,3,0,4,
        1,6,1,4,
        0,4,1,5,		//en passant
        6,1,7,0,			//Change Pawn

        1,0,2,2,
        2,6,1,5,
        2,0,0,2,
        1,5,1,4,
        3,0,4,1,
        1,4,1,3,
        4,0,2,0		//rochade test

    }; // 12 turns ;En passant

    int test2[] =
    {
        1,1,1,2,
        5,6,5,4,
        4,1,4,3,
        5,4,4,3,
        5,1,5,3,
        4,3,5,2
    };// 6 turns ; Rochade

    int test3[] =
       {
           3,1,3,3,
		   3,6,3,4,
		   2,0,4,2,
		   2,7,5,4,
		   5,1,5,2,
		   5,4,2,1,
		   3,0,2,1,
		   4,6,4,5,
		   1,0,3,1,
		   6,6,6,5,
		   4,0,2,0,
		   5,7,7,5,
		   5,2,7,5,
		   4,2,7,5,
		   6,7,5,5,
		   6,1,6,3,
		   4,7,6,7,
		   1,7,2,5,
		   7,5,6,4,
		   4,0,3,0,
		   3,1,4,3,
		   4,7,6,7//
       };
    //rungame(&a);
    testgame(test3, &a, 22);

    return 0;
}


void rungame(IChess *a){
	while(true){
		a->print();
		int g[4]={0,0,0,0};
		cin >>g[0]>>g[1]>>g[2]>>g[3];
		a->execTurn(g[0],g[1],g[2],g[3]);
		//a->print();
	}


}

void testgame(int *ab, IChess * a, int turns)
{

    for(int i=0; i<turns*4; i=i+4)
    {
        cout <<i/4<<". Zug: "<<ab[i]<<" "<<ab[i+1]<<" "<<ab[i+2]<<" "<<ab[i+3]<< endl;
        a->execTurn(ab[i],ab[i+1],ab[i+2],ab[i+3]);
        a->print();
    }

    return;
}
