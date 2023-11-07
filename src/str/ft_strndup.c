#include"../../inc/minishell.h"

char	*ft_strndup(char *s, int n)
{
	char	*res;
	int		i;

	if (n == -1)
		n = ft_strlen(s);
	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
