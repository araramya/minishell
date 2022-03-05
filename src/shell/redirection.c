/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:10:34 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/05 10:35:27 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_get_flag(t_redirect_kind kind)
{
	int	flags;

	flags = O_CREAT | O_WRONLY;
	if ((kind & R_DOUBLE_RIGHT) != 0)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

static int	shell_redirection_right(t_node *command)
{
	int		fd;
	char	*tfile;
	char	**argv;
	int		argc;
	int		code;

	tfile = expander_word(command->target);
	argv = expander_eval(command->arguments);
	argc = argument_size(argv);
	if (fork() == 0)
	{
		fd = open(tfile, shell_get_flag(command->redirect_kind), 0755);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		code = shell_builtin(argc, argv);
		argument_destroy(argv);
		free(tfile);
		exit(code);
	}
	wait(&code);
	argument_destroy(argv);
	free(tfile);
	return (0);
}

int	shell_redirection(t_node *command)
{
	char	*tfile;
	char	**argv;
	int		argc;
	int		code;
	int		fd;

	if ((command->redirect_kind & (R_DOUBLE_RIGHT | R_RIGHT)) != 0)
		return (shell_redirection_right(command));
	tfile = expander_word(command->target);
	argv = expander_eval(command->arguments);
	argc = argument_size(argv);
	if (fork() == 0)
	{
		fd = open(tfile, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
		code = shell_builtin(argc, argv);
		argument_destroy(argv);
		free(tfile);
		exit(code);
	}
	wait(&code);
	argument_destroy(argv);
	free(tfile);
	return (code);
}
