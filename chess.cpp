#include "chess.hpp"


void Schachbrett::print(){



  for(int i=7;i>-1; i--){
	cout <<i+1<<"  ";
      for(int j=0;j<8;j++){
	  cout <<board[j][i]<<" ";

      }
      if(i==0)
	cout <<endl<<endl<<"   a b c d e f g h"<<endl;

      cout <<endl;
  }



}
