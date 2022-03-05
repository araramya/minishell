/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:10:34 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/05 17:09:25 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_get_flag(t_redirect_kind kind)
{
	int	flags;

	if ((kind & R_LEFT) != 0)
		return (O_RDONLY);
	flags = O_CREAT | O_WRONLY;
	if ((kind & R_DOUBLE_RIGHT) != 0)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

static int	shell_get_fd(t_redirect_kind kind)
{
	if ((kind & R_LEFT) != 0)
		return (STDIN_FILENO);
	return (STDOUT_FILENO);
}

int	shell_redirection(t_node *command)
{
	char	*tfile;
	char	**argv;
	int		argc;
	int		code;
	int		fd;

	tfile = expander_word(command->target);
	argv = expander_eval(command->arguments);
	argc = argument_size(argv);
	if (fork() == 0)
	{
		fd = open(tfile, shell_get_flag(command->redirect_kind), 0755);
		dup2(fd, shell_get_fd(command->redirect_kind));
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
