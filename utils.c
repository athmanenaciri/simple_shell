#include "exec.h"
#include "simpleshell.h"
#include <signal.h>
#include <sys/errno.h>
#include <sys/stat.h>

char	*find_path(char *path, char *cmd)
{
	int		size;
	char	*cmd_path;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	if (cmd[0] == '/' || cmd[0] == '.')
		return (ft_strndup(cmd, -1));
	if (cmd[0] == '\0')
		return (NULL);
	while (*path)
	{
		size = ft_strchar(path, ":");
		cmd_path = malloc(size + cmd_len + 2);
		if (cmd_path == NULL)
			return (NULL);
		ft_strncpy(cmd_path, path, size);
		ft_strncpy(cmd_path + size, "/", 1);
		ft_strncpy(cmd_path + size + 1, cmd, cmd_len);
		if (!access(cmd_path, F_OK))
			return (cmd_path);
		free(cmd_path);
		path += size + (path[size] == ':');
	}
	return (NULL);
}

char	*get_command(t_ctx *ctx, char **words)
{
	char	*path;
	char	*command;
	char	*cmd_path;

	if (words[0] == NULL)
		return (NULL);
	path = get_var_or_null("PATH", ctx->env, 4);
	if (!has_var("PATH", ctx->env, 4)
		|| check_builins(words[0]) || path == NULL)
		return (ft_strndup(words[0], -1));
	command = words[0];
	cmd_path = find_path(path, command);
	if (cmd_path == NULL)
	{
		ft_putstr(2, "minishell: ");
		ft_putstr(2, words[0]);
		ft_putstr(2, " command not found\n");
	}
	return (cmd_path);
}

int	ft_wait(pid_t pid)
{
	int	status;

	if (pid == -1)
	{
		g_exit_status = 1;
		perror("minishell: fork");
		kill(0, SIGTERM);
		while (waitpid(-1, 0, 0) != -1)
			;
		return (0);
	}
	if (waitpid(pid, &status, 0) == -1)
		status = 0;
	g_exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit: 3\n");
		g_exit_status = WTERMSIG(status) + 128;
	}
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		ft_putstr(2, "\n");
	return (1);
}

int	ft_dup(t_list *reds, int cmd_fd[], int fd_in)
{
	if (redirect(reds, cmd_fd) == 0)
		return (0);
	dup2(cmd_fd[0], 0);
	close(cmd_fd[0]);
	dup2(cmd_fd[1], 1);
	close(cmd_fd[1]);
	close(fd_in);
	return (1);
}

int	is_dir(char *filename)
{
	struct stat	st;

	errno = 0;
	stat(filename, &st);
	if (S_ISDIR(st.st_mode))
	{
		ft_putstr(2, "minishell: ");
		ft_putstr(2, filename);
		ft_putstr(2, ": ");
		ft_putstr(2, strerror(EISDIR));
		ft_putstr(2, "\n");
		return (1);
	}
	return (0);
}
