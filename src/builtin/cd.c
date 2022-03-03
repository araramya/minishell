/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:12 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/03/03 17:20:42 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(int argc, char **argv)
{
	char	*home;

	if (argc > 1)
		home = argv[1];
	else
		home = getenv("HOME");
	if (chdir(home) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(home, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}
