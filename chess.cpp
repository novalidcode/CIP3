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
bool checkDiagonal(int sx, int sy, int zx, int zy){
  //(1,1) -> (5,5)
  if(abs(sx-zx)==abs(sy-zy)){

  }
  return false;
}
   bool checkNESW(int sx, int sy, int zx, int zy){
     return sx == zx ? true: sy==zy ? true: false ;



   }
   bool checkArea(int sx, int sy, int zx, int zy){
       return (board[zx][zy]!='#' || board[zx][zy]!=' ') ;

   }
   bool checkKnight(int sx, int sy, int zx, int zy){
     int g[] = {2, -2};
     int ge[] = {1, -1};

       for(int i=0; i<2; i++)
	 for(int j=0; j< 2; j++)
	     if ((sy + g[j])==zy && (sx +ge[i])==zx)
		return true;
       for(int i=0; i<2; i++)
       	 for(int j=0; j< 2; j++)
       	     if ((sx + g[j])==zx && (sy +ge[i])==zy)
       		return true;

     return false;
   }
   bool checkPawn(int sx, int sy, int zx, int zy){
     //
     if(sy==6 || sy==1 )
	 ;
     return;
   }


   bool isValid(int sx, int sy, int zx, int zy){
     return;
   }
