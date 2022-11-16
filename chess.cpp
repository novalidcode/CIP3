#include "chess.hpp"

/*
 * 	ChessEngine::checkArea almost finished
 * 		castling & attackedField
 *
 * 	ChessEngine::checkPawn almost finished
 * 		en passant
 * 		upgradePawn => Queen, Roook, Knight or Bishop when reached other side
 *
 *	ChessEngine::isValid not implemented here
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
 *	Promotion		Umwandlung
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
void ChessSimple::print()
{

    for (int i = 7; i > -1; i--)
    {
        cout << i + 1 << "  ";
        for (int j = 0; j < 8; j++)
        {
            cout << convert(board[j][i]) << " ";

        }
        if (i == 0)
            cout << endl << endl << "   a b c d e f g h" << endl;

        cout << endl;
    }

}
;

//Finished
bool ChessEngine::checkDiagonal(int sx, int sy, int zx, int zy)
{

//Check if diagonal
//UPDATE: added a previously missing return statement in line 76
    if (abs(sx - zx) == abs(sy - zy))
    {
        //Check if something betweeen
        int g = sx < zx ? 1 : -1;
        int ge = sy < zy ? 1 : -1;
        //-1 because of the first check and +1 because not the same field
        for (int i = 1; i < abs(sx - zx) - 1; i++)
            if (!isEmptySpace(board[sx + (g * i)][sy + (ge * i)]))
                return false;
        return true;
    }
    return false;
}
;
// Finished
bool ChessEngine::checkNESW(int sx, int sy, int zx, int zy)
{

    int g = 1;	//pos. or neg. way
    if (sx == zx)
    {
        g = sy < zy ? 1 : -1;
        //check emptyness
        for (int i = 1; i < abs(sy - zy) - 1; i++)//-1 because of the first check and +1 because not the same field
            if (!isEmptySpace(board[sx][sy + (g * i)]))
                return false;
        return true;
    }
    else if (sy == zy)
    {
        g = sx < zx ? 1 : -1;
        //check emptyness
        for (int i = 1; i < abs(sx - zx) - 1; i++)//-1 because of the first check and +1 because not the same field
            if (!isEmptySpace(board[sx + (g * i)][sy]))
                return false;
        return true;
    }
    else
    {
        return false;
    }

}
;

//Not finished yet
bool ChessEngine::checkArea(int sx, int sy, int zx, int zy)
{


    //King issue that he can't move on a protected/attacked field // maybe write a methode to figure it out if there is a protection / attack,
    //Could also be used for the rouchade

    //Still Missing
    //bool checkPosAttacked?(zx,zy){ knight?, Pawn near?  Rook? Bishop? (Queen)? } //King && King 1 empty Field betweeen
    //castling methode? member Array bool moved_[6] of 6 bool values for , R K R, R K R

    return true;

}
;

//Finished
bool ChessEngine::checkKnight(int sx, int sy, int zx, int zy)
{
    int g[] = { 2, -2 };
    int ge[] = { 1, -1 };

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if ((sy + g[j]) == zy && (sx + ge[i]) == zx)
                return true;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if ((sx + g[j]) == zx && (sy + ge[i]) == zy)
                return true;

    return false;
}



bool ChessEngine::checkPawn(int sx, int sy, int zx, int zy)
{

    //en passant a bit complicated perhaps
	/*
    bool playerW = isW(board[sx][sy]);
	bool playerB = isB(board[sx][sy]);
    bool notmoved = ((playerW && sy == 1) || (playerB && sy == 6));
    int distance = zy - sy;
			
    int direction = 1;
    playerW ? direction = 1 : direction = -1;
    //playerW? direction *=1 : direction *=-1;

    //Check move
    //cout <<distance<<endl<<direction<<endl<<notmoved<<endl;
    if (sx == zx)
    {
        //Straight move forward
        if ((distance * direction) == 1
                || (notmoved && (distance * direction) == 2))
        {

            for (int i = 1; i <= (distance * direction); i++)
            {
                if (!isEmptySpace(board[sx][sy + (i * direction)]))
                {
                    return false;
                }

            }

            if(checkPromotion( zy, playerW))
            {
                if(Promotion(sx, sy, playerW))
                {
                    enpassant_ = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            }

            if(abs(distance) == 2)
            {

                enpassant_ = zx+zy*8;
                //cout <<"Enpassant "<< enpassant_<<endl;

            }
            else
            {
                enpassant_ = 0;
            }
            //Check here if you can Change the Figure to a
            //Queen,Rook, Knight, Bishop

            return true;	//Move forward succed
        }
    }
    else
    {
        //Hit or en passant?
        if ((distance * direction) == 1)
        {
            if (abs(sx - zx) == 1)
            {
                if (!isEmptySpace(board[zx][zy]))
                {
                    if (playerW != isW(board[zx][zy]))
                    {

                        if(checkPromotion( zy, playerW))
                        {
                            if(Promotion(sx, sy, playerW))
                            {

                                return true;
                            }
                            else
                            {
                                return false;
                            }
                        }

                        return true;
                    }
                }
                else if (enpassant_>0)
                {
                    //en passant

                    if(enpassant_ == zx+(zy-(1*direction))*8)
                    {


                        if  ((zx+zy-(1*direction))%2)
                            board[zx][zy-(1*direction)] = wEmpty;
                        else
                            board[zx][zy-(1*direction)] = bEmpty;

                        enpassant_ = 0;
                        return true;

                    }

                }
            }
        }

    }
    return false;*/
	return true;
};

bool ChessSpecial::isFieldAttacked(int fx, int fy, bool color)
{

    //Variable W or B
    short eCP = 0;
    color ? eCP = 0 : eCP = 6;

    bool checkDirection[4];

    //Check all Diagonal possibilities
    //Pawn,
    //
    if (color)
    {
        if (fy + 1 <= 7)
        {
            if (fx + 1 <= 7)
            {
                if (board[fx + 1][fy + 1] == (wPawn + eCP))
                {
                    return true;
                }
            }
            if (fx - 1 >= 0)
            {
                if (board[fx - 1][fy + 1] == (wPawn + eCP))
                {
                    return true;
                }
            }
        }
    }
    else
    {
        if (fy - 1 >= 0)
        {
            if (fx + 1 <= 7)
            {
                if (board[fx + 1][fy - 1] == (wPawn + eCP))
                {
                    return true;
                }
            }
            if (fx - 1 >= 0)
            {
                if (board[fx - 1][fy - 1] == (wPawn + eCP))
                {
                    return true;
                }
            }
        }

    }

    //Bishop, Queen
    checkDirection[0] = true;
    checkDirection[1] = true;
    checkDirection[2] = true;
    checkDirection[3] = true;
    for (int i = 0; i < 7; i++)
    {

        if (checkDirection[0] && (fx + i) <= 7 && (fy + i) <= 7)
        {
            if (!isEmptySpace(board[fx + i][fy + i]))
            {
                if (board[fx + i][fy + i] == (wQueen + eCP)
                        || board[fx + i][fy + i] == (wBishop + eCP))
                {
                    return true;
                }
                checkDirection[0] = false;	//Something in the way
            }
        }

        if (checkDirection[1] && (fx + i) <= 7 && (fy - i) >= 0)
        {
            if (!isEmptySpace(board[fx + i][fy - i]))
            {
                if (board[fx + i][fy - i] == (wQueen + eCP)
                        || board[fx + i][fy - i] == (wBishop + eCP))
                {
                    return true;
                }
                checkDirection[1] = false;	//Something in the way
            }
        }

        if (checkDirection[2] && (fx - i) >= 0 && (fy + i) <= 7)
        {
            if (!isEmptySpace(board[fx - i][fy + i]))
            {
                if (board[fx - i][fy + i] == (wQueen + eCP)
                        || board[fx - i][fy + i] == (wBishop + eCP))
                {
                    return true;
                }
                checkDirection[2] = false;	//Something in the way
            }
        }

        if (checkDirection[3] && (fx - i) >= 0 && (fy - i) >= 0)
        {
            if (!isEmptySpace(board[fx - i][fy - i]))
            {
                if (board[fx - i][fy - i] == (wQueen + eCP)
                        || board[fx - i][fy - i] == (wBishop + eCP))
                {
                    return true;
                }
                checkDirection[3] = false;	//Something in the way
            }
        }
    }

    //Check all NESW possibilities
    //Rook, Queen
    checkDirection[0] = true;
    checkDirection[1] = true;
    checkDirection[2] = true;
    checkDirection[3] = true;

    for (int i = 0; i < 7; i++)
    {

        if (checkDirection[0] && (fx + i) <= 7)
        {
            if (!isEmptySpace(board[fx + i][fy]))
            {
                if (board[fx + i][fy] == (wQueen + eCP)
                        || board[fx + i][fy] == (wRook + eCP))
                {
                    return true;
                }
                checkDirection[0] = false;	//Something in the way
            }
        }

        if (checkDirection[1] && (fx - i) >= 0)
        {
            if (!isEmptySpace(board[fx - i][fy]))
            {
                if (board[fx - i][fy] == (wQueen + eCP)
                        || board[fx - i][fy] == (wRook + eCP))
                {
                    return true;
                }
                checkDirection[1] = false;	//Something in the way
            }
        }

        if (checkDirection[2] && (fy + i) <= 7)
        {
            if (!isEmptySpace(board[fx][fy + i]))
            {
                if (board[fx][fy + i] == (wQueen + eCP)
                        || board[fx][fy + i] == (wRook + eCP))
                {
                    return true;
                }
                checkDirection[2] = false;	//Something in the way
            }
        }

        if (checkDirection[3] && (fy - i) >= 0)
        {
            if (!isEmptySpace(board[fx][fy - i]))
            {
                if (board[fx][fy - i] == (wQueen + eCP)
                        || board[fx][fy - i] == (wRook + eCP))
                {
                    return true;
                }
                checkDirection[3] = false;	//Something in the way
            }
        }
    }

    //Check Knight
    int g[] = { 2, -2 };
    int ge[] = { 1, -1 };

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            //Check out of Range
            if ((fy + g[j]) < 7 && (fy + g[j]) < 0 && (fx + ge[i]) < 7 && (fx + ge[i]) < 0)
            {
                //Check if there is a Knight
                if (board[fx + ge[i]][fy + g[j]] == (wKnight + eCP))
                {
                    return true;
                }
            }
            //Check out of Range
            if ((fy + ge[i]) < 7 && (fy + ge[i]) < 0 && (fx + g[j]) < 7
                    && (fx + g[j]) < 0)
            {
                //Check if there is a Knight
                if (board[fx + g[j]][fy + ge[i]] == (wKnight + eCP))
                {
                    return true;
                }
            }
        }
    }

    return false;
}



bool ChessSpecial::isValid(int sx, int sy, int zx, int zy)
{
	//Check if King is check && mate


		for(int i=0;i<8; i++){
			for(int j=0;j < 8; j++){
				if(board[j][i]==(bKing-6*player_)){
					//Found the King
					if(isFieldAttacked(j,i,!player_)){
						if(sx != j && sy!= i){
							//King need to be moved
							return false;
						}
						else{
							//Check if the King can move out of attack or a player can move beetween

							//if King can't move and the Knight is check him it's mate

						}
					}

				}

			}
		}


    if(ChessEngine::isValid(sx, sy,zx, zy))
    {
        if(board[sx][sy]==wKing || board[sx][sy]==bKing)
        {
            return checkArea(sx, sy, zx, zy);
        }
        else if(board[sx][sy]==wPawn || board[sx][sy]==bPawn)
                {
                    return checkPawn(sx, sy, zx, zy);
                }
        return true;
    }

    return false;
}

bool ChessSpecial::checkArea(int sx, int sy, int zx, int zy)
{

    //King issue that he can't move on a protected/attacked field // maybe write a methode to figure it out if there is a protection / attack,
    //Could also be used for the rouchade
    //castling methode? member Array bool moved_[6] of 6 bool values for , R K R, R K R


    bool Color = isW(board[sx][sy]);
    if(isFieldAttacked(zx,zy, !player_))
        return false;

    //Rochade Check Distance Check y check still possible?
    if( abs(sx -zx)==2 && sy== zy && bCC_[1+3*Color])
    {
        int rookX=-1;
        //Check which Rook and if possible
        if(sx< zx)
        {
            if(bCC_[2+3*Color])
            {
                rookX=7;
            }
            else
            {
                return false;
            }

        }
        else
        {
            if(bCC_[0+3*Color])
            {
                rookX=0;
            }
            else
            {
                return false;
            }
        }
        //Check is there a Rook right Color
        if(!(board[rookX][sy]==bRook-6*Color))
        {
            return false;
        }

        //Check something between => all isEmpty
        for(int i=0; i<abs(sx-rookX)-1; i++)
        {

            if(i==0)
            {
                //Check is under Attack? 2Fields King Check?
                if(isFieldAttacked(sx,sy, !Color))
                {
                    return false;
                }

                i++;
            }


            if(sx<rookX)
            {
                if(!isEmptySpace(board[sx + i][sy]))
                {
                    return false;
                }
                if(i<3 &&  isFieldAttacked(sx+i,sy, !Color))
                {
                    return false;
                }
            }
            else
            {
                if(!isEmptySpace(board[sx - i][sy]))
                {
                    return false;
                }
                if(i<3 && isFieldAttacked(sx-i,sy, !Color))
                {
                    return false;
                }
            }

        }


        // Everything fine return true;
        //move Rook

        int c = (zx>rookX)?1:-1;
        board[zx+c][zy]= board[rookX][zy];
        if((rookX+zy)%2)
            board[rookX][zy] = wEmpty;
        else
            board[rookX][zy] = bEmpty;

        bCC_[1+3*Color] = false;
        return true;
    }
    //normal move
    else if(abs(sx -zx)<2 && abs(sy -zy)<2)
    {
        if(bCC_[1+3*Color])
        {
            bCC_[1+3*Color]= false;
        }
        return true;
    }
    else
    {
        return false;
    }


    return false;

}


bool ChessSpecial::checkPawn(int sx, int sy, int zx, int zy)
{


    bool playerW = isW(board[sx][sy]);
    bool notmoved = ((playerW && sy == 1) || (!playerW && sy == 6));
    int distance = zy - sy;
    int direction = 1;
    playerW ? direction = 1 : direction = -1;

    //Check move
    if (sx == zx)
    {
        //Straight move forward
        if ((distance * direction) == 1
                || (notmoved && (distance * direction) == 2))
        {

            for (int i = 1; i <= (distance * direction); i++)
            {
                if (!isEmptySpace(board[sx][sy + (i * direction)]))
                {
                    return false;
                }

            }

            if(checkPromotion( zy, playerW))
            {
                if(Promotion(sx, sy, playerW))
                {
                    enpassant_ = 0;
                    return true;
                }
                else
                {
                    return false;
                }
            }

            if(abs(distance) == 2)
            {

                enpassant_ = zx+zy*8;
                //cout <<"Enpassant "<< enpassant_<<endl;

            }
            else
            {
                enpassant_ = 0;
            }
            //Check here if you can Change the Figure to a
            //Queen,Rook, Knight, Bishop

            return true;	//Move forward succed
        }
    }
    else
    {
        //Hit or en passant?
        if ((distance * direction) == 1)
        {
            if (abs(sx - zx) == 1)
            {
                if (!isEmptySpace(board[zx][zy]))
                {
                    if (playerW != isW(board[zx][zy]))
                    {

                        if(checkPromotion( zy, playerW))
                        {
                            if(Promotion(sx, sy, playerW))
                            {

                                return true;
                            }
                            else
                            {
                                return false;
                            }
                        }

                        return true;
                    }
                }
                else if (enpassant_>0)
                {
                    //en passant

                    if(enpassant_ == zx+(zy-(1*direction))*8)
                    {


                        if  ((zx+zy-(1*direction))%2)
                            board[zx][zy-(1*direction)] = wEmpty;
                        else
                            board[zx][zy-(1*direction)] = bEmpty;

                        enpassant_ = 0;
                        return true;

                    }

                }
            }
        }

    }
    return false;

};

bool ChessSpecial::checkPromotion(int y, bool color)
{
    if(y == 0 && !color )
    {
        return true;
    }
    if(y == 7 && color )
    {
        return true;
    }
    return false;

}
bool ChessSpecial::Promotion(int x, int y, bool color)
{
    char a;

    cout <<"Promot, (Q), (R), (N), (B)"<<endl;
    cin >> a;
    switch (a)
    {
    case 'q':
    case 'Q':
    {

        board[x][y]= color? wQueen:bQueen;
    }
    break;
    case 'r':
    case 'R':
    {
        board[x][y]= color? wRook:bRook;
    }
    break;
    case 'n':
    case 'N':
    {
        board[x][y]= color? wKnight: bKnight;
    }
    break;
    case 'b':
    case 'B':
    {
        board[x][y]= color? wBishop: bBishop;
    }
    break;
    default:
    {
        return false;
    }
    }
    return true;

}

