/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:22:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 20:31:52 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_string	demo;
	t_token		*demo2;

	string_init(&demo);
	string_push(&demo, "Hello");
	string_push(&demo, " ");
	string_push(&demo, getenv("USER"));
	string_push(&demo, "!");
	printf("%s\n", demo.buffer);
	string_deinit(&demo);
	demo2 = token_create(T_BEGIN, NULL);
	token_push(demo2, token_create(T_EOF, NULL));
	token_print(demo2);
	token_destroy(demo2);
	return (0);
}
