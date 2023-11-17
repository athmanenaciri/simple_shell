#include "exec.h"
#include "simpleshell.h"

int	count(t_list	*list)
{
	t_list	*cur;
	int		count;

	count = 0;
	cur = list;
	while (cur && cur->type != TK_PIPE)
	{
		if (is_redirection(cur))
			cur = cur->next;
		else
			count += (cur->type == TK_WORD);
		cur = cur->next;
	}
	return (count);
}

int	creat_cmd(t_cmd **cmd, t_list *list)
{
	int	i;

	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (0);
	i = count(list);
	(*cmd)->words = malloc(sizeof(char *) * (i + 1));
	if ((*cmd)->words == NULL)
		return (free(*cmd), 0);
	(*cmd)->words[i] = NULL;
	(*cmd)->next = NULL;
	(*cmd)->redirections = NULL;
	(*cmd)->val = NULL;
	return (1);
}

t_list	*convert2cmd(t_list	*list, t_cmd *cmd)
{
	t_list	*cur;	
	t_list	*next;
	int	i;

	cur = list;
	i = 0;
	while (cur && cur->type != TK_PIPE)
	{
		next = cur->next;
		if (cur->type == TK_WORD)
		{
			cmd->words[i++] = cur->val;
			free(cur);
		}
		else if (is_redirection(cur))
		{
			next = next->next;
			cur->next->next = NULL;
			ft_lstadd_back(&cmd->redirections, cur);
		}
		else
			destroy_one(cur);
		cur = next;
	}
	return (cur);
}

t_cmd	*filter_pipes(t_list *list)
{
	t_list	*cur;
	t_list	*next;
	t_cmd	*head;
	t_cmd	*cmd;

	cur = list;
	head = NULL;
	while (cur)
	{
		if (creat_cmd(&cmd, cur) == 0)
			return (NULL);
		next = convert2cmd(cur, cmd);
		ft_lstadd_back_cmd(&head, cmd);
		if (next == NULL)
			break;
		cur = next->next;
		destroy_one(next);
	}
	return (head);
}

int	exec_line(char *line, t_ctx *ctx)
{
	t_list	*list;
	t_cmd	*cmd;
	int		r;

	line = skip(line);
	list = lexer(line);
	if (list == NULL)
		return (1);
	if (!is_ok(list))
		return (printf("error\n"), 1);
	heredoc(list);
	if (expand(list, ctx->env) == 0)
		return (destroy_list(list), 1);
	if (ft_join(list) == 0)
		return (destroy_list(list), 1);
	cmd = filter_pipes(list);
	if (cmd == NULL)
		return (destroy_list(list), 1);
	switch_handler(ctx, 1);
	r = execute(cmd, ctx);
	destroy_cmd(cmd);
	return (switch_handler(ctx, 0), r);
}
