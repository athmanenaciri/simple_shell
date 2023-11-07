#include"../inc/minishell.h"

int	is_ok(t_list	*list)
{
	if (list == NULL)
		return (69);
	if (list->type == TK_PIPE)
		return (0);
	while (list)
	{
		if (list->type == TK_PIPE && list->next == NULL)
			return (0);
		if (is_redirection(list)
			&& (list->next == NULL || list->next->type == TK_PIPE))
			return (0);
		if (list->type == TK_PIPE && list->next->type == TK_PIPE)
			return (0);
		if (list->type == TK_ERROR)
			return (0);
		list = list->next;
	}
	return (1);
}
