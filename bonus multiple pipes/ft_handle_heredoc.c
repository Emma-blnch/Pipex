#include "ft_pipex.h"

void	handle_here_doc(t_pipe_args *args, char *limiter)
{
	int		pipe_fd[2];
	char	*line;

	// Création du pipe pour ici_doc
	if (pipe(pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed for here_doc");

	write(STDOUT_FILENO, "here_doc> ", 10);
	while ((line = get_next_line(STDIN_FILENO)))
	{
		// Comparaison avec le LIMITER
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "here_doc> ", 10);
	}
	close(pipe_fd[1]);

	// Stockage du pipe de lecture dans args
	args->pipe_fd[0] = pipe_fd[0];
}

