/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/04 15:56:06 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

// Functions
int		main(int argc, char **argv, char **envp);
int		perror_return(const char *message, int return_value);
void	perror_exit(const char *message);
void	create_pipe(char *file1, char *path_cmd1, char **cmd1,
			char *path_cmd2, char **cmd2, char *file2, char **envp);
char	*parse_command(const char *cmd);
char	**ft_split(char const *s, char c);
char	*allocate_string(size_t size);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *string);

#endif
