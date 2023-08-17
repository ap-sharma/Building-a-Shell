#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include<signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_NUM_BACKGROUND_PR 64
void sig_handler(int signo){
	if (signo==SIGINT){
		//printf("\nreceived SIGINT\n");
	}
	else printf("received %d",signo);
}


int bi=0;					//bi is counter for no. of background processes
int fcb[MAX_NUM_BACKGROUND_PR];			//fcb will store PID of running background processes
int j,fc;
/* Splits the string by space and returns the array of tokens
*
*/
char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
	tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
	strcpy(tokens[tokenNo++], token);
	//printf("in tokenise; tokens[tokenNo]=%s",tokens[tokenNo-1]);
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  //printf("in tokenise; tokens[tokenNo]=%s; #%d",tokens[tokenNo],tokenNo);
  //if(tokens[tokenNo]==NULL)
  	//printf("yes");
  return tokens;
}


int main(int argc, char* argv[]) {
	signal(SIGINT,sig_handler);//Register signal handler
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;
	char  **tokensc;              
	int i;
	                 					
	
	
	
	//defining function for signal handling
       		 //void signal_handler(int sigchld){
       		 //int temp_fcb=-fcb[j];
       		 //int reap = waitpid(temp_fcb,NULL,0);
       		 //printf("SHELL: Background process with PID %d finished \n",fcb[j]);
       		 //bi=bi-1;
       		 //return;
       		     		
       		//}

	while(1) {	
		//checking for dead processes and ensuring that fcb array is only filled for 0 to bi
       		//printf("\nreached here***->%d\n",bi);
       		for(j=0;j<bi;++j){
			int reap=waitpid(fcb[j],NULL,WNOHANG);
			//printf("process khatam hui?? %d",reap);
			//printf("reap is %d \n",reap);
			if (reap > 0) {
				printf("\n SHELL: Background process with PID %d finished \n",reap);
				fcb[j]=fcb[bi-1];
				fcb[bi-1]=NULL;
				bi=bi-1;
			}
		}		
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		printf("$ ");
		scanf("%[^\n]", line);	
		getchar();
		//printf("Command entered: %s (remove this debug output later)\n", line);
		/* END: TAKING INPUT */
		//terminate with new line
		line[strlen(line)] = '\n'; 
		tokens=tokensc = tokenize(line);
			
   
       //do whatever you want with the commands, here we just print them
		// kept this for loop because i is a global variable
		
		for(i=0;tokens[i]!=NULL;i++){
		//	printf("found token %s (remove this debug output later) at %d \n", tokens[i],i);
		}
		//SHELL IMPLEMENTATION
       		int a=5;
		char str1[]={'c','d','\0'};
		
		char str2[]={'&','\0'};
		
		char str3[]={'e','x','i','t','\0'};
		
		if(tokens[0]== NULL){
       			continue;
       		}
       		//exit implementation
       		else if (strcmp(tokens[0],str3)==0){
       			for (int k=0;k<bi;k++){
       				kill(fcb[k],SIGKILL);
       				waitpid(fcb[k],NULL,0);       				      			
       			}
       			for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);}
			free(tokens);	
       			break;
       		
       		}
       		//cd implementation
       		else if (strcmp(tokens[0],str1)==0){
			int err = chdir(tokens[1]); 
			if (err != 0) printf("SHELL:Incorrect cd command ");
		}
       		
       		if (strcmp(tokens[0],str1) != 0){
       			// To determine fc in case of background processes
       			if(strcmp(tokens[i-1],str2) == 0){
       				if (bi >= MAX_NUM_BACKGROUND_PR) printf("Too many background processes");
       				else {
       				fcb[bi]=fork();
       				bi++;
       				fc = fcb[bi-1];
       				//printf("comparing &, fc=%d",fc);
       				//printf("****%d",strcmp(tokens[i-1],str2));
       				}} 		
	       		else{
	       			//printf("\n This is not a background process \n");
	       			fc=fork();
	       			//printf("forked a child for non bg process; fc= %d",fc);
	       		}
	       		
		       	//printf("forked a child and fc= %d",fc);
		       	if (fc<0){// fork failed
		       		fprintf(stderr,"%s\n","Unable to create child process\n");
		       		}
	       		else if(fc==0){//child code
	       			//printf("\n child process with PID %d",fc);
	       			if(strcmp(tokens[i-1],str2) == 0) {tokensc[i-1]=NULL;setpgid(0,0);}
	       			execvp(tokens[0],tokensc);
				printf("Invalid command\n");
				exit(1);
			}		
	       		else if (fc>0){//parent code
	       			//if(strcmp(tokens[i-1],str2) == 0) printf("\n in parent when background %s \n",tokens[i-1]);
		       		if(strcmp(tokens[i-1],str2) != 0) {
		       		int wc=waitpid(fc,NULL,0);
		       		}
	       		}
       		}
       		
       		
	// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);}
		free(tokens);
			
	}
	
	return 0;
}
	

