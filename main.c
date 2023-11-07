#include "exec.h"
#include "simpleshell.h"
#include <termios.h>

int	g_exit_status = 0;

void	ft_putstr(int fd, char *s)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
}

t_env	*get_env(char **env)
{
	t_env	*list_env;
	t_env	*node;
	int		i;

	list_env = NULL;
	i = 0;
	while (env[i])
	{
		node = ft_lst_new_ev(ft_strndup(env[i], -1));
		if (node == NULL)
			return (destroy_env(list_env), NULL);
		ft_lstadd_back_ev(&list_env, node);
		i++;
	}
	return (list_env);
}

void	handle_signal(t_ctx *ctx)
{
	struct termios	term;
	struct termios	restore;

	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
	ctx->restore = restore;
	setup_signals(ctx);
}

int	main(int ac, char **av, char **env)
{	
	char	*line;
	t_ctx	ctx;

	(void)ac;
	(void)av;
	rl_outstream = stderr;
	handle_signal(&ctx);
	ctx.env = get_env(env);
	if (ctx.env == NULL && env[0] != NULL)
		return (1);
	while (1)
	{
		line = readline("$> ");
		if (line == NULL)
		{
			ft_putstr(2, "exit\n");
			break ;
		}
		if (*line != '\0')
			add_history(line);
		exec_line(line, &ctx);
		free(line);
	}
	rl_clear_history();
	return (destroy_env(ctx.env), g_exit_status);
}
