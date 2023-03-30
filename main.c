
#include "get_next_line.h"
// #include "get_next_line_bonus.h"

# define DOC "estadioazteca.dict"
# define DOC2 "beatit.dict"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

// int	get_next_line(int fd, char **line);


void ft_leaks()
{
	system("leaks a.out");
}

int main(void)
{
	char	*line = NULL;
	int		fd;
	int 	fd2;

	atexit(ft_leaks);
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

	// system("leaks a.out");
	return (0);
}
//✗ gcc -Wall -Wextra -Werror -fsanitize=address get_next_line.c get_next_line_utils.c main.c
//✗ gcc -Wall -Wextra -Werror -fsanitize=address get_next_line_bonus.c get_next_line_utils_bonus.c main.c
