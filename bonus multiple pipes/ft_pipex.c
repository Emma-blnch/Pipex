/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:02 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/30 12:20:43 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// void	handle_here_doc(char *limiter)
// {
// 	pid_t	reader;
// 	int		pipe_fd[2];
// 	char	*line;

// 	if (pipe(pipe_fd) == -1)
// 		perror_exit("Error: Pipe creation failed for here_doc");
// 	reader = fork();
// 	if (reader == -1)
// 		perror_exit("Error: Fork failed for here_doc");
// 	if (reader == 0)
// 	{
// 		close(pipe_fd[0]);
// 		write(STDOUT_FILENO, "here_doc> ", 10);
// 		while ((line = get_next_line(STDIN_FILENO)))
// 		{
// 			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0 && line[ft_strlen(limiter)] == '\n')
// 			{
// 				free(line);
// 				break ;
// 			}
// 			write(pipe_fd[1], line, ft_strlen(line));
// 			free(line);
// 			write(STDOUT_FILENO, "here_doc> ", 10);
// 		}
// 		close(pipe_fd[1]);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		close(pipe_fd[1]);
// 		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
// 			perror_exit("Error: dup2 failed for here_doc");
// 		close(pipe_fd[0]);
// 		wait(NULL);
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	int	i;
// 	int	filein;
// 	int	fileout;

// 	if (argc >= 5)
// 	{
// 		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 		{
// 			i = 3;
// 			fileout = open_file(argv[argc - 1], 0);
// 			handle_here_doc(argv[2]);
// 		}
// 		else
// 		{
// 			i = 2;
// 			fileout = open_file(argv[argc - 1], 1);
// 			filein = open_file(argv[1], 2);
// 			if (dup2(filein, STDIN_FILENO) == -1)
// 				perror_exit("Error: dup2 failed for infile");
// 			close(filein);
// 		}
// 		while (i < argc - 2)
// 			child_process(argv[i++], envp);
// 		if (dup2(fileout, STDOUT_FILENO) == -1)
// 			perror_exit("Error: dup2 failed for outfile");
// 		close(fileout);
// 		execute(argv[argc - 2], envp);
// 	}
// 	usage_return();
// }

int	setup_here_doc(char **argv)
{
	handle_here_doc(argv[2]);
	return (3);
}

int	setup_files(int argc, char **argv, int *fileout)
{
	int	filein;

	*fileout = open_file(argv[argc - 1], 1);
	filein = open_file(argv[1], 2);
	if (dup2(filein, STDIN_FILENO) == -1)
		perror_exit("Error: dup2 failed for infile");
	close(filein);
	return (2);
}

void	execute_pipeline(int argc, char **argv, char **envp, int fileout)
{
	int	i;

	i = setup_files(argc, argv, &fileout);
	while (i < argc - 2)
		child_process(argv[i++], envp);
	if (dup2(fileout, STDOUT_FILENO) == -1)
		perror_exit("Error: dup2 failed for outfile");
	close(fileout);
	execute(argv[argc - 2], envp);
}

int	main(int argc, char **argv, char **envp)
{
	int	fileout = 0;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
			setup_here_doc(argv);
		else
			setup_files(argc, argv, &fileout);
		execute_pipeline(argc, argv, envp, fileout);
	}
	usage_return();
}
