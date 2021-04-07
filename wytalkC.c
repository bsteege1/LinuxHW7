#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <string.h>
#include "socketfun.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    int port = 51100;
    char end = '\n';
    char buff[1024];

    //creates connection with D
    int sockFd = request_connection(argv[1], port);

    //Error to check for failed connection
    if (sockFd == 1 || sockFd == -1)
    {
        return 0;
    }

    while (1)
    {
        //readBuff holds values read in from D
        char readBuff[1024];

        //Gets user input
        if (fgets(buff, 1024, stdin) == NULL)
        {
            //if user input closes
            if (feof(stdin))
            {
                write(sockFd, "\n", 1);

                read(sockFd, readBuff, 1);
                printf("%s", readBuff);

                //read last input
                while (readBuff[0] != end)
                {
                    read(sockFd, readBuff, 1);
                    printf("%s", readBuff);
                }
                //End
                break;
            }
            else
            {
                printf("User Input Error: \n");
                break;
            }
        }

        //The user input is written to the socket
        write(sockFd, buff, strlen(buff));

        //Reads in first byte to check if the value is a return
        int readCheck = read(sockFd, readBuff, 1);
        //checking for EOF from C
        if (readCheck == 0 || readCheck == -1)
        {
            //The final write is the most recent 
            //write due to nature of the loop
            close(sockFd);
            break;
        }
        //If it isn't, print the first char and read the rest
        printf("%s", readBuff);
        //Loop to allow reading one line at a time
        //Stops once the return char is read in
        while (readBuff[0] != end)
        {
            read(sockFd, readBuff, 1);
            printf("%s", readBuff);
        }
    }

    //Closes the socket
    close(sockFd);
    return 0;
}