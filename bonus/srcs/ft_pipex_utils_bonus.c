/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ema_blnch <ema_blnch@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:44 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/26 16:59:02 by ema_blnch        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex_bonus.h"

void	init_args(t_pipe_args *args, int argc, char **argv, char **envp)
{
	int	i;

	args->here_doc = (ft_strncmp(argv[1], "here_doc", 8) == 0);
	args->file_in = args->here_doc ? NULL : argv[1];
	args->file_out = argv[argc - 1];
	args->cmd_count = argc - (args->here_doc ? 3 : 2);
	args->cmds = malloc(sizeof(char **) * args->cmd_count);
	args->paths = malloc(sizeof(char *) * args->cmd_count);
	args->envp = envp;
	if (!args->cmds || !args->paths)
		perror_exit("Error: malloc failed");
	i = 0;
	while (i < args->cmd_count)
	{
		args->cmds[i] = ft_split(argv[i + (args->here_doc ? 2 : 2)], ' ');
		args->paths[i] = get_path(args->cmds[i][0], envp);
		if (!args->paths[i])
		{
			free_args(args);
			perror_exit("Error: command not found");
		}
		i++;
	}
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

char	*get_path(const char *cmd, char **envp)
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
