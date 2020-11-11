#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1024

char	*check_reaminder(char *reaminder, char **line)
{
	char	*ptr_to_nl;

	ptr_to_nl = NULL;
	if (reaminder)
	{
		if ((ptr_to_nl = strchr(reaminder, '\n')))
		{
			ptr_to_nl = '\0';
			*line = strdup(reaminder);
			strcpy(reaminder, ++ptr_to_nl);
		}

	}
	else
		*line = strdup(reaminder);
	return (ptr_to_nl);
}

int	get_next_line(int fd, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	int	bytes_readed;
	char	*ptr_to_nl;
	static char	*reaminder;

	ptr_to_nl = check_reaminder(reaminder, line);
	while (!ptr_to_nl && (bytes_readed = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bytes_readed] = '\0';
		if ((ptr_to_nl = strchr(buf, '\n')))
		{
			*ptr_to_nl = '\0';
			ptr_to_nl++;
			reaminder = strdup(ptr_to_nl);
		}
		*line = strcat(*line, buf);
	}
	return (0);
}

int	main(void)
{
	char	*line;
	int	fd;

	fd = open("text.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);
	return (0);
}
