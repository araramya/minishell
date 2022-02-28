/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:27:00 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/28 15:04:43 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(t_env **env, int argc, char **argv)
{
	if (argc < 2)
		return (0);
	*env = env_unset(*env, argv[1]);
	return (0);
}
