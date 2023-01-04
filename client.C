/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants

#include "chess.hpp"
#include "SHA256.H"
#include "SIMPLESOCKET.H"

using namespace std;

int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;
	IChess* game = new ChessSpecial();

	//connect to host
	c.conn(host , 2022);

	int i=0;
	bool goOn=1;
	while(goOn){
		char ch;
		cout << "Start game? (y/n) " << flush;
		cin >> ch;
		if((ch=='n')||(ch=='N'))
			goOn = 0;

		game->init();
		c.sendData(string("INIT"));
		msg = c.receive(32);

		if(msg.compare(0,2,"OK")!=0){
			goOn = 0;
			cout << "communication error" << endl;
			cout << msg << endl;
			}
		while(goOn){
			string cstate = game->getState();
			c.sendData(string("HASH"));
			msg = c.receive(64);

			cout <<"msg =" <<  msg << endl;
			if(cstate.compare(msg) != 0){
				cout << "chessboard desync... restarting game." << endl;
				break;
			}
			char sx,zx;
			int sy,zy;

			game->print();

			do{
				cout << "input start coordinates:";
				
				cin >> sx >> sy;
				//cout << sx << " " << sy << endl;
				if(cin.fail()){
					cin.clear();
					cout << "ERROR" << endl;
					cin.ignore(1000,'\n');
					continue;
				}

				cout << "input destination coordinates:";
				cin >> zx >> zy;
				//cout << zx << " " << zy << endl;
				if(cin.fail()){
					cin.clear();
					cout << "ERROR" << endl;
					cin.ignore(1000,'\n');
					continue;
				}

			}while(!game->isValid(sx-'a',sy-1,zx-'a',zy-1));
			game->execTurn(sx-'a',sy-1,zx-'a',zy-1);
			game->print();
			
			string coords("EXEC");
			coords = ((((coords + sx)+(char)('0'+sy))+zx)+(char)('0'+zy)); 

			c.sendData(coords);
			msg = c.receive(32);
			
			if(msg.compare(0,2,"OK")!=0){
				cout << "exec error" << endl;
				cout << "msg = " << msg << endl;
				continue;
			}
			
			c.sendData(string("GET_TURN"));
			msg = c.receive(32);

			cout << "server executes turn: " << msg << endl;
			if(game->isValid(msg[0]-'a',msg[1]-'1',msg[2]-'a',msg[3]-'1')){
				game->execTurn(msg[0]-'a',msg[1]-'1',msg[2]-'a',msg[3]-'1');
				game->print();
			}else{
				cout << "executing turn failed" << endl;
				continue;
			}
		}
	}

	msg = string("BYEBYE");
	c.sendData(msg);
	delete game;
}


