

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char const *argv[])
{
	int	pid;

	pid = fork();
	open("infile", O_RDONLY);
	while (1)
	{
		printf("Hellooooo miniHELLLLLL %i\n", pid);
		sleep(1);
	}
	return (0);
}
