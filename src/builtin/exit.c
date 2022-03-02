/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:59 by araramya          #+#    #+#             */
/*   Updated: 2022/03/02 17:08:14 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_exit_value(void);

int	builtin_exit(int argc, char **argv)
{
	if (argc > 1)
		exit(atoi(argv[1]));
	else
		exit(0);
}
