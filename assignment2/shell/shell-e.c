#include  <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64


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
	tokenIndex = 0; 
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }
 
  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}



int main(int argc, char* argv[]) {
	char  line[MAX_INPUT_SIZE];            
	char  **tokens;              
	int i;
	char *buf;
	signal(SIGINT, SIG_IGN);

	while(1) {

		buf = getcwd(NULL, 0);
		printf("%s$ ",buf);
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		scanf("%[^\n]", line);
		getchar();

		/* END: TAKING INPUT */

		line[strlen(line)] = '\n'; //terminate with new line
		tokens = tokenize(line);
  		
		if(tokens[0]!=NULL){
			if(strcmp(tokens[0], "cd")==0){
				if(chdir(tokens[1])!=0)
					printf("Error. Path not found\n");
			}else if(strcmp(tokens[0], "exit")==0){
				for(i=0;tokens[i]!=NULL;i++){
					free(tokens[i]);
				}
				free(tokens);
				free(buf);
				kill(getpid(),1);		
			}else{
				pid_t pid = fork();
				if(pid==0){
					signal(SIGINT, SIG_DFL);
					execvp(tokens[0], tokens);
				
					printf("Command not found\n");
					exit(1);
				}else if(pid>0){
					int ws;
					waitpid(pid, &ws, 0);
					signal(SIGINT, SIG_IGN);					
					if(WIFEXITED(ws)){
						if(WEXITSTATUS(ws)){
							printf("EXITSTATUS: %d\n", WEXITSTATUS(ws));
						}
					}
				}
			}
		}
       //do whatever you want with the commands, here we just print them
       
		// Freeing the allocated memory	
		for(i=0;tokens[i]!=NULL;i++){
			free(tokens[i]);
		}
		free(tokens);
		free(buf);

	}
	return 0;
}
