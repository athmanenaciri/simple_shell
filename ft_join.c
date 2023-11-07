#include "exec.h"
#include "simpleshell.h"

t_list	*clean_node(t_list	*node)
{
	t_list	*next;

	if (node == NULL)
		return (node);
	free(node->val);
	node->val = NULL;
	node->len = -1;
	next = node->next;
	free(node);
	return (next);
}

int	ft_sjoin(char **str1, char *str2, int i)
{
	char	*res;

	if (str2 == NULL)
		return (1);
	res = ft_strnjoin(*str1, str2, i);
	free(*str1);
	*str1 = NULL;
	if (res == NULL)
		return (0);
	*str1 = res;
	return (1);
}

t_list	*get_next_node(t_list	*list)
{
	t_list	*cur;
	t_list	*first;
	int		is_space;

	first = list;
	cur = list->next;
	if (first->is_space || first->type != TK_WORD)
		return (cur);
	while (cur && (cur->type == TK_WORD || cur->type == TK_IGNORE))
	{
		if (cur->type == TK_IGNORE)
		{
			cur = cur->next;
			continue ;
		}
		ft_sjoin(&first->val, cur->val, -1);
		is_space = cur->is_space;
		first->next = clean_node(cur);
		if (is_space == 1)
			break ;
		cur = first->next;
	}
	if (cur == NULL)
		return (NULL);
	return (cur->next);
}

t_list	*ft_join(t_list	*list)
{
	t_list	*cur;

	cur = list;
	while (cur)
	{
		cur = get_next_node(cur);
	}
	return (list);
}
