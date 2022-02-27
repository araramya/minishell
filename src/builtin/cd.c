/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:12 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/02/27 19:17:06 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buildin_cd(int argc, char **argv)
{
	char	*home;

	if (argc > 1)
		home = argv[1];
	else
		home = getenv("HOME");
	if (chdir(home) != 0)
	{
		printf("cd: %s: No such file or directory\n", home);
		return (1);
	}
	return (0);
}
