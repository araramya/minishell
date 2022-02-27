/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:58:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/27 17:37:08 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_shell *self, t_node *node)
{
	(void)self;
	(void)node;
	// if (node && (node->kind & NODE_BINARY) != 0)
	// 	self->env = env_set(self->env, node->lhs->value, node->rhs->value);
	return (0);
}
