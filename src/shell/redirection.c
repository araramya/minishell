/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 21:10:34 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/06 13:08:53 by aabajyan         ###   ########.fr       */
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
	int		code;
	int		fd;

	tfile = expander_word(command->rhs);
	if (fork() == 0)
	{
		fd = open(tfile, shell_get_flag(command->redirect_kind), 0755);
		dup2(fd, shell_get_fd(command->redirect_kind));
		close(fd);
		exit(shell_command(command->lhs));
	}
	wait(&code);
	if (ft_strncmp(tfile, SHELL_TMP, ft_strlen(SHELL_TMP)) == 0)
		unlink(tfile);
	free(tfile);
	return (code);
}
