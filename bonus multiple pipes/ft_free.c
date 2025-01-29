#include "ft_pipex.h"

void	free_args(t_pipe_args *args)
{
	int i;

	// Libération des commandes et chemins
	for (i = 0; i < args->nb_cmds; i++)
	{
		if (args->cmds[i])
			free_split(args->cmds[i]);
		if (args->paths_cmds[i])
			free(args->paths_cmds[i]);
	}

	// Libération de la mémoire pour les tableaux
	free(args->cmds);
	free(args->paths_cmds);

	// Libération des pipes
	for (i = 0; i < args->nb_cmds - 1; i++)
		free(args->pipes[i]);
	free(args->pipes);
}
