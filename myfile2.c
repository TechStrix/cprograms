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
	char a;
	pid_t pid;
	int status;
	FILE *fp1, *fp2;

	
	while (getinput(buf, sizeof(buf))) {
		buf[strlen(buf) - 1] = '\0';
		/* Place your code to check "exit". If so, then exit */

		if(strstr(getinput(buf, sizeof(buf)),"exit") != NULL ) {

			printf("bye");
                        exit(EX_OK);
                }

		if((pid=fork()) == -1) {
			fprintf(stderr, "shell: can't fork: %s\n", strerror(errno));
			continue;
		} else if (pid == 0) {
			/* child process to do each command 
   – place your code here to handle read, write, append */
					
			printf("entered child process");			

			if((strstr(getinput(buf, sizeof(buf)),"read < hello.c") != NULL) && (strstr(getinput(buf, sizeof(buf)),"read < hello.c | write > hello2.c") == NULL) ) {
					
				printf("reading...");

				fp1 = fopen("hello.c", "r");
				fp2 = fopen("temp.txt", "w");
				do {
      					a = fgetc(fp1);
      					fputc(a, fp2);
   				} while (a != EOF);
				
				exit(0);

                
			} else if (strstr(getinput(buf, sizeof(buf)),"write > out1.c") != NULL){

				printf("writing...");

                                fp1 = fopen("temp.txt", "r");
                                fp2 = fopen("out1.c", "w");
                                do {
                                        a = fgetc(fp1);
                                        fputc(a, fp2);
                                } while (a != EOF);

                                exit(0);
		
			} else if (strstr(getinput(buf, sizeof(buf)),"read < hello.c | write > hello2.c") != NULL){
			
				printf("reading...");
                                
                                fp1 = fopen("hello.c", "r");
                                fp2 = fopen("temp.txt", "w");
                                do {    
                                        a = fgetc(fp1);
                                        fputc(a, fp2);
                                } while (a != EOF);

                                fclose(fp1);
				fclose(fp2);
                        
                                printf("writing...");

                                fp1 = fopen("temp.txt", "r");
                                fp2 = fopen("hello2.c", "w");
                                do {
                                        a = fgetc(fp1);
                                        fputc(a, fp2);
                                } while (a != EOF);

                                exit(0);			

	
			} else if (strstr(getinput(buf, sizeof(buf)),"append >> out2.c") != NULL){

				printf("appending...");
        
                                fp1 = fopen("temp.txt", "r");
                                fp2 = fopen("out2.c", "a");
                                do {
                                        a = fgetc(fp1);
                                        fputc(a, fp2);
                                } while (a != EOF);

                                exit(0);	
			}	

			exit(EX_OK);
		}

		if ((pid=waitpid(pid, &status, 0)) < 0)
			fprintf(stderr, "shell: waitpid error: %s\n",
					strerror(errno));
	}
	exit(EX_OK);
}

