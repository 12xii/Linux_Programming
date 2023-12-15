#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "applicationHeader.h"

void initSwManager(swManager* manage) //Init struct swManager
{
    manage->p_no = 0;
    manage->deadPid = 0;
    for(int i = 0; i < BLOCK_COUNT; i++) {
        manage->pids[i] = 0;
        manage->inform[i].name = (String)malloc(sizeof(char)*20);
        manage->inform[i].reason = (String)malloc(sizeof(char)*50);
        manage->inform[i].exitCode = (String)malloc(sizeof(char)*10);
        manage->inform[i].restartCount = 0;
        manage->inform[i].startTime = (String)malloc(sizeof(char)*30);
        manage->swParam[i].name = (String)malloc(sizeof(char)*20);
        manage->swParam[i].para1 = (String)malloc(sizeof(char)*20);
        manage->swParam[i].para2 = (String)malloc(sizeof(char)*20);
        manage->swParam[i].para3 = (String)malloc(sizeof(char)*20);
    }
}

void readFileList(swManager* manage)
{
    FILE* fp;
    fp = fopen("./FileList", "r");
    char str[MAX_STR];
    int swno = 0;

    while(fgets(str, MAX_STR, fp))
    {
        char* result;
        str[strlen(str)-1] = 0; // 줄바꿈 삭제
        
        result = strtok(str, ";");
        strcpy(result, trim(result));

        strcpy(manage->param[swno].name, result);

        for(int i = 0; result = strtok(NULL, ";"); i++)
        {
            strcpy(result, trim(result));

            switch (i){
            	case 0:
                	strcpy(manage->param[swno].para1, result);
                	break;
            	case 1:
                	strcpy(manage->param[swno].para2, result);
                	break;
            	case 2:
                	strcpy(manage->param[swno].para3, result);
                	break;
            
            default:
                break;
            }
        }

        swno++;
    }

    manage->p_no = swno;
}

void initSwBlock(swManager* manage)
{
    pid_t pid;
    int i, status;

    for(i = 0; i < manage->p_no; i++){
        strcpy(info->swInfo[i].name, info->param[i].name);
        sprintf(info->swInfo[i].reason, "Init.");
        sprintf(info->swInfo[i].restartCount, "%d", 0);
        strcpy(info->swInfo[i].startTime, gettime());

        LogWrite(&(manage->swInfo[i]));
        LogInterface(manage);

        pid = fork();

        if(pid > 0) { //p
            manage->pids[i] = pid; 
        }
        else if(pid == 0) {
            char path[30] = "./";
            strcat(path, manage->param[i].name);
            execl(path, manage->param[i].name, 
            info->param[i].para1, 
            info->param[i].para2, 
            info->param[i].para3, NULL);
        }
    }
}

void reinitSwBlock(swManager* manage, int index) {
    pid_t pid;

    pid = fork();

    if(pid > 0) {
        manage->pids[index] = pid;
        strcpy(manage->swInfo[index].startTime, gettime());
    }
    else if(pid == 0) {
        char path[30] = "./";
        strcat(path, info->param[index].name);
        execl(path, info->param[index].name,
        manage->param[index].para1, 
        manage->param[index].para2, 
        manage->param[index].para3, NULL);
    }
}

int findSwBlock(swManager* manage) {
    for(int i = 0; i < manage->p_no; i++) {
        if(manage->deadPid == manage->pids[i]) {
            return i;
        }
    }

    return -1;
}

void logWrite(swInfo* inform) {
    mkdir(LOGDIR, 0755);
    chdir(LOGDIR);

    FILE* fp;

    fp = fopen(LOGFILE, "a");

    fprintf(fp, "S/W block name: %s\trestart count: %s\tstart time: %s\treason: %s\n",
                    inform->name, inform->restartCount, inform->startTime, inform->reason);

    fclose(fp);  

    chdir("../");
}

void logInterface(swManager* manage) {
    char param[10];

    system("clear");
    printf(" _____________________________________________________________________________________________ \n");
    printf("| S/W block name | Restart count |       Start time        |               Reason               |\n");
    printf("|______________|_______________|_________________________|____________________________________|\n");

    for(int i = 0; i < manage->p_no; i++)
    {
        printf("| %12s |", manage->swInfo[i].name);
        printf(" %13s |", manage->swInfo[i].restartCount);
        printf(" %s|", manage->swInfo[i].startTime);
        printf(" %34s |\n", manage->swInfo[i].reason);
    }

    printf("|______________|_______________|_________________________|____________________________________|\n");
}

char* rtrim(const char* s)
{
    while(isspace(*s) || !isprint(*s)) ++s;
    return strdup(s);
}

char* ltrim(const char* s)
{
    char* r = strdup(s);
    if(r != NULL)
    {
        char* fr = r + strlen(s) - 1;
        while((isspace(*fr) || !isprint(*fr) || *fr == 0) && fr >= r) --fr;
        *++fr = 0;
    }
    return r;
}

char* trim(const char* s)
{
    char* r = rtrim(s);
    char* f = rtrim(r);
    free(r);
    return f;
}

char *gettime(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    time_t t = (time_t)tv.tv_sec;

    struct tm *ptm = localtime(&t);

    static char str[1024];

    sprintf(str, "%04d.%02d.%02d %02d:%02d:%02d.%03d ",

            ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,

            ptm->tm_hour, ptm->tm_min, ptm->tm_sec, (int)tv.tv_usec / 1000);

    return str;
}
