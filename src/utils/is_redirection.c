#include"../../inc/minishell.h"

int	is_redirection(t_list *node)
{
	if (node->type == TK_REDIRICT_OUT
		|| node->type == TK_REDIRICT_IN
		|| node->type == TK_APPEND
		|| node->type == TK_HEREDOC)
		return (42);
	return (0);
}
