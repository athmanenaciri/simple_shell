#include"../../inc/minishell.h"

t_list	*ft_lst_new(char *val)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->val = val;
	node->next = NULL;
	return (node);
}
