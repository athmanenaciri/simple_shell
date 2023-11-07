#include "exec.h"
#include "simpleshell.h"

int	check_builins(char *s)
{
	return (ft_strncmp(s, "cd", 3) == 0
		|| ft_strncmp(s, "pwd", 4) == 0
		|| ft_strncmp(s, "export", 7) == 0
		|| ft_strncmp(s, "unset", 6) == 0
		|| ft_strncmp(s, "env", 4) == 0
		|| ft_strncmp(s, "echo", 5) == 0
		|| ft_strncmp(s, "exit", 5) == 0);
}

int	execute_bultin(t_ctx *ctx, t_cmd *cmds, int cmd_fd[2])
{
	char	**words;
	int		fd[2];

	cmd_fd[0] = -1;
	cmd_fd[1] = -1;
	fd[0] = dup(0);
	fd[1] = dup(1);
	words = cmds->words;
	if (ft_dup(cmds->redirections, cmd_fd, -1) == 0)
		return (1);
	if (ft_strncmp(words[0], "cd", 3) == 0)
		execute_cd(ctx, words);
	else if (ft_strncmp(words[0], "pwd", 4) == 0)
		execute_pwd(ctx);
	else if (ft_strncmp(words[0], "export", 7) == 0)
		execute_export(ctx, words);
	else if (ft_strncmp(words[0], "unset", 6) == 0)
		execute_unset(ctx, words);
	else if (ft_strncmp(words[0], "env", 4) == 0)
		execute_env(ctx, words);
	else if (ft_strncmp(words[0], "echo", 5) == 0)
		execute_echo(words);
	else if (ft_strncmp(words[0], "exit", 5) == 0)
		execute_exit(ctx, words);
	return (dup2(fd[0], 0), close(fd[0]), dup2(fd[1], 1), close(fd[1]));
}
