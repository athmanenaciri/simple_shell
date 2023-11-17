#include "exec.h"
#include "simpleshell.h"

void	next_combn(char *s)
{
	int	len;
	int	i;

	len = ft_strlen(s);
	i = 1;
	while (i < 9 && s[len - i] == '9')
		s[len - i++] = '0';
	if ((s[len - i] >= '0' && s[len - i] < '9'))
		s[len - i]++;
}

char	*get_tmp(void)
{
	char	*file;
	char	*heredoc_file;

	heredoc_file = "/tmp/.minishell-000000000";
	file = ft_strndup(heredoc_file, -1);
	if (file == NULL)
		return (NULL);
	while (1)
	{
		if (access(file, F_OK | W_OK | R_OK) == 0)
		{
			next_combn(file);
			continue;
		}
		break;
	}
	return (file);
}

void	run_here(t_list *node)
{
	char	*del;
	char	*tmp_doc;
	int		fd;
	char	*line;

	del = node->val;
	tmp_doc = get_tmp();
	fd = open(tmp_doc, O_WRONLY | O_CREAT, 0600);
	while (1)
	{
		line = readline("here> ");
		if (line == NULL || strncmp(line, del, ft_strlen(del) + 1) == 0)
			break;
		ft_putstr(fd, line);
		ft_putstr(fd, "\n");
		free(line);
	}
	free(line);
	close(fd);
	node->val = tmp_doc;
	free(del);
}

void	heredoc(t_list *list)
{
	t_list	*cur;

	cur = list;
	while (cur)
	{
		if (cur->type == TK_HEREDOC)
		{
			cur->next->next = get_next_node(cur->next);
			run_here(cur->next);
		}
		cur = cur->next;
	}
}
