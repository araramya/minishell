/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:22:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 19:46:14 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_string	demo;

	string_init(&demo);
	string_push(&demo, "Hello");
	string_push(&demo, " ");
	string_push(&demo, getenv("USER"));
	string_push(&demo, "!");
	printf("%s\n", demo.buffer);
	string_deinit(&demo);
	return (0);
}
