/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan < aabajyan@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:27:00 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/26 17:26:03 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_shell *self, t_node *node)
{
	(void)self;
	if (node && node->value)
	{
	}
	printf("TODO: Implement unset command\n");
	return (0);
}
