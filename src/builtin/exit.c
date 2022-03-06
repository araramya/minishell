/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:59 by araramya          #+#    #+#             */
/*   Updated: 2022/03/06 18:53:46 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_exit_value(char *str)
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
	if (argc >= 2)
	{
		if (!ft_check_exit_value(argv[1]))
		{
			printf("bash: exit:  Not numeric argument\n");
			exit(255);
		}
		if (ft_atoi(argv[1]) > INT_MAX || ft_atoi(argv[1]) < INT_MIN)
		{
			printf("bash: exit: Not numeric argument\n");
			exit(255);
		}
		else if(argc > 2)
		{
			printf("bash: exit: Too many arguments\n");
			return (0);
		}
		exit(ft_atoi(argv[1]));
	}
	else
		exit(0);
	return (0);
}
