/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:59 by araramya          #+#    #+#             */
/*   Updated: 2022/03/08 01:03:41 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_check(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(int argc, char **argv)
{
	long	value;

	if (argc >= 2)
	{
		value = ft_atoi(argv[1]);
		if (!exit_check(argv[1]) || value > INT_MAX || value < INT_MIN)
		{
			ft_putstr_fd("minishell: exit: Not numeric argument\n", 2);
			return (2);
		}
		return (value);
	}
	return (0);
}
