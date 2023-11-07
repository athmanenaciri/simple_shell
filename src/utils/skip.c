#include"../../inc/minishell.h"

char	*skip(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	return (line + i);
}
