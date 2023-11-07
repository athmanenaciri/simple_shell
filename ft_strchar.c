#include "exec.h"
#include "simpleshell.h"

int	ft_strchar(char *line, char *str)
{
	int	i;
	int	j;	

	i = 0;
	while (line[i])
	{
		j = 0;
		while (str[j])
		{
			if (line[i] == str[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
