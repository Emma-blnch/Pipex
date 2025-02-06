/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:47:49 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/06 08:32:35 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

void	handle_here_doc(t_pipe_args *args, char *limiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed for here_doc");
	write(STDOUT_FILENO, "here_doc> ", 10);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "here_doc> ", 10);
		line = get_next_line(STDIN_FILENO);
	}
	close(pipe_fd[1]);
	args->pipe_fd[0] = pipe_fd[0];
}
