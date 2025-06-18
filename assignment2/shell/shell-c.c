#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

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

	for (i = 0; i < strlen(line); i++)
	{

		char readChar = line[i];

		if (readChar == ' ' || readChar == '\n' || readChar == '\t')
		{
			token[tokenIndex] = '\0';
			if (tokenIndex != 0)
			{
				tokens[tokenNo] = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
				strcpy(tokens[tokenNo++], token);
				tokenIndex = 0;
			}
		}
		else
		{
			token[tokenIndex++] = readChar;
		}
	}

	free(token);
	tokens[tokenNo] = NULL;
	return tokens;
}

int check_exit_status(int status)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void reap_zombie_children()
{
	int status;
	pid_t pid;

	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		printf("Shell: Background process finished\n");
		if (check_exit_status(status))
		{
			printf("EXITSTATUS: 1\n");
		}
	}
}

int main(int argc, char *argv[])
{
	char line[MAX_INPUT_SIZE];
	char **tokens;
	int i;
	char *buf;

	while (1)
	{
		/* BEGIN: TAKING INPUT */
		bzero(line, sizeof(line));
		buf = getcwd(NULL, 0);
		printf("%s$ ", buf);
		scanf("%[^\n]", line);
		getchar();

		/* END: TAKING INPUT */

		reap_zombie_children();

		line[strlen(line)] = '\n'; // terminate with new line
		tokens = tokenize(line);

		if (tokens[0] != NULL)
		{
			char *last_token = tokens[0];
			int i;
			for (i = 1; tokens[i] != NULL; i++)
				last_token = tokens[i];

			if (strcmp(tokens[0], "cd") == 0)
			{
				if (chdir(tokens[1]) != 0)
					printf("Error. Path not found\n");
			}
			else if (strcmp(last_token, "&") == 0)
			{
				pid_t pid = fork();
				tokens[i - 1] = NULL;
				if (pid == 0)
				{
					execvp(tokens[0], tokens);

					printf("Command not found\n");
					exit(1);
				}
			}
			else
			{
				pid_t pid = fork();
				if (pid == 0)
				{
					execvp(tokens[0], tokens);

					printf("Command not found\n");
					exit(1);
				}
				else if (pid > 0)
				{
					int ws;
					waitpid(pid, &ws, 0);
					if (WIFEXITED(ws))
					{
						if (WEXITSTATUS(ws))
						{
							printf("EXITSTATUS: %d\n", WEXITSTATUS(ws));
						}
					}
				}
			}
		}
		// do whatever you want with the commands, here we just print them

		// Freeing the allocated memory
		for (i = 0; tokens[i] != NULL; i++)
		{
			free(tokens[i]);
		}
		free(tokens);
		free(buf);
	}
	return 0;
}
