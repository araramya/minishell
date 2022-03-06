/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 23:29:45 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/05 23:38:12 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*utils_get_tmp_path(void)
{
	static size_t	index = 0;
	t_string		string;

	string_init(&string);
	if (index + 1 >= SIZE_MAX)
		index = 0;
	string_push(&string, SHELL_TMP);
	string_move(&string, ft_itoa(index++));
	return (string_freeze(&string));
}
