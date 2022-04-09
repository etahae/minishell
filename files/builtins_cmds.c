/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:43:00 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/07 23:31:40 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char	**options, t_minishell *minish)
{
	int	x;

	if (options[0])
	{
		if (!ft_strncmp(options[1], "-n", 3))
			x = 1;
		else
			x = 0;
		while (options[++x])
		{
			ft_putstr_fd(options[x], minish->w_fd);
			write(1, " ", 1);
		}
		ft_putstr_fd(options[x], minish->w_fd);
	}
	if (ft_strncmp(options[1], "-n", 3))
		ft_putchar_fd('\n', minish->w_fd);
	minish->exit_status = 0;
}

static void	just_cd_error(char *path, t_minishell *minish)
{
	if (twod_array_len(minish->options) == 1)
	{
		path = var_value("HOME", minish->local_env);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			minish->exit_status = 1;
			return ;
		}
		chdir(path);
	}
	else
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(path, 2);
		minish->exit_status = 1;
	}
	return ;
}

void	cd(char *path, t_minishell *minish)
{
	minish->exit_status = 0;
	if (twod_array_len(minish->options) == 1
		|| twod_array_len(minish->options) > 2)
		return (just_cd_error(path, minish));
	else
	{
		if (f_or_d(path) != 'd')
		{
			ft_putstr_fd("error: no such file or directory: ", 2);
			ft_putendl_fd(path, 2);
			minish->exit_status = 2;
			return ;
		}
		if (access(path, X_OK))
		{
			ft_putstr_fd("error: permission denied: ", 2);
			ft_putendl_fd(path, 2);
			minish->exit_status = 13;
			return ;
		}
	}
	chdir(path);
}

void	env(char	**env, t_minishell *minish)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], minish->w_fd);
	minish->exit_status = 0;
}
