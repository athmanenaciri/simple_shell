#include"../../inc/minishell.h"

int	is_var(char *str)
{
	return (*str == '?' || *str == '_' || ft_isalpha(*str));
}

char	*dolar(t_list *tk, char *line)
{
	int	i;

	i = 2;
	while (line[i] && (line[i] == '_' || ft_isalnum(line[i])))
		i++;
	tk->val = ft_strndup(line + 1, i - 1);
	tk->len = ft_strlen(tk->val);
	line += tk->len + 1;
	tk->type = TK_VAR;
	return (line);
}
