/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:41:40 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/09 08:23:14 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(char *input)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (input[++i])
	{
		if (input[i] == ' ')
			counter++;
		while (input[i] == ' ')
			i++;
		if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"' && input[i])
				i++;
		}
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i])
				i++;
		}
	}
	return (++counter);
}

void	twod_free(char	**array)
{
	int	x;

	x = -1;
	while (array[++x])
		free(array[x]);
	free(array);
}

void	print_error(char *str1, char *str2, t_minishell *minish, int val)
{
	if (str2)
	{
		ft_putstr_fd(str1, 2);
		ft_putendl_fd(str2, 2);
	}
	else
		ft_putendl_fd(str1, 2);
	minish->exit_status = val;
}

void	print_export(t_minishell *minish)
{
	int		y;

	y = 0;
	while (minish->local_env[y])
	{
		ft_putstr_fd("declare -x ", minish->w_fd);
		ft_putendl_fd(minish->local_env[y++], minish->w_fd);
	}
}
