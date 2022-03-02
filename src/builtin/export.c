/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:58:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/02 15:24:47 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	export_split(char *value, char **a, char **b)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(value);
	while (value[i] != '=' && value[i] != '\0')
		i++;
	if (value[i] == '\0')
		return (false);
	*a = ft_substr(value, 0, i++);
	*b = ft_substr(value, i, len - i);
	return (true);
}

int	builtin_export(int argc, char **argv)
{
	char	*a;
	char	*b;
	int		code;

	code = 0;
	if (argc < 2)
		env_print("declare -x ");
	else if (export_split(argv[1], &a, &b))
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
	}
	return (code);
}
