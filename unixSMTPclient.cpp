/* 	BGUNIX SMTP client built by Michael Bruns

	** Command to execute **
	client smtp.bgsu.edu toEmail@domain toEmail@domain msgSubject message
*/

#include "/home/cs/kresman/3270/clientServer.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

char buf0[1024];
char buf1[1024];
char buf2[1024];
char buf3[1024];
char buf4[1024];
char buf5[1024];
char buf6[1024];

using namespace std;

int main (int argc, char *argv[]){

	
	/* Create a socket */
	int socketNO = socket(AF_INET, SOCK_STREAM, 0); 
	if (socketNO < 0){ 
		perror("socket creation"); 
		exit(1); 
	}
	
	/* Connects to server */
	if(connectToHost(socketNO, argv[1], 25) < 0){
		perror("connection to host");
		exit(1);
	}
	
	/* Hopefully server says it is pleased to meet you */
	read(socketNO, buf0, 1024);
	
	/* Misspell hello followed by yourDomain */
	write (socketNO, "HELO ", 5);
	write (socketNO, argv[1], strlen(argv[1]));
	write (socketNO, "\n", 1);
	read(socketNO, buf1, 1024);
	
	/* Address the mail is coming from */
	write (socketNO, "MAIL FROM:<", 11);
	write (socketNO, argv[2], strlen(argv[2]));
	write (socketNO, ">", 1);
	write (socketNO, "\n", 1);
	read(socketNO, buf2, 1024);
	
	/* Address the mail is going to */
	write (socketNO, "RCPT TO:<", 9);
	write (socketNO, argv[3], strlen(argv[3]));
	write (socketNO, ">", 1);
	write (socketNO, "\n", 1);	
	read(socketNO, buf3, 1024);
	
	/* Says you are about to start the message & waits for servers OK */
	write (socketNO, "DATA", 5);
	write (socketNO, "\n", 1);
	read(socketNO, buf4, 1024);
	
	/* Writes the subject and the message */
	write (socketNO, "SUBJECT: ", 9);
	write (socketNO, argv[4], strlen(argv[4]));
	write (socketNO, "\n", 1);
	write (socketNO, "\n", 1);
	write (socketNO, argv[5], strlen(argv[5]));
	write (socketNO, "\n", 1);
	write (socketNO, ".", 1);
	write (socketNO, "\n", 1); 		// You've got mail!
	read(socketNO, buf5, 1024);
	
	/* Quits the connection */
	write (socketNO, "QUIT", 4);
	write (socketNO, "\n", 1);
	read  (socketNO, buf6, 1024);
	
	close(socketNO);
	
	printf("%s", buf0);
	cout << "HELO " << argv[1] << endl;
	cout << endl;
	
	printf("%s", buf1);
	cout << "MAIL FROM:<" << argv[2] << ">" << endl;
	cout << endl;
	
	printf("%s", buf2);
	cout << "MAIL TO:<" << argv[3] << ">" << endl;
	cout << endl;
	
	printf("%s", buf3);
	cout << "DATA" << endl;
	cout << endl;
	
	printf("%s", buf4);
	cout << "SUBJECT: " << argv[4] << endl;
	cout << argv[5] << endl;
	cout << "." << endl;
	cout << endl;
	
	printf("%s", buf5);
	cout << "QUIT" << endl;
	cout << endl;
	
	printf("%s\n", buf6);
}