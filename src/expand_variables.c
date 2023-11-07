#include"../inc/minishell.h"
#include"../inc/exec.h"

int	expand_var(t_list *list, t_env *list_env)
{
	char	*val;

	val = get_var_or_null(list->val, list_env, list->len);
	if (val == NULL)
	{
		list->type = TK_IGNORE;
		return (1);
	}
	free(list->val);
	list->len = ft_strlen(val);
	list->val = ft_strndup(val, -1);
	if (list->val == NULL)
		return (0);
	list->type = TK_WORD;
	return (1);
}

int	fill(t_list *cur, char *res)
{
	cur->type = TK_WORD;
	if (res == NULL)
		return (1);
	free(cur->val);
	cur->val = res;
	cur->len = ft_strlen(cur->val);
	return (1);
}

int	expand_str(t_list *cur, t_env *list_env)
{
	int		n;
	char	*str;
	char	*res;
	char	*val;

	res = NULL;
	str = cur->val;
	while (*str != '\0')
	{
		if (*str == '$' && is_var(str + 1))
		{
			n = var_len(++str);
			val = get_var_or_null(str, list_env, n);
			if (ft_sjoin(&res, val, -1) == 0)
				return (0);
		}
		else
		{
			n = till(str, '$');
			if (ft_sjoin(&res, str, n) == 0)
				return (0);
		}
		str += n;
	}
	return (fill(cur, res));
}

int	expand(t_list *list, t_env *list_env)
{
	t_list	*cur;

	cur = list;
	while (cur)
	{
		if (cur->type == TK_VAR)
		{
			if (expand_var(cur, list_env) == 0)
				return (0);
		}
		else if (cur->type == TK_TEMPLATE)
		{
			if (expand_str(cur, list_env) == 0)
				return (0);
		}
		else if (cur->type == TK_LITERAL)
			cur->type = TK_WORD;
		cur = cur->next;
	}
	return (1);
}
