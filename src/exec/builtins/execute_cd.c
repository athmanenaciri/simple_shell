#include "../../../inc/exec.h"

void	execute_pwd(t_ctx *ctx)
{
	char	*cwd;

	cwd = get_var_or_null("PWD", ctx->env, 3);
	if (cwd != NULL)
	{
		printf("%s\n", cwd);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		perror("minishell: ");
	else
		printf("%s\n", cwd);
	free(cwd);
}

int	_cd(t_ctx *ctx, char *path)
{
	char	*oldpwd;
	char	*pwd;
	t_env	*env;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		return (perror("minishell: "), 1);
	if (chdir(path) == -1)
	{
		ft_putstr(2, "minishell: cd: ");
		ft_putstr(2, path);
		return (perror(": "), free(oldpwd), 1);
	}
	if (!has_var("PWD", ctx->env, 3))
		add_env(ctx, "PWD=", 0);
	pwd = getcwd(NULL, 0);
	env = get_env_or_null("PWD", ctx->env, 3);
	env_replace(env, pwd);
	env = get_env_or_null("OLDPWD", env, 6);
	if (env == NULL)
		add_env(ctx, "OLDPWD=", 0);
	env = get_env_or_null("OLDPWD", ctx->env, 6);
	env_replace(env, oldpwd);
	return (free(pwd), free(oldpwd), 0);
}

void	execute_cd(t_ctx *ctx, char **words)
{
	char	*path;

	g_exit_status = 2;
	if (words[0] && words[1] == NULL)
	{
		path = get_var_or_null("HOME", ctx->env, 4);
		if (path == NULL)
		{
			ft_putstr(2, "HOME env not setted");
			return ;
		}
		g_exit_status = _cd(ctx, path);
	}
	else if (ft_strncmp(words[1], "-", 2) == 0)
	{
		path = get_var_or_null("OLDPWD", ctx->env, 6);
		if (path == NULL)
		{
			ft_putstr(2, "OLDPWD env not setted");
			return ;
		}
		g_exit_status = _cd(ctx, path);
	}
	else
		g_exit_status = _cd(ctx, words[1]);
}
