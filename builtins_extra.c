#include "exec.h"
#include "simpleshell.h"

void	print_words(int i, char **words)
{
	while (words[i])
	{
		ft_putstr(1, words[i]);
		if (words[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	execute_echo(char **words)
{
	int		i;
	char	*cmd;

	cmd = (char *)words[1];
	i = (cmd && cmd[0] == '-');
	if (cmd)
	{
		while (cmd && cmd[i] == 'n')
			i++;
		if (cmd[i] != 'n' && cmd[i])
		{
			print_words(1, words);
			write(1, "\n", 1);
		}
		else
			print_words(2, words);
	}
	else
		write(1, "\n", 1);
}

void	execute_env(t_ctx *ctx, char **cmd)
{
	t_env	*env;

	if (cmd[1])
	{
		g_exit_status = 1;
		return ;
	}
	env = ctx->env;
	while (env)
	{
		printf("%s\n", (char *)env->val);
		env = env->next;
	}
	g_exit_status = 0;
}

char	*get_val(char *s)
{
	int	u;

	u = ft_strchar(s, "+=");
	if (s[u] == '+')
		u++;
	if (s[u] == '=')
		u++;
	return (s + u);
}

int	add_env(t_ctx *ctx, char *value, int i)
{
	t_env	*node;
	char	*new;

	if (value[i] != '+')
		value = ft_strndup(value, -1);
	else
	{
		new = malloc(sizeof(char) * ft_strlen(value));
		ft_strncpy(new, value, i);
		ft_strncpy(new + i, value + i + 1, ft_strlen(value + i));
		value = new;
	}
	node = ft_lst_new_ev(value);
	if (node == NULL)
		return (0);
	ft_lstadd_back_ev(&ctx->env, node);
	return (1);
}
