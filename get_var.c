#include "exec.h"
#include "simpleshell.h"

t_env	*get_env_or_null(char *var, t_env *list_env, int n)
{
	t_env	*cur;

	cur = list_env;
	while (cur)
	{
		if (ft_strncmp(var, cur->val, n) == 0
			&& (cur->val[n] == '=' || cur->val[n] == '\0'))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

char	*get_var_or_null(char *var, t_env *list_env, int n)
{
	t_env	*cur;

	if (ft_strncmp(var, "?", 2) == 0)
		return (ft_itoa(g_exit_status));
	cur = list_env;
	while (cur)
	{
		if (ft_strncmp(var, cur->val, n) == 0
			&& (cur->val[n] == '=' || cur->val[n] == '\0'))
			return (cur->val + n + 1);
		cur = cur->next;
	}
	return (NULL);
}

int	has_var(char *var, t_env *list_env, int n)
{
	return (get_var_or_null(var, list_env, n) != NULL);
}

char	*get_var(char *var, t_env *list_env, int n)
{
	char	*res;

	res = get_var_or_null(var, list_env, n);
	if (res == NULL)
		return (ft_strndup("", -1));
	else
		return (ft_strndup(res, -1));
}
