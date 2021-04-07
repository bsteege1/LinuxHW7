#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "socketfun.h"
#include <stdlib.h>

int main()
{
    int port = 51100;
    int server_fd;
    char end = '\n';

    //Gets hostname for socket creation
    char hostname[256];
    gethostname(hostname, 256);

    //Creating socket
    server_fd = serve_socket(hostname, port);
    //Listens for connection request, errors if fails
    if (listen(server_fd, 1) < 0)
    {
        return 0;
    }

    //Accepting the connection
    int newFD;
    newFD = accept_connection(server_fd);

    //writebuff is used for writing to client
    //char writeBuff[1024];

    while (1 == 1)
    {

        char readBuff[1024];
        int i = 0;
        int readCheck;
        //reading in first char for check
        readCheck = read(newFD, readBuff, 1);

        //checking for EOF from C
        if(readCheck == 0 || readCheck == -1)
        {
            char finWrite[1024];
            //getting final message to be sent to C
            fgets(finWrite, 1024, stdin);
            write(newFD, finWrite, strlen(finWrite));
            //Ends loop
            break;
        }

        //Otherwise, print the first value
        printf("%s", readBuff);
        //read the rest of the values until, the end is reached
        while (readBuff[0] != end)
        {

            read(newFD, readBuff, 1);
            printf("%s", readBuff);
        }

        //writebuff is used for writing to client
        char writeBuff[1024];
        //getting user input from stdin
        fgets(writeBuff, 1024, stdin);
        //if the user input is a return character, the program ends
        //if(writeBuff[0] == end)
        if (feof(stdin))
        {
            write(newFD, "\n", 1);

            read(newFD, readBuff, 1);
            printf("%s", readBuff);

            while (readBuff[0] != end)
            {

                read(newFD, readBuff, 1);
                printf("%s", readBuff);
            }
            break;
        }

        //Writes user input to the socket.
        write(newFD, writeBuff, strlen(writeBuff));
        i++;
    }
    //closing both sockets
    close(newFD);
    close(server_fd);

    return 0;
}