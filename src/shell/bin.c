/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:39:24 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/06 17:18:33 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*shell_bin_exists(char *path, char *filename)
{
	t_string	temp;

	string_init(&temp);
	string_push(&temp, path);
	string_push(&temp, "/");
	string_push(&temp, filename);
	if (access(temp.buffer, F_OK) == 0)
		return (string_freeze(&temp));
	string_deinit(&temp);
	return (NULL);
}

static char	*shell_find_bin(char *f)
{
	char	**paths;
	size_t	i;
	char	*found;

	if (!f)
		return (NULL);
	if ((f[0] == '/' || f[0] == '.') && access(f, F_OK) == 0)
		return (ft_strdup(f));
	paths = ft_split(env_get("PATH"), ':');
	i = 0;
	found = NULL;
	while (paths && paths[i] != NULL)
	{
		if (!found)
			found = shell_bin_exists(paths[i], f);
		free(paths[i++]);
	}
	free(paths);
	return (found);
}

int	shell_bin(char **argv)
{
	char	*path;
	int		code;
	char	**envp;

	path = shell_find_bin(argv[0]);
	if (!path)
	{
		printf("Command '%s' not found\n", argv[0]);
		return (1);
	}
	envp = env_to_string();
	if (fork() == 0)
	{
		signal_default();
		execve(path, argv, envp);
		perror("execvp failed");
		exit(1);
	}
	wait(&code);
	free(path);
	argument_destroy(envp);
	return (code);
}
