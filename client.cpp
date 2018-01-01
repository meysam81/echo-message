// send, sendto, sendmsg - send a message on a socket
#include <sys/socket.h>
#include <sys/types.h>



/*
sa_family_t    sin_family
in_port_t      sin_port
struct in_addr sin_addr
unsigned char  sin_zero[8]
*/
#include <netinet/in.h>



#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

using namespace std;


int main(int argc, char *argv[])
{
    int sockfd = 0; // to hold the result of creating a socket
    const char sendingMSg[1024] = "This is a message from client";
    int pos = 0;
    while(sendingMSg[pos++]); // to get the size of the message


    char receivingMsg[1024];

    struct sockaddr_in serv_addr;

    if(argc != 3) // number of command line arguments
    {
        printf("\n Usage: %s <ip of server> <port address> \n",argv[0]);
        return 1;
    }


    memset(receivingMsg, '\0',sizeof(receivingMsg)); // fill the buffer with nulls


    if((sockfd =
        socket(AF_INET, // ipv4 address type
                        SOCK_STREAM, // tcp socket, not udp
               0) // IP (internet protocol)
        ) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    }



    memset(&serv_addr, '0', sizeof(serv_addr));// fill the buffer with nulls




    serv_addr.sin_family = AF_INET; // AF_INET (IPv4 protocol) , AF_INET6 (IPv6 protocol
    serv_addr.sin_port = htons(atoi(argv[2])); // htons: host to network conversion



    if(
            inet_pton( // new with IPv6 and work with both IPv4 and IPv6 addresses.
                       // "p" stands for presentation
                AF_INET, // covered before
                 argv[1], // ip address from command line arguments
                       &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    }

    if( // if failed to create a socket
            connect(
                sockfd, // the integer to hold the result of creating a socket
                    (struct sockaddr *)&serv_addr, // structure of ip address, port etc.
                sizeof(serv_addr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        return 1;
    }

//    printf("enter your message: ");
//    gets(s);



    send(
                sockfd, // send with the same integer that held the result of creating a socket
                sendingMSg, pos, 0);
    printf("sended from client to server\n");



    int rn=0, // receive result
            c=0; // number of received bytes
    while((rn=recv(
               sockfd, // again receive data with the same integer used for creating the socket
               receivingMsg, sizeof(receivingMsg), 0))>0 ){
        c++;
		printf("%d recived message from server \n", c );
		//sleep(4);


    }


    return 0;
}

