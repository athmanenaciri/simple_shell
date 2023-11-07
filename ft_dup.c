#include "exec.h"
#include "simpleshell.h"

int	red_out(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[1]);
	fd = open(reds->next->val, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		perror("minishell");
		return (0);
	}
	cmd_fd[1] = fd;
	return (1);
}

int	red_in(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[0]);
	fd = open(reds->next->val, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(2, "minishell: ");
		perror(reds->next->val);
		return (0);
	}
	cmd_fd[0] = fd;
	return (1);
}

int	red_here(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[0]);
	fd = open(reds->next->val, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr(2, "minishell: ");
		perror(reds->next->val);
		return (0);
	}
	unlink(reds->next->val);
	cmd_fd[0] = fd;
	return (1);
}

int	red_append(t_list *reds, int cmd_fd[], int fd)
{
	close(cmd_fd[1]);
	fd = open(reds->next->val, O_APPEND | O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr(2, "minishell: ");
		perror(reds->next->val);
		return (0);
	}
	cmd_fd[1] = fd;
	return (1);
}

int	redirect(t_list *reds, int cmd_fd[])
{
	int	fd;
	int	result;

	fd = 0;
	result = 1;
	while (result && reds)
	{
		if (reds->type == TK_REDIRICT_OUT)
			result = red_out(reds, cmd_fd, fd);
		else if (reds->type == TK_REDIRICT_IN)
			result = red_in(reds, cmd_fd, fd);
		else if (reds->type == TK_HEREDOC)
			result = red_here(reds, cmd_fd, fd);
		else if (reds->type == TK_APPEND)
			result = red_append(reds, cmd_fd, fd);
		reds = reds->next;
	}
	return (result);
}
