/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:01:16 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/27 16:28:10 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argument_print(char **arguments)
{
	size_t	i;

	i = 0;
	while (arguments[i] != NULL)
		printf("%s\n", arguments[i++]);
}

void	argument_destroy(char **arguments)
{
	size_t	i;

	i = 0;
	while (arguments[i] != NULL)
		free(arguments[i++]);
	free(arguments);
}
