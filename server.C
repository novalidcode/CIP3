/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "chess.hpp"
#include "SHA256.H"

class SimpleServer : public TCPserver{
public:

	SimpleServer(int port, int length): TCPserver(port, length){
		chess = new ChessSpecial();	
	};
	~SimpleServer(){
		if(chess!=nullptr)
			delete chess;
	}
protected:
	IChess* chess;
	string myResponse(string input);

};

string SimpleServer::myResponse(string input){


	if(input.compare(0,4,"INIT") == 0){
		chess->init();
		return string("OK");
	}
	else if(input.compare(0,4,"HASH") == 0){
		string state = chess->getState();
		return state;
	}
	else if(input.compare(0,4,"EXEC") == 0){ 
		if(input.length()>=8){
			if(chess->isValid(input[4]-'a',input[5]-'1',input[6]-'a',input[7]-'1')){
				chess->execTurn(input[4]-'a',input[5]-'1',input[6]-'a',input[7]-'1');
				chess->print();
				return string("OK");
			}
		}
		return string("ERROR");
	}
	else if(input.compare(0,8,"GET_TURN") == 0){
		string coords("");
		char sx,zx;
		int sy,zy;

		chess->print();

		do{
			cout << "Input start coordinates:";
			
			cin >> sx >> sy;
			//cout << sx << " " << sy << endl;
			if(cin.fail()){
				cin.clear();
				cout << "ERROR" << endl;
				cin.ignore(1000,'\n');
				continue;
			}

			cout << "Input destination coordinates:";
			cin >> zx >> zy;
			//cout << zx << " " << zy << endl;
			if(cin.fail()){
				cin.clear();
				cout << "ERROR" << endl;
				cin.ignore(1000,'\n');
				continue;
			}

		}while(!chess->isValid(sx-'a',sy-1,zx-'a',zy-1));
		chess->execTurn(sx-'a',sy-1,zx-'a',zy-1);

		coords = ((((coords + sx)+(char)('0'+sy))+zx)+(char)('0'+zy)); 
		return coords;
	}
	return string("Unknown Command");
}



int main(){
	srand(time(nullptr));
	SimpleServer srv(2022,25);
	srv.run();
}
