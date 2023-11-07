#include"../../inc/minishell.h"

char	*string(t_list *tk, char *line)
{
	int		i;

	i = ft_strchar(line, "$| '<>\"");
	while (line[i] == '$' && !is_var(line + i + 1))
		i++;
	tk->type = TK_WORD;
	tk->val = ft_strndup(line, i);
	tk->len = ft_strlen(tk->val);
	line += tk->len;
	return (line);
}
