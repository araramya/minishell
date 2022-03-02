/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:01:16 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/02 19:56:40 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argument_print(char **arguments, char *prefix)
{
	size_t	i;

	i = 0;
	while (arguments[i] != NULL)
		printf("%s%s\n", prefix, arguments[i++]);
}

void	argument_destroy(char **arguments)
{
	size_t	i;

	i = 0;
	while (arguments[i] != NULL)
		free(arguments[i++]);
	free(arguments);
}

int	argument_size(char **arguments)
{
	int	i;

	if (!arguments)
		return (0);
	i = 0;
	while (arguments[i] != NULL)
		++i;
	return (i);
}
