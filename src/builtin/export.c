/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan < aabajyan@student.42yerevan.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:58:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/26 17:26:00 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_shell *self, t_node *node)
{
	(void)self;
	if (node && (node->kind & NODE_BINARY) != 0)
	{
	}
	printf("TODO: Implement export command\n");
	return (0);
}