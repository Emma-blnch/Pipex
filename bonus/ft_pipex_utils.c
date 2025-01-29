/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:44 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 13:18:09 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

void	init_args(t_pipe_args *args, int argc, char **argv, char **envp)
{
	if (args->is_heredoc && argc == 6)
		args->pipe_fd[0] = get_heredoc(argv[1]); // TO DO
	else
		args->pipe_fd[0] = open(argv[1], O_RDONLY);
	if (args->pipe_fd[0] < 0)
		return (perror(argv[1]), 3);
	if (args->is_heredoc)
		args->pipe_fd[1] = open(argv[argc - 1], O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		args->pipe_fd[1] = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (args->pipe_fd[1] < 0)
		return (close(args->pipe_fd[0]), perror(argv[argc - 1]), 4);
	// args->cmd1 = ft_split(argv[2], ' ');
	// args->cmd2 = ft_split(argv[3], ' ');
	// args->envp = envp;
	// args->exit_code = 0;
	// if (!args->cmd1 || !args->cmd2)
	// {
	// 	free_args(args);
	// 	perror_exit("Error: Command parsing failed");
	// }
	// args->path_cmd1 = get_path(args->cmd1[0], envp);
	// args->path_cmd2 = get_path(args->cmd2[0], envp);
}

// get path to command
// char	*build_full_path(const char *path, const char *cmd)
// {
// 	char	*temp_path;
// 	char	*full_path;

// 	temp_path = ft_strjoin(path, "/");
// 	full_path = ft_strjoin(temp_path, cmd);
// 	free(temp_path);
// 	return (full_path);
// }

char	**find_path(char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!*envp)
		return (NULL);
	path = ft_split(*envp + 5, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		if (path[i][ft_strlen(path[i]) - 1] != '/')
		{
			temp = ft_strjoin(path[i], "/");
			if (!temp)
				return (ft_fsplit(path), NULL);
			free(path[i]);
			path[i] = temp;
		}
		i++;
	}
	//free_split(path);
	return (path);
}

char	*get_path(const char *cmd, char **envp)
{
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	else
		return (find_path(envp));
}

// Free
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
