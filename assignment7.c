#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <stdbool.h>


int exitCheck = 1;
int main(){
    do{
        char userInput[128];
        int pid;
        int exitStatus;

        scanf("%[^\n]%*c", userInput);
        //printf("%s",userInput);
        int exitCheck = strcmp(userInput, "exit");
        //printf("%d",exitCheck);
        if (exitCheck == 0){exit(1);}

        bool spaceCheck = false;

        for (int i = 0; i <= strlen(userInput); i++)
        {
            //printf("loopy");
            if (userInput[i] == ' ')
            {
                spaceCheck = true;
                break;
            }
        }
        //char* arglist[2] = {"1","2"};
        if (spaceCheck == false)
        {
            char* arglist[] = {userInput,NULL};
            
            //printf("%s",arglist[0]);
            //printf("%s",arglist[1]);
            
            int pid = fork();
            switch (pid)
            {
             case -1:
                perror("Forking Faiiiiled");
                    exit(1);
            
             case 0:
                execvp(arglist[0], arglist);
                perror( "execvp failed" );
        			    printf("\n");
                        exit(1);
            default:
                while( wait( &exitStatus ) != pid );
            }
        }
        else
        {
            //printf("Else Reached \n");

            //char tempString[128];
            //strcpy(tempString, userInput);
            char *command = strtok(userInput, " ");
            char *arguments = strtok(NULL, "\n");

            //printf("%s",command);
            //printf("\n");
            //printf("%s",arguments);

            char* arglist[3] = {command, arguments, NULL};
            //printf("%s",arglist[1]);
            /*
            int size = sizeof arglist / sizeof arglist[0];
            for (int i = 0; i < size; i++)
            {
                printf("%s\n", arglist[i]);
            }
            */
            
            int pid = fork();
            switch (pid)
            {
             case -1:
                perror("Forking Faiiiiled");
                    exit(1);
            
             case 0:
                execvp(arglist[0], arglist);
                perror( "execvp failed" );
        			    printf("\n");
                        exit(1);
            default:
                while( wait( &exitStatus ) != pid );
            }
        }  
    }while(exitCheck != 0);
    return 0;
}