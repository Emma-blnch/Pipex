/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 12:05:10 by eblancha          #+#    #+#             */
/*   Updated: 2025/01/26 12:05:13 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_pipex.h"

void	perror_exit(const char *message)
{
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	errno = 0;
	exit(EXIT_FAILURE);
}

int	perror_return(const char *message, int return_value)
{
	if (errno != 0)
		perror(message);
	else
		write(STDERR_FILENO, message, ft_strlen(message));
	errno = 0;
	return (return_value);
}
