/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:59 by araramya          #+#    #+#             */
/*   Updated: 2022/02/26 21:57:00 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_check_exit_value();

int buildin_exit(t_shell *self, t_node *node)
{
    //todo
    (void)self;
    exit(atoi(node->value));
}