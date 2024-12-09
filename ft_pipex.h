/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:47 by eblancha          #+#    #+#             */
/*   Updated: 2024/12/09 10:20:39 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H

# include "libft/libft.h"
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
}	t_pipe_args;

// Functions
int		main(int argc, char **argv, char **envp);
int		perror_return(const char *message, int return_value);
int		open_file(char *file, int in_or_out);
void	perror_exit(const char *message);
void	create_pipe(t_pipe_args *args);
void	execute_command(t_pipe_args *args, int infile, int outfile);
void	child(t_pipe_args *args, int infile, int outfile, int is_first_cmd);
char	*get_path(const char *cmd, char **envp);
// char	**ft_split(char const *s, char c);
// char	*allocate_string(size_t size);
// char	*ft_strjoin(const char *s1, const char *s2);
// size_t	ft_strlen(const char *string);

#endif
