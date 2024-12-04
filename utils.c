/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:47:11 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/04 15:48:13 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// perror messages
void	perror_exit(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

int	perror_return(const char *message, int return_value)
{
	perror(message);
	return (return_value);
}

// Ft_strjoin
size_t	ft_strlen(char *string)
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

char	*ft_strjoin(char *s1, char *s2)
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
