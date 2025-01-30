/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:44 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/30 14:42:05 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	usage_return(void)
{
	ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 1);
	ft_putstr_fd("    ./pipex \"here_doc\" <LIMITER> <cmd> <cmd1> <...> <file>\n", 1);
	exit(EXIT_SUCCESS);
}

void	perror_exit(const char *message)
{
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

int	open_file(char *argv, int mode)
{
	int	file;

	file = 0;
	if (mode == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == 2)
		file = open(argv, O_RDONLY);
	if (file == -1)
	{
		perror(argv);
		exit(0);
	}
	return (file);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argv, ' ');
	path = get_path(cmd[0], envp);
	if (!path)	
	{
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		exit(127);
	}
	if (execve(path, cmd, envp) == -1)
	{
		perror(cmd[0]);
		if (errno == EACCES)
			exit(126);
		exit(127);
	}
}

pid_t	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		perror_exit("Error: Pipe creation failed");
	pid = fork();
	if (pid == -1)
		perror_exit("Error: Fork creation failed");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror_exit("Error: dup2 failed for pipe write");
		close(pipe_fd[1]);
		execute(argv, envp);
	}
	else
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
			perror_exit("Error: dup2 failed for pipe read");
		close(pipe_fd[0]);
	}
	return (pid);
}
