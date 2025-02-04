/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:05:10 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/04 11:28:07 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	perror_exit(const char *message)
{
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

int	perror_return(const char *message, int return_value)
{
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	return (return_value);
}

// Free
void	free_args(t_pipe_args *args)
{
	if (args)
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
}
