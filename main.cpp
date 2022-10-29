#include <iostream>
#include "chess.hpp"

using namespace std;

int main(){
	Schachbrett a;

	a.print();
	a.execTurn(1,1,4,4);
	a.print();
	a.execTurn(4,7,4,5);
	a.print();
    a.execTurn(1,2,7,7);
	a.print();
	return 0;
}
