#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int		ft_dup(t_list *cmds, int cmd_fd[], int fd_in);
int		ft_wait(pid_t pid);
int		is_dir(char *filename);
char	*get_command(t_ctx *ctx, char **words);
int		execute(t_cmd *cmds, t_ctx *ctx);
void	ft_exec_child(t_ctx *ctx, t_cmd *cmds, char *cmd, int cmd_fd[]);
void	execute_env(t_ctx *ctx, char **words);
void	execute_export(t_ctx *ctx, char **words);
void	execute_unset(t_ctx *ctx, char **words);
void	execute_pwd(t_ctx *ctx);
void	execute_cd(t_ctx *ctx, char **words);
void	execute_echo(char **words);
void	execute_exit(t_ctx *ctx, char **words);
void	print_var(char *var, int size);
char	*get_var(char *var, t_env *list_env, int n);
int		check_builins(char *s);
int		has_var(char *var, t_env *list_env, int n);
int		redirect(t_list *reds, int cmd_fd[]);
int		env_replace(t_env *env, void *new_value);

#endif
