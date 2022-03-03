/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:56 by araramya          #+#    #+#             */
/*   Updated: 2022/03/03 16:51:19 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(int argc, char **argv)
{
	bool	endline;
	int		i;

	i = 1;
	endline = true;
	if (argc > 1)
	{
		endline = (ft_strcmp("-n", argv[1]));
		if (!endline)
			i++;
		while (i < argc)
		{
			printf("%s", argv[i++]);
			if (i < argc)
				printf(" ");
		}
	}
	if (endline)
		printf("\n");
	return (0);
}
