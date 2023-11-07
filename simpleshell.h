#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "list.h"
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include <sys/signal.h>
# include <termios.h>

typedef struct s_ctx
{
	t_env				*env;
	struct sigaction	old_act;
	struct termios		restore;
}	t_ctx;

t_list				*lexer(char *line);
int					exec_line(char *line, t_ctx *ctx);
t_list				*get_token(char *line);
int					ft_strlen(char *str);
char				*dolar(t_list *tk, char *line);
char				*double_quote(t_list	*tk, char *line);
int					is_space(char c);
int					is_redirection(t_list *node);
int					ft_strchar(char *line, char *str);
char				*single_quote(t_list *tk, char *line);
char				*string(t_list *tk, char *line);
char				*ft_strndup(char *s, int n);
int					ft_strncmp(char *s1, char *s2, unsigned int n);
char				*skip(char *line);
int					expand_var(t_list *list, t_env *list_env);
int					ft_strlcpy(char *dst, char *src, int dstsize);
char				*ft_strnjoin(char *s1, char *s2, int n);
int					expand(t_list *list, t_env *list_env);
int					is_var(char *str);
int					var_len(char *str);
int					till(char *str, char c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
t_list				*get_next_node(t_list	*list);
t_list				*ft_join(t_list	*list);
void				ft_putstr(int fd, char *s);
void				heredoc(t_list *list);
int					is_ok(t_list	*list);
t_env				*get_env_or_null(char *var, t_env *list_env, int n);
char				*get_var_or_null(char *var, t_env *list_env, int n);
int					add_env(t_ctx *ctx, char *value, int i);
void				ft_strncpy(char *dest, char *src, unsigned int size);
int					ft_sjoin(char **str1, char *str2, int i);
void				setup_signals(t_ctx *ctx);
void				destroy_one(t_list *node);
int					ft_dup(t_list *reds, int cmd_fd[], int fd_in);
int					execute_bultin(t_ctx *ctx, t_cmd *cmds, int cmd_fd[2]);
int					check_builins(char *s);
void				execute_echo(char **words);
void				execute_env(t_ctx *ctx, char **cmd);
int					env_replace(t_env *env, void *new_value);
void				execute_export(t_ctx *ctx, char **cmd);
void				execute_unset(t_ctx *ctx, char **cmd);
void				destroy_cmd(t_cmd *list);
struct sigaction	switch_handler(t_ctx *ctx, int echo);
int					is_redirection(t_list *node);
char				*get_var(char *var, t_env *list_env, int n);
void				execute_cd(t_ctx *ctx, char **words);
char				*get_val(char *s);
void				execute_pwd(t_ctx *ctx);
void				execute_exit(t_ctx *ctx, char **cmd);
void				destroy_env_one(t_env *env);
extern int			g_exit_status;
char				*ft_itoa(int nbr);
void				print_var(char *var, int size);

#endif
