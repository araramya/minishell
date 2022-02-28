/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:56 by araramya          #+#    #+#             */
/*   Updated: 2022/02/28 16:39:43 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	buildin_echo(int argc, char **argv)
{
	bool	endline;
	int		i;

	i = 1;
	if (argc > 1)
	{
		endline = (ft_strcmp("-n", argv[1]) != 0);
		if (!endline)
			i++;
		while (i < argc)
		{
			printf("%s", argv[i++]);
			if (i < argc)
				printf(" ");
		}
		if (endline)
			printf("\n");
	}
	return (0);
}
