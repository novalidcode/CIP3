#include "chess.hpp"
#include <iostream>

void Schachbrett::print(){

  for(int i=0; i< 8; i++)
    for(int j=0; j< 8; j++)
      ((j+i)%2)?board[j][i]=' ':board[j][i]='#';

  for(int i=7;i>-1; i--){
	cout <<i+1<<" ";
      for(int j=7;j>-1;j--){
	  cout <<board[i][j]<<" ";

      }
      if(i==0)
	cout <<"  a b c d e f g"<<endl;
  }



}
