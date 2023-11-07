#include "exec.h"
#include "simpleshell.h"

void	ft_lstadd_back_ev(t_env **list, t_env *jedida)
{
	t_env	*node;

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
