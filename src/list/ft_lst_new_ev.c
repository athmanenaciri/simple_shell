#include"../../inc/minishell.h"

t_env	*ft_lst_new_ev(char *val)
{
	t_env	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->val = val;
	node->next = NULL;
	return (node);
}
