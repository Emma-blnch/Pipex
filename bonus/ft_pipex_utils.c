/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:44 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 16:08:29 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	init_args(t_pipe_args *args, char **argv, char **envp)
{
	args->file1 = argv[1];
	if (args->is_heredoc)
	{
		args->limiter = argv[2];
		args->file2 = argv[5];
		args->cmd1 = ft_split(argv[3], ' ');
		args->cmd2 = ft_split(argv[4], ' ');
	}
	else
	{
		args->limiter = NULL;
		args->file2 = argv[4];
		args->cmd1 = ft_split(argv[2], ' ');
		args->cmd2 = ft_split(argv[3], ' ');
	}
	args->envp = envp;
	args->exit_code = 0;
	if (!args->cmd1 || !args->cmd2)
	{
		free_args(args);
		perror_exit("Error: Command parsing failed");
	}
	args->path_cmd1 = get_path(args->cmd1[0], envp);
	args->path_cmd2 = get_path(args->cmd2[0], envp);
}

// get path to command
char	*build_full_path(const char *path, const char *cmd)
{
	char	*temp_path;
	char	*full_path;

	temp_path = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp_path, cmd);
	free(temp_path);
	return (full_path);
}

char	*find_path(const char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
		envp++;
	if (!*envp)
		return (NULL);
	paths = ft_split(*envp + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_split(paths);
	return (NULL);
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
		return (find_path(cmd, envp));
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
