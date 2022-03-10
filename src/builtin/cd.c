/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:12 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/03/10 13:53:02 by aabajyan         ###   ########.fr       */
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
		error_print_code(NAME, "cd", NULL);
		return (1);
	}
	return (0);
}
