#include "applicationHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status;
    char exit_code[50];

    swManager* mySwInfo = (swManager*)malloc(sizeof(swManager));
    initSwManager(mySwInfo);

    readFileList(mySwInfo);
    initSwBlock(mySwInfo);

    while(1)
    {
        mySwInfo->deadPID = waitpid(-1, &status, 0);

        if(mySwInfo->deadPID != -1)
        {
            int idx = findSwBlock(mySwInfo);
            mySwInfo->inform[idx].restartCount++;
            sprintf(mySwInfo->inform[idx].restartCount, "%d", mySwInfo->inform[idx].restartCount);

            if(WIFEXITED(status)) {
                sprintf(exit_code, "EXIT(%d)", WEXITSTATUS(status));
                strcpy(mySwInfo->inform[idx].reason, exit_code);
            }
            else if(WIFSIGNALED(status)) {
                sprintf(exit_code, "SIGNAL(%d).%s", WTERMSIG(status), strsignal(WTERMSIG(status)));
                strcpy(mySwInfo->inform[idx].reason, exit_code);
            }

            reinitSwBlock(mySwInfo, idx);
            logWrite(&(mySwInfo->inform[idx]));
            logInterface(mySwInfo);
        }
    }
}
