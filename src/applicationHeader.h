#ifndef __APPLICATION_HEADER_H__
#define __APPLICATION_HEADER_H__

#include <sys/types.h>

#define MAX_STR 100
#define BLOCK_COUNT 10
#define LOGDIR "./log"
#define LOGFILE "restart.txt"

typedef struct {
	char* name;
	char* startTime;
	char* exitCode;
	char* reason;
	int restartCount;
} swInfo;

typedef struct {
		char* name;
		char* para1;
		char* para2;
		char* para3;
} swParam;

typedef struct {
		int deadPID;
		int pids[BLOCK_COUNT];
		swInfo inform[BLOCK_COUNT];
		swParam param[BLOCK_COUNT];
		int p_no;
} swManager;

void readFileList(swManager* manage);
void initSwBlock(swManager* manage);
void initSwManager(swManager* manage);
int findSwBlock(swManager* manage);
void reinitSwBlock(swManager* manage, int index);
void logWrite(swInfo* inform);
void logInterface(swManager* manage);

char* rtrim(const char* s);
char* ltrim(const char* s);
char* trim(const char* s);
char *gettime(void);

#endif
