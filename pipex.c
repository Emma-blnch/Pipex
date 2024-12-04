/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:46:59 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/04 15:53:54 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*parse_command(const char *cmd)
{
	char	*dir[];
	char	*full_path;
	char	*temp_path;
	int		i;

	i = 0;
	dir = {"/bin", "/user/bin", NULL};
	while (dir[i])
	{
		temp_path = ft_strjoin(dir[i], "/");
		full_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	create_pipe(char *file1, char *path_cmd1, char **cmd1,
				char *path_cmd2, char **cmd2, char *file2, char **envp)
{
	int	pipe_fd[2];
	int	pid1;
	int	pid2;
	int	infile;
	int	outfile;

	if (pipe(pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed\n");
	pid1 = fork();
	if (pid1 == -1)
		perror_exit("Error: Fork creation failed\n");
	if (pid1 == 0)
	{
		infile = open(file1, O_RDONLY);
		if (infile == -1)
			perror_exit("Error: cannot open file1\n");
		dup2(infile, stdin);
		dup2(pipe_fd[1], stdout);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(infile);
		execve(path_cmd1, cmd1, envp);
		perror_exit("Error: Execve failed\n");
	}
	pid2 = fork();
	if (pid2 == -1)
		perror_exit("Error: Fork creation failed\n");
	if (pid2 == 0)
	{
		outfile = open(file2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (outfile == -1)
			perror_exit("Error: cannot write in file2\n");
		dup2(pipe_fd[0], stdin);
		dup2(outfile, stdout);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(outfile);
		execve(path_cmd2, cmd2, envp);
		perror_exit("Error: Execve failed\n");
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
	{
		free(path_cmd1);
		free(path_cmd2);
		perror_return("Error: invalid command\n", 1);
	}
	create_pipe(argv[1], path_cmd1, cmd1, path_cmd2, cmd2, argv[4], envp);
	free(path_cmd1);
	free(path_cmd2);
	return (0);
}
