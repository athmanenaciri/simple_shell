#include "exec.h"
#include "simpleshell.h"

int	var_len(char *str)
{
	int	i;

	i = 1;
	if (str[1] == '?')
		return (2);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}
