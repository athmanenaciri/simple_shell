#include "exec.h"
#include "simpleshell.h"

int	env_replace(t_env *env, void *new_value)
{
	int		size;
	char	*new;

	size = ft_strchar(env->val, "=");
	if (new_value == NULL)
		return (1);
	new = malloc((size + ft_strlen(new_value) + 2));
	if (new == NULL)
		return (0);
	ft_strncpy(new, env->val, size);
	ft_strncpy(new + size, "=", size);
	ft_strncpy(new + size + 1, new_value, ft_strlen(new_value));
	free(env->val);
	env->val = new;
	return (1);
}

int	search_and_replace(t_ctx *ctx, char *var)
{
	int		i;
	t_env	*e;

	g_exit_status = 1;
	if (!is_var(var) || (var[var_len(var)] != '\0' && var[var_len(var)] != '='
			&&!(var[var_len(var)] == '+' && var[var_len(var) + 1] == '=')))
		return (ft_putstr(2, "syntax error\n"), 0);
	g_exit_status = 0;
	i = ft_strchar(var, "+=");
	if (!has_var(var, ctx->env, i))
		return (add_env(ctx, var, i), 1);
	if (var[i] == '\0')
		return (1);
	e = get_env_or_null(var, ctx->env, i);
	if (var[i] == '+')
	{
		e->val = ft_strnjoin(e->val, get_val(var), -1);
		return (1);
	}
	env_replace(e, get_val(var));
	return (1);
}

void	execute_export(t_ctx *ctx, char **cmd)
{
	int		j;
	t_env	*env;

	env = ctx->env;
	if (cmd[1] == NULL)
	{
		while (env)
		{
			print_var(env->val, ft_strchar(env->val, "="));
			env = env->next;
		}
	}
	else
	{
		j = 1;
		while (cmd[j])
		{
			search_and_replace(ctx, cmd[j]);
			j++;
		}
	}
}

int	env_to_cmp(char *cmd, t_env *env)
{
	int	n;

	n = ft_strlen(cmd);
	return (!ft_strncmp(cmd, env->val, n)
		&& (env->val[n] == '='
			|| env->val[n] == '\0'));
}

void	execute_unset(t_ctx *ctx, char **cmd)
{
	t_env	*env;
	t_env	*last;
	t_env	*next;

	last = NULL;
	while (*++cmd)
	{
		env = ctx->env;
		while (env)
		{
			if (env_to_cmp(*cmd, env))
			{
				next = env->next;
				if (last == NULL)
					ctx->env = next;
				else
					last->next = next;
				destroy_env_one(env);
				break ;
			}
			last = env;
			env = env->next;
		}
	}
}
