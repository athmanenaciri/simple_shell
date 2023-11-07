#include "exec.h"
#include "simpleshell.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	int		s1_len;
	char	*str;

	if (n == -1)
		n = ft_strlen(s2);
	if (s1 == NULL)
		return (ft_strndup(s2, n));
	s1_len = ft_strlen(s1);
	str = malloc(s1_len + n + 1);
	if (str == NULL)
		return (0);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcpy(str + s1_len, s2, n + 1);
	return (str);
}
