#ifndef LIST_H
# define LIST_H

typedef enum e_token_type
{
	TK_WHITESPACE,
	TK_WORD,
	TK_TEMPLATE,
	TK_LITERAL,
	TK_REDIRICT_OUT,
	TK_REDIRICT_IN,
	TK_APPEND,
	TK_HEREDOC,
	TK_VAR,
	TK_PIPE,
	TK_EOF,
	TK_ERROR,
	TK_IGNORE
}	t_token_type;

typedef struct node
{
	char				*val;
	enum e_token_type	type;
	struct node			*next;
	int					is_space;
	int					len;
} t_list;

typedef struct s_env
{
	char			*val;
	struct s_env	*next;
} t_env;

typedef struct s_cmd
{
	char			*val;
	struct s_cmd	*next;
	t_list			*redirections;
	char			**words;
} t_cmd;

void	ft_lstadd_back(t_list **list, t_list *jedida);
void	ft_lstadd_back_ev(t_env **list, t_env *jedida);
int		ft_lstsize(t_list *lst);
t_list	*ft_lst_new(char *val);
t_env	*ft_lst_new_ev(char *val);
void	ft_lstadd_back_cmd(t_cmd **list, t_cmd *jedida);
void	destroy_list(t_list *list);
void	destroy_env(t_env *list);

#endif
