#include "../../inc/list.h"
#include"../../inc/minishell.h"

int	fill_token(t_list *node, char *val, int len, t_token_type type)
{
	node->val = val;
	node->len = len;
	node->type = type;
	return (len);
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r');
}

char	*tokonizer(t_list **head, char *line)
{
	t_list	*node;

	node = ft_lst_new(NULL);
	if (node == NULL)
		return (NULL);
	if (*line == '$' && is_var(line + 1))
		line = dolar(node, line);
	else if (*line == '|')
		line += fill_token(node, NULL, 1, TK_PIPE);
	else if (ft_strncmp(line, "<<", 2) == 0)
		line += fill_token(node, NULL, 2, TK_HEREDOC);
	else if (ft_strncmp(line, ">>", 2) == 0)
		line += fill_token(node, NULL, 2, TK_APPEND);
	else if (*line == '<')
		line += fill_token(node, NULL, 1, TK_REDIRICT_IN);
	else if (*line == '>')
		line += fill_token(node, NULL, 1, TK_REDIRICT_OUT);
	else if (*line == '"')
		line = double_quote(node, line);
	else if (*line == '\'')
		line = single_quote(node, line);
	else
		line = string(node, line);
	node->is_space = is_space(*line);
	return (ft_lstadd_back(head, node), skip(line));
}

t_list	*lexer(char *line)
{
	t_list	*head;

	head = NULL;
	while (*line)
	{
		line = tokonizer(&head, line);
		if (line == NULL)
			return (destroy_list(head), NULL);
	}
	return (head);
}
