#include "exec.h"
#include "simpleshell.h"

char	*double_quote(t_list *tk, char *line)
{
	int	i;

	i = 1;
	while (line[i] != '"' && line[i])
		i++;
	if (line[i] == '\0')
		tk->type = TK_ERROR;
	else
		tk->type = TK_TEMPLATE;
	tk->val = ft_strndup(line + 1, i - 1);
	tk->len = ft_strlen(tk->val);
	return (line + i + (line[i] != 0));
}

char	*single_quote(t_list *tk, char *line)
{
	int	i;

	i = 1;
	while (line[i] != '\'' && line[i])
		i++;
	if (line[i] == '\0')
		tk->type = TK_ERROR;
	else
		tk->type = TK_LITERAL;
	tk->val = ft_strndup(line + 1, i - 1);
	tk->len = ft_strlen(tk->val);
	return (line + i + (line[i] != 0));
}
