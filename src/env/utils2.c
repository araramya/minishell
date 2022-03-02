/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 20:04:15 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/02 20:30:46 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	env_split(char *value, char **a, char **b)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(value);
	if (!value)
		return (false);
	while (value[i] != '=' && value[i] != '\0')
		i++;
	if (value[i] == '\0')
		return (false);
	*a = ft_substr(value, 0, i++);
	*b = ft_substr(value, i, len - i);
	return (true);
}

int	env_from_string(char *string)
{
	char	*a;
	char	*b;
	bool	code;

	code = 0;
	if (env_split(string, &a, &b))
	{
		if (ft_strchr(a, ' '))
		{
			printf("export: '%s' is not a valid identifier\n", a);
			code = 1;
		}
		else
			env_set(a, b);
		free(a);
		free(b);
		return (code);
	}
	return (code);
}
