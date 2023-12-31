#include "exec.h"
#include "simpleshell.h"

int	is_nbr(char *str)
{
	int	i;

	i = 0;
	if (*str == '-')
		str++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	k;

	i = 0;
	n = 0;
	k = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = k * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	return (n * k);
}

void	execute_exit(t_ctx *ctx, char **cmd)
{
	int	size;

	(void)ctx;
	size = 0;
	while (cmd[size])
		size++;
	if (size == 1)
		exit(g_exit_status);
	if (size > 1 && !is_nbr(cmd[1]))
	{
		ft_putstr(2, "minishell: exit: ");
		ft_putstr(2, cmd[1]);
		ft_putstr(2, ": numeric argument required\n");
		exit(255);
	}
	else if (size > 2)
	{
		ft_putstr(2, "minishell: exit: too many arguments\n");
		return;
	}
	exit(ft_atoi(cmd[1]) & 0xff);
}
