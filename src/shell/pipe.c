/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:20:42 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/04 19:25:12 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_close_pfd(int pfd[2])
{
	close(pfd[0]);
	close(pfd[1]);
}

static void	shell_dup2(int pfd[2], int fd, int fd2)
{
	dup2(fd, fd2);
	shell_close_pfd(pfd);
}

static void	shell_destroy_and_exit(char **argv, int code)
{
	argument_destroy(argv);
	exit(code);
}

int	shell_pipe(t_node *command)
{
	int		pfd[2];
	int		code;
	char	**argv;
	int		argc;

	if (pipe(pfd) == -1)
		return (1);
	argv = expander_eval(command->arguments);
	argc = argument_size(argv);
	if (fork() == 0)
	{
		shell_dup2(pfd, pfd[1], STDOUT_FILENO);
		shell_destroy_and_exit(argv, shell_builtin(argc, argv));
	}
	wait(&code);
	if (fork() == 0)
	{
		shell_dup2(pfd, pfd[0], STDIN_FILENO);
		shell_destroy_and_exit(argv, shell_command(command->pipe));
	}
	shell_close_pfd(pfd);
	wait(&code);
	argument_destroy(argv);
	return (code);
}
