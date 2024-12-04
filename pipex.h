/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/04 16:26:32 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

// Functions
int		main(int argc, char **argv, char **envp);
int		perror_return(const char *message, int return_value);
void	perror_exit(const char *message);
void	create_pipe(char *file1, char *path_cmd1, char **cmd1,
			char *path_cmd2, char **cmd2, char *file2, char **envp);
char	*parse_command(const char *cmd);
char	**ft_split(char const *s, char c);
char	*allocate_string(size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *string);

#endif
