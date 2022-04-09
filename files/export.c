/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:05:27 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/08 23:50:42 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_name_func(char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	while (var[i] != '=' && var[i])
		i++;
	var_name = malloc(i + 1);
	i = -1;
	while (var[++i] != '=' && var[i])
		var_name[i] = var[i];
	var_name[i] = 0;
	return (var_name);
}

static int	valid_var_name(char	*var, t_minishell *minish)
{
	int		x;
	char	*var_name;

	x = -1;
	if (!var[0])
	{
		ft_putstr_fd("export: not valid in this context: ", 2);
		ft_putendl_fd(var, 2);
		minish->exit_status = 1;
		return (1);
	}
	var_name = var_name_func(var);
	while (var_name[++x])
	{
		if (!ft_isalnum(var_name[x]) && var_name[x] != '_'
			&& var_name[x] != '=')
		{
			ft_putstr_fd("export: not valid in this context: ", 2);
			ft_putendl_fd(var_name, 2);
			minish->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

static char	**export_check(t_minishell *minish, char **local_env)
{
	int		y;
	int		i;
	char	*var_name;

	y = 1;
	while (minish->options[y])
	{
		var_name = var_name_func(minish->options[y]);
		if (is_var(local_env, var_name))
		{
			if (!ft_strchr(minish->options[y], '='))
			{
				i = 0;
				while (local_env[i] && ft_strncmp(local_env[i], var_name \
				, ft_strlen(var_name_func(local_env[i]))))
					i++;
				minish->options[y] = ft_strdup(local_env[i]);
			}
			local_env = unset_var(var_name, local_env);
		}
		y++;
		free(var_name);
	}
	y = -1;
	return (local_env);
}

char	**local_to_new(t_minishell *minish, char **local_env,
	int y, char **new_env)
{
	int		x;

	x = -1;
	while (local_env[++x])
		new_env[x] = local_env[x];
	if (minish->options[y][ft_strlen(minish->options[y]) - 1] == '=')
		new_env[x] = ft_strjoin(ft_strdup(minish->options[y]), "\"\"");
	else
		new_env[x] = ft_strdup(minish->options[y]);
	new_env[++x] = 0;
	return (new_env);
}

char	**export(char	**local_env, t_minishell *minish)
{
	int		y;
	char	**new_env;

	minish->exit_status = 0;
	if (twod_array_len(minish->options) == 1)
		print_export(minish);
	if (twod_array_len(minish->options) > 1)
	{
		y = 0;
		local_env = export_check(minish, local_env);
		while (minish->options[++y])
		{
			if (valid_var_name(minish->options[y], minish))
				continue ;
			new_env = malloc((twod_array_len(local_env) + 2) * sizeof(char *));
			local_env = local_to_new(minish, local_env, y, new_env);
		}
	}
	return (local_env);
}
