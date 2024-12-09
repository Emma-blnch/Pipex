/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:08:44 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/09 10:13:26 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

// perror messages
void	perror_exit(const char *message)
{
	errno = 0;
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	exit(EXIT_FAILURE);
}

int	perror_return(const char *message, int return_value)
{
	errno = 0;
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	return (return_value);
}

char *get_path(const char *cmd, char **envp)
{
    char **paths;
    char *full_path;
    char *temp_path;
    int i;

    while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
        envp++;
    if (!*envp)
        return (NULL);
    paths = ft_split(*envp + 5, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[++i])
    {
        temp_path = ft_strjoin(paths[i], "/");
        full_path = ft_strjoin(temp_path, cmd);
        free(temp_path);
        if (access(full_path, X_OK) == 0)
        {
            free(paths);
            return (full_path);
        }
        free(full_path);
    }
    free(paths);
    return (NULL);
}
