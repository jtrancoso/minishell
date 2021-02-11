#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct stat buffer;

void forkexample()
{
	if (fork() == 0)
		printf("Hello from child\n");
	else
		printf("Hello from parent\n");	
}

int main ()
{
	printf("%d\n", stat("/Users/jtrancos/Desktop/Curso/Ejercicios/minishell/main.c", &buffer));
	printf("%4lld\n", buffer.st_size);
	printf("%4d\n", buffer.st_nlink);
	return (0);
}