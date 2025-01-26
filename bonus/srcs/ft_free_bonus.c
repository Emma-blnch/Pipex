/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:05:26 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/26 16:51:48 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex_bonus.h"

void	free_args(t_pipe_args *args)
{
	int	i;

	i = 0;
	while (i < args->cmd_count)
	{
		if (args->cmds[i])
			free_split(args->cmds[i]);
		if (args->paths[i])
			free(args->paths[i]);
		i++;
	}
	free(args->paths);
	free(args->cmds);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
	split = NULL;
}
