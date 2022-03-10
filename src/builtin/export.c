/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 16:58:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/10 12:34:17 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(int argc, char **argv)
{
	char	**env;
	int		i;
	int		code;

	if (argc < 2)
	{
		env = env_to_string(true);
		argument_print(env, "declare -x ");
		argument_destroy(env);
	}
	i = 1;
	code = 0;
	while (i < argc)
		if (env_from_string(argv[i++]) && code == 0)
			code = 1;
	return (code);
}
