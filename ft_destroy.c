#include "exec.h"
#include "simpleshell.h"

void	destroy_one(t_list *node)
{
	free(node->val);
	free(node);
}

void	destroy_list(t_list *list)
{
	t_list	*cur;
	t_list	*next;

	cur = list;
	while (cur)
	{
		next = cur->next;
		free(cur->val);
		free(cur);
		cur = next;
	}
}

void	destroy_env(t_env *list)
{
	t_env	*cur;
	t_env	*next;

	cur = list;
	while (cur)
	{
		next = cur->next;
		free(cur->val);
		free(cur);
		cur = next;
	}
}

void	destroy_cmd(t_cmd *list)
{
	int		i;
	t_cmd	*cur;
	t_cmd	*next;

	cur = list;
	while (cur)
	{
		next = cur->next;
		i = 0;
		while (cur->words[i])
			free(cur->words[i++]);
		free(cur->words);
		destroy_list(cur->redirections);
		free(cur);
		cur = next;
	}
}

void	destroy_env_one(t_env *env)
{
	free(env->val);
	free(env);
}
