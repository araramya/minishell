/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:56:12 by marvin@42.f       #+#    #+#             */
/*   Updated: 2022/02/26 20:09:36 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int buildin_cd(t_shell *self, t_node *node)
{
    (void)self;
    if(node)
    {
        if(chdir(node->value) != 0)
        {
            printf("cd: %s: No such file or directory\n", node->value );
            return (1);
        }
    }
    return (0);
}
