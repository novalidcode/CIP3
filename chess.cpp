#include "chess.hpp"

/*
 * 	Schachspiel::checkArea almost finished
 * 		castling & attackedField
 *
 * 	Schachspiel::checkPawn almost finished
 * 		en passant
 * 		upgradePawn => Queen, Roook, Knight or Bishop when reached other side
 *
 *	Schachspiel::isValid not implemented here
 *
 * 	methode needed bool checkProtectKing(int sx, int sy){ } //Checks if the King is protected by a Figure, needs to be checked for all
 * 	maybe just put it just inside the isvalid methode?
 *
 *
 * 	English			German
 * 	-------------------------------------
 * 	Chess			Schach
 * 	check			Schach
 * 	check mate		Schachmatt
 *
 * 	Special moves
 *
 * 	castling		Rochade		https://en.wikipedia.org/wiki/castling
 *	En passant		en passant	https://en.wikipedia.org/wiki/En_passant
 *
 * 	Chessboard		Schachbrett
 * 	Pawn			Bauer
 * 	Rook			Turm
 * 	Knight			Springer
 * 	Bishop			Läufer
 * 	Queen			Königin
 * 	King			König
 *
 */



//Finished
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

};

//Finished
bool Schachspiel::checkDiagonal(int sx, int sy, int zx, int zy){
//First check start and end position color, if true then return false, this add as methode? //Catches also if the same place is tried to use (1,1) (1,1) => false
//Check is there a Figure to move // check same color
	if(isEmptySpace(board[sx][sy]) || (isW(board[sx][sy])&&isW(board[zx][zy])) || (isB(board[sx][sy])&&isB(board[zx][zy]))) 
              return false;


//Check if diagonal
//UPDATE: added a previously missing return statement in line 76 
	if(abs(sx-zx)==abs(sy-zy)){
	//Check if something betweeen
		int g= sx<zx ? 1: -1;
		int ge = sy<zy ? 1: -1;
		//-1 because of the first check and +1 because not the same field
		for(int i=1; i<abs(sx-zx)-1; i++)	
			if(!isEmptySpace(board[sx+(g*i)][sy+(ge*i)]))
				return false;
		return true;
	}
	return false;
};
// Finished
   bool Schachspiel::checkNESW(int sx, int sy, int zx, int zy){
//First check start and end position color, if true then return false, this add as methode?
//Catches also if the same place is tried to use (1,1) (1,1) => false
          if(isEmptySpace(board[sx][sy]) || (isW(board[sx][sy])&&isW(board[zx][zy])) || (isB(board[sx][sy])&&isB(board[zx][zy]))) //Check is there a Figure to move // check same color
            return false;


          int g=1;	//pos. or neg. way
          if(sx == zx){
              g= sy<zy? 1:-1;
              //check emptyness
              for(int i=1; i<abs(sy-zy)-1; i++)		//-1 because of the first check and +1 because not the same field
        	if(!isEmptySpace(board[sx][sy+(g*i)]))
        	  return false;
              return true;
            }
          else if(sy==zy){
              g= sx<zx? 1:-1;
              //check emptyness
	      for(int i=1; i<abs(sx-zx)-1; i++)		//-1 because of the first check and +1 because not the same field
		  if(!isEmptySpace(board[sx+(g*i)][sy]))
		    return false;
	      return true;
          }
          else{
              return false;
          }





   };

   //Not finished yet
   bool Schachspiel::checkArea(int sx, int sy, int zx, int zy){
     //First check start and end position color, if true then return false, this add as methode? //Catches also if the same place is tried to use (1,1) (1,1) => false
     if(isEmptySpace(board[sx][sy]) || (isW(board[sx][sy])&&isW(board[zx][zy])) || (isB(board[sx][sy])&&isB(board[zx][zy]))) //Check is there a Figure to move // check same color
       return false;
     //King issue that he can't move on a protected/attacked field // maybe write a methode to figure it out if there is a protection / attack,
     //Could also be used for the rouchade

     //Still Missing
       //bool checkPosAttacked?(zx,zy){ knight?, Pawn near?  Rook? Bishop? (Queen)? } //King && King 1 empty Field betweeen
       //castling methode? member Array bool moved_[6] of 6 bool values for , R K R, R K R

     if (sy == zy){
	if(sx-1==zx || sx+1==zx){
	    return true;
	}
	else{
	    return false;
	}
     }
     else if (sy+1 == zy){
	if(sx-1==zx || sx==zx ||sx+1==zx ){
	   return true;
	}
	else{
	   return false;
	}
     }
     else if (sy-1 == zy){
	if(sx-1==zx || sx==zx ||sx+1==zx ){
	    return true;
	}
	else{
	   return false;
	}
     }
     else{
	 return false;
     }

   };

   //Finished
   bool Schachspiel::checkKnight(int sx, int sy, int zx, int zy){
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
   };
   //almost finished
   bool Schachspiel::checkPawn(int sx, int sy, int zx, int zy){
     //First check start and end position color, if true then return false, this add as methode?

     //en passant a bit complicated perhaps

     if(isEmptySpace(board[sx][sy]) || (isW(board[sx][sy])&&isW(board[zx][zy])) || (isB(board[sx][sy])&&isB(board[zx][zy]))) //Check is there a Figure to move // check same color
       return false;

     bool notmoved=(sy==6 || sy==1 );		//Pawn at Startpoint

     //Find direction
     int ge = isW(board[sx][sy])? abs(sy-zy) :-abs(sy-zy);

     if(abs(ge)>2 || (abs(ge)>1 && sx!=zx) )
       return false; //Out of Range | wrong move sidewards

     //Vertical move
     if(sx == zx){
	 //check Emptyness
	 for(int i=0; i<abs(ge); i++){
	    if(!isEmptySpace(board[sx][sy+((i+1)*(ge/ge))]))
	      return false;
	 }
	 return true;
     }

     if(sx!=zx){ //Check if hit other color --- --- en passant special implement later, need to know the last move of the other player
	 if(!isEmptySpace(board[zx][zy]))
	   return true;
	 //else if(enpassant)
	 else{
	     return false;
	 }
     }

     return true;
   };



