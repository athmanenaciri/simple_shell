#include "exec.h"
#include "simpleshell.h"

char	*skip(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	return (line + i);
}
