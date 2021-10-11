{
	int	fd[2];
	pipe(fd);

	int	pid = fork();
	
	if (pid)
	{
		dup2(fd[1], 1);
		echo hola
		write(fd[1], "hola", 4);
		close(fd[0]);
		// padre
	}
	else
	{
		dup2();
		read(fd[0], 4);
		close(fd[1]);
		// hijo
	}
}