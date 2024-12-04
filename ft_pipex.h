/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/04 17:26:57 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

//struct
typedef struct s_pipe_args
{
	char	*file1;
	char	*path_cmd;
	char	**cmd;
	char	*path_cmd2;
	char	**cmd2;
	char	**cmd1;
	char	*path_cmd1;
	char	*file2;
	char	**envp;
} t_pipe_args;

// Functions
int		main(int argc, char **argv, char **envp);
int		perror_return(const char *message, int return_value);
void	perror_exit(const char *message);
void	create_pipe(t_pipe_args *args);
void    execute_command(int infile, int outfile, t_pipe_args *args);
void    child_process_1(t_pipe_args *args, int pipe_fd[2]);
void    child_process_2(t_pipe_args *args, int pipe_fd[2]);
char	*parse_command(const char *cmd);
char	**ft_split(char const *s, char c);
char	*allocate_string(size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *string);

#endif
