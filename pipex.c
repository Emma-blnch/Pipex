/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:46:59 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/04 13:06:12 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(char *file1, char *path_cmd1, char **cmd1, char *path_cmd2, char **cmd2, char *file2, char **envp)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;
	int	infile;
	int	outfile;

	if (pipe(pipe_fd) == -1)
		perror_exit("Pipe creation failed\n");
	pid1 = fork();
	if (pid1 == -1)
		perror_exit("Fork creation failed\n");
	if (pid1 == 0)
	{
		infile = open(file1, O_RDONLY);
		if (infile == -1)
			perror_exit("Error: cannot open file1\n");
		dup2(infile, stdin);
		dup2(pipe_fd[1], stdout);
		close(pipe_fd[0]);
		execve(path_cmd1, cmd1, envp);
		perror_exit("Execve failed\n");
	}
	pid2 = fork();
	if (pid2 == -1)
		perror_exit("Fork creation failed\n");
	if (pid2 == 0)
	{
		outfile = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile == -1)
			perror_exit("Error: cannot write in file2\n");
		dup2(pipe_fd[0], stdin);
		dup2(outfile, stdout);
		close(pipe_fd[1]);
		execve(path_cmd2, cmd2, envp);
		perror_exit("Execve failed\n");
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);	
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmd1;
	char	**cmd2;
	char	*path_cmd1;
	char	*path_cmd2;

	if (argc < 5)
		perror_return("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
	if (access(argv[1], R_OK) == -1)
		perror_return("Error: File cannot be read\n");
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd1 || !cmd2)
		perror_return("Error: Command parsing failed\n", 1);
	path_cmd1 = parse_command(cmd1[0]);
	path_cmd2 = parse_command(cmd2[0]);
	if (!path_cmd1 || !path_cmd2)
		perror_return("Error: invalid command\n", 1);
	create_pipe(argv[1], path_cmd1, cmd1, path_cmd2, cmd2, argv[4], envp);
	return (0);
}
