#include "exec.h"
#include "simpleshell.h"

static int	nbr_size(int nbr)
{
	int	i;

	i = 1;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int nbr)
{
	int			i;
	int			is_neg;
	static char	result[25];

	is_neg = nbr < 0;
	i = (nbr <= 0) + nbr_size(nbr);
	result[0] = '-';
	result[--i] = 0;
	if (!is_neg)
		nbr *= -1;
	while (--i >= is_neg)
	{
		result[i] = (nbr % 10 * -1) + '0';
		nbr /= 10;
	}
	return (result);
}

void	print_var(char *var, int size)
{
	printf("declare -x %.*s", size, var);
	if (var[size] == '\0')
	{
		printf("\n");
		return ;
	}
	var += size + 1;
	printf("=\"");
	while (*var)
	{
		size = ft_strchar(var, "\"");
		printf("%.*s", size, var);
		if (var[size] == '"')
			printf("\\\"");
		var += size + (var[size] != '\0');
	}
	printf("\"\n");
}
