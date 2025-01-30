#include "ft_pipex.h"

static void	read_here_doc(char *limiter, int write_fd)
{
	char	*line;

	write(STDOUT_FILENO, "here_doc> ", 10);
	while ((line = get_next_line(STDIN_FILENO)))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "here_doc> ", 10);
	}
	close(write_fd);
	exit(EXIT_SUCCESS);
}

static void	child_here_doc(int *pipe_fd, char *limiter)
{
	pid_t	reader;

	reader = fork();
	if (reader == -1)
		perror_exit("Error: Fork failed for here_doc");
	if (reader == 0)
	{
		close(pipe_fd[0]);
		read_here_doc(limiter, pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror_exit("Error: dup2 failed for here_doc");
		close(pipe_fd[0]);
		wait(NULL);
	}
}

void	handle_here_doc(char *limiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed for here_doc");
	child_here_doc(pipe_fd, limiter);
}

