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


class SimpleServer : public TCPserver{
public:

	SimpleServer(int port, int length): TCPserver(port, length){;};
protected:
	string myResponse(string input);

};

string SimpleServer::myResponse(string input){


	if(input.compare(0,4,"init") == 0){
		return string("Init Okay");
	}
	else if(input.compare(0,4,"hash") == 0){
		return string("hash Okay");
	}
	else if(input.compare(0,5,"xturn") == 0){
		return string("execute Turn Okay");
	}
	else if(input.compare(0,5,"gturn") == 0){
		return string("getTurn Okay");
	}
	return string("Unknown Command");
}



int main(){
	srand(time(nullptr));
	SimpleServer srv(2022,25);
	srv.run();
}
