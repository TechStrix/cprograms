/*c program for taking bash commands from user*/

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

char *getinput(char *buffer, size_t buflen) {
	printf("$$ ");
	return fgets(buffer, buflen, stdin);
}

int main(int argc, char **argv) {
	char buf[1024];
	pid_t pid;
	int status;
	
	char* fcmd;
	char* cmd;
	
	char* cmd1;
	char* op1;
	char* file1;

	char* delim = "\0";

	char* cmd2;
	char* op2;
	char* file2;
	
	char* syscall;
	

	
	while (getinput(buf, sizeof(buf))) {
		buf[strlen(buf) - 1] = '\0';
		/* Place your code to check "exit". If so, then exit */
		
		strcpy(cmd,buf);
		sscanf(cmd, "%s %s %s %s %s %s %s", cmd1, op1, file1, delim, cmd2, op2, file2 );

		
		if(strstr(getinput(buf, sizeof(buf)),"exit") != NULL ) {
			exit(EX_OK);			
		}
		
		if((pid=fork()) == -1) {
			fprintf(stderr, "shell: can't fork: %s\n", strerror(errno));
			continue;
		} else if (pid == 0) {
			/* child process to do each command 
   – place your code here to handle read, write, append */
		

			/*strcpy(fcmd, getinput(buf, sizeof(buf));*/
		
			printf("%s",cmd1);		
			if (strstr(delim,"\0")!=NULL){

				snprintf(syscall, sizeof(syscall), "cat temp.txt %s %s %s cat tempt.txt %s %s", op1, file1, delim,  op2, file2);
				system(syscall);			
	
			} else {

				if (strstr(cmd1,"read")!=NULL){
				
					snprintf(syscall, sizeof(syscall), "cat temp.txt %s %s", op1, file1);
                        		system(syscall);
				}

				else if (strstr(cmd1,"write")!=NULL) {
			
					snprintf(syscall, sizeof(syscall), "cat temp.txt %s %s", op1, file1);
                                	system(syscall);

				}	

				else if (strstr(cmd1,"append")!=NULL) {

					snprintf(syscall, sizeof(syscall), "cat temp.txt %s %s", op1, file1);
                                	system(syscall);

				}


			}	

				exit(EX_OK);
		}

		if ((pid=waitpid(pid, &status, 0)) < 0)
			fprintf(stderr, "shell: waitpid error: %s\n",
					strerror(errno));
	}
	exit(EX_OK);
}

