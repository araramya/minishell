/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:57:02 by araramya          #+#    #+#             */
/*   Updated: 2022/03/08 01:06:05 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", buffer);
	return (0);
}
