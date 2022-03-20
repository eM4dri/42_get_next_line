
#include "get_next_line.h"

# define DOC "estadioazteca.dict"
# define DOC2 "beatit.dict"
// # include <fcntl.h>
// # include <stdio.h>
// # include <unistd.h>
// # include <stdlib.h>

int	get_next_line(int fd, char **line);

int main(void)
{
	char	*line = NULL;
	int		fd;
	int 	fd2;

	close(0);
	fd = open(DOC, O_RDONLY);
	fd2 = open(DOC2, O_RDONLY);
	free(line);
	int i=-1;
	while( ++i < 5)
	{
		get_next_line(fd, &line);
		printf("%s\n",line);
		free(line);
		// get_next_line(fd2, &line);
		// printf("\t\t%s\n",line);
		// free(line);
	}
	if (close(fd) < 0 && fd != -1)
		return (0);

	system("leaks a.out");
	return (0);
}

