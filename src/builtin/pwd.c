/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:57:02 by araramya          #+#    #+#             */
/*   Updated: 2022/02/26 19:12:50 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int buildin_pwd(t_shell *self, t_node *node)
{
    (void)node;
    (void)self;
    char buffer[PATH_MAX];
    if (getcwd(buffer, PATH_MAX))
    {
        printf("%s\n", buffer);
        return (0);
    }
    return (1);
}