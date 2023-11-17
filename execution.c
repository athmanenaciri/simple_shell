#include <errno.h>
#include "exec.h"
#include "simpleshell.h"

char	**to_env(t_env *env)
{
	t_env	*cur;
	int		size;
	char	**words;

	size = 0;
	cur = env;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	words = malloc(sizeof(char *) * (size + 1));
	words[size] = NULL;
	while (size--)
	{
		words[size] = ft_strndup(env->val, -1);
		env = env->next;
	}
	return (words);
}

void	ft_exec_child(t_ctx *ctx, t_cmd *cmds, char *cmd, int cmd_fd[])
{
	int		fd_in;
	char	**env;

	fd_in = cmd_fd[2];
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_dup(cmds->redirections, cmd_fd, fd_in) == 0)
		exit(1);
	if (cmd == NULL
		&& cmds->redirections == NULL)
		exit(127);
	if (cmd == NULL)
		exit(0);
	if (check_builins(cmds->words[0]))
	{
		execute_bultin(ctx, cmds, cmd_fd);
		exit(g_exit_status);
	}
	env = to_env(ctx->env);
	execve(cmd, (char **)cmds->words, env);
	ft_putstr(2, "minishell: ");
	perror(cmd);
	exit(127 - (errno == EACCES));
}

int	run_cmd(t_ctx *ctx, t_cmd *cmd, int cmd_fd[], int fd[])
{
	char		*name;
	int			pid;
	static int	last_fd = -1;

	name = get_command(ctx, cmd->words);
	if (is_dir(name))
		return (free(name), -2);
	cmd_fd[0] = last_fd;
	cmd_fd[1] = -1;
	if (cmd->next != NULL)
	{
		if (pipe(fd))
			return (free(name), -2);
		last_fd = fd[0];
		cmd_fd[1] = fd[1];
	}
	cmd_fd[2] = fd[0];
	pid = fork();
	if (pid == 0)
		ft_exec_child(ctx, cmd, name, cmd_fd);
	close(cmd_fd[0]);
	close(cmd_fd[1]);
	if (!cmd->next)
		last_fd = -1;
	return (free(name), pid);
}

int	execute(t_cmd *cmds, t_ctx *ctx)
{
	int	fd[2];
	int	cmd_fd[3];
	int	pid;

	g_exit_status = 0;
	pid = -2;
	if (cmds && !cmds->next && cmds->words[0] != NULL
		&& check_builins(cmds->words[0]))
		return (execute_bultin(ctx, cmds, cmd_fd), 1);
	fd[0] = -1;
	fd[1] = -1;
	while (cmds)
	{
		pid = run_cmd(ctx, cmds, cmd_fd, fd);
		if (pid == -1)
			break;
		cmds = cmds->next;
	}
	return (ft_wait(pid));
}
