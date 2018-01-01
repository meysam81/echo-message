#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[])
{
    /*Variable*/
    int listenfd = 0, // the resulting integer from creating a socket
            connfd = 0;
    struct sockaddr_in serv_addr; // the structure of ip address, port etc.
	if(argc != 2) // number of command line arguments
    {
        printf("\n Usage: %s <port address> \n",argv[0]);
        return 1;
    }

    char recBuff[1025];

    /*Creat Socket*/
    listenfd = socket(
                AF_INET, // ipv4 address family
                      SOCK_STREAM, // tcp
                0); // IP (internet protocol)


    memset(&serv_addr, '\0', sizeof(serv_addr)); // fill with nulls
    memset(recBuff, '\0', sizeof(recBuff)); // again the same deal

    serv_addr.sin_family = AF_INET; // ipv4
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // listen to all ip's
    serv_addr.sin_port = htons(atoi(argv[1])); // host to network conversion of port 5000

    /*Call Bind*/
    bind(listenfd, // binder to the resulting integer of creating a socket
         (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    /*Listen*/
    listen(listenfd,
           10); // listen to 10 people at the same time

    /*Accept*/

    connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); // accept people trying to reach out the server

    int n = recv(connfd,recBuff, sizeof(recBuff), 0); // receive a message


    // to get the number of characters in the message received from client
    int pos = 0;
    while(recBuff[pos++]);





    printf("recived from client in server:\n");
	//write(0, recBuff, sizeof(recBuff)); // print client's message to screen


    printf("recived message is : %s\n",recBuff);



    if(n<0){

        printf("\n Error : recice error\n");
    }

    int i;
//    int sizeOfMsg = sizeof(recBuff);
    for(i=0;i<5;i++){
        int counter = 0;
        while(counter < pos)
        {
            send(connfd,
                 recBuff + counter, 1, // send 1 Byte = 8 bit which starts from "position of the last sending + 1"
                 0);
            counter += 1; // start sending from the next byte next time
	        sleep(5);
        }

        printf("%d sended from server to client\n",i+1);
    }


    close(connfd); // close the socket obviously


}

