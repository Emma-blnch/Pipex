/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:47:11 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/04 16:36:24 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// perror messages
void	perror_exit(const char *message)
{
	errno = 0;
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	//errno = 0;
	exit(EXIT_FAILURE);
}

int	perror_return(const char *message, int return_value)
{
	errno = 0;
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));

	//errno = 0;
	return (return_value);
}

// Ft_strjoin
size_t	ft_strlen(const char *string)
{
	size_t	index;

	if (!string)
		return (0);
	index = 0;
	while (string[index])
		index++;
	return (index);
}

char	*allocate_string(size_t size)
{
	char	*result;

	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	return (result);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	if (!s1 && !s2)
		return (allocate_string(0));
	s1_len = 0;
	s2_len = 0;
	result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[s1_len])
	{
		result[s1_len] = s1[s1_len];
		s1_len++;
	}
	while (s2[s2_len])
	{
		result[s1_len + s2_len] = s2[s2_len];
		s2_len++;
	}
	result[s1_len + s2_len] = '\0';
	return (result);
}
