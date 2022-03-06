/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:22:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/06 16:35:14 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Main function.
 * 
 * @return int 
 */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell_init(&shell, envp);
	if (argc > 2 && ft_strcmp(argv[1], "-c") == 0)
		return (shell_execute(&shell, ft_strdup(argv[2])));
	signal_shell();
	return (shell_start(&shell));
}
