/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:05:26 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:28 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

void	free_args(t_pipe_args *args)
{
	if (args->path_cmd1)
		free(args->path_cmd1);
	if (args->path_cmd2)
		free(args->path_cmd2);
	if (args->cmd1)
		free_split(args->cmd1);
	if (args->cmd2)
		free_split(args->cmd2);
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
