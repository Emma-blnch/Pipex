/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:44 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/29 16:49:23 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	cmd_handle(t_pipe_args *args, char **argv, char **envp)
{
	int	i;
	
	i = 0;
	while (i < args->nb_cmds)
	{
		if (args->is_heredoc)
			args->cmds[i] = ft_split(argv[i + 3], ' ');
		else
			args->cmds[i] = ft_split(argv[i + 2], ' ');
		args->paths_cmds[i] = get_path(args->cmds[i][0], envp);
		if (!args->cmds[i] || !args->paths_cmds[i])
			perror_exit("Error: Command parsing failed");
		i++;
	}
}

void	init_args(t_pipe_args *args, int argc, char **argv, char **envp)
{
	args->is_heredoc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (args->is_heredoc)
	{
		args->limiter = argv[2];
		args->nb_cmds = argc - 4;
	}
	else
	{
		args->limiter = NULL;
		args->nb_cmds = argc - 3;
	}
	args->file1 = argv[1];
	args->file2 = argv[argc - 1];
	args->envp = envp;
	args->exit_code = 0;
	args->cmds = malloc(sizeof(char **) * args->nb_cmds);
	args->paths_cmds = malloc(sizeof(char *) * args->nb_cmds);
	if (!args->cmds || !args->paths_cmds)
		perror_exit("Error: Memory allocation failed");
	cmd_handle(args, argv, envp);
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
