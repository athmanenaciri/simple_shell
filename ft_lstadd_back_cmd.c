#include "exec.h"
#include "simpleshell.h"

void	ft_lstadd_back_cmd(t_cmd **list, t_cmd *jedida)
{
	t_cmd	*node;

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
