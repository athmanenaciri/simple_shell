#include"../../inc/minishell.h"

void	ft_lstadd_back(t_list **list, t_list *jedida)
{
	t_list	*node;

	node = *list;
	if (*list == NULL)
		*list = jedida;
	else
	{
		while (node->next)
			node = node->next;
		node->next = jedida;
	}
}
