#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


void runCommand(char **);

int main(void) {

  char input[2048];

  while(strcmp(input, "exit") != 0){
     printf("MUSH ~# ");
     fflush(stdout);
     fgets(input, 2048, stdin);
		
     char *token;
     char *argv[128];
     argv[127] = NULL;
     int i = 0;

     if((token = strtok(input, " \t\n\r")) != NULL){
	do{
           argv[i] = token; 
	   argv[i + 1] = NULL;
	   i++;
	 } while((token = strtok(NULL, " \t\n\r")) != NULL);
     }
  
     runCommand(argv);

     printf("\n");		 	
  }//while
}//main



void runCommand(char **argv){

   if(strcmp(argv[0], "cd") == 0){
      printf("chdir called...\n");
      pid_t pid = chdir(argv[1]);
      if(pid == -1){
	perror("chdir");
	printf("Second word of command line: %s\n", argv[1]);
      }	
   }	   
   if(strcmp(argv[0], "ls") == 0){
     printf("ls called...");
     pid_t pid = fork();
        if(pid == 0){
	   execvp(argv[0], argv);
	   perror("exec");
	   exit(1);
	}
	else{
           wait(NULL);
        }	   
   }
   if(strcmp(argv[0], "exit") == 0){
     printf("exiting...\n");
     exit(0);
   } 
}
