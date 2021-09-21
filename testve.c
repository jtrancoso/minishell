#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argv, char **argc, char **envp)
{
	int pid = fork();
	char **cmd;
	int i = 0;

	cmd = malloc (sizeof(char *) * 3);
	cmd[0] = strdup("/bin/ls");
	cmd[1] = strdup("-l");
	cmd[2] = NULL;

	if (pid == 0)
	{
		execve(cmd[0], cmd, envp);
		exit(0);
	}
	else
	{
		wait(&i);
		printf("Hola\n");
	}
	return(0);
}