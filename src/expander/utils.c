/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:04:07 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/07 22:04:21 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander_merge(t_string *temp, t_node *node)
{
	t_node	*merge;
	char	*temp_value;

	if (!node)
		return (string_freeze(temp));
	merge = node->merged;
	while (merge)
	{
		temp_value = expander_simple_word(merge);
		if (temp_value)
		{
			string_push(temp, temp_value);
			free(temp_value);
		}
		merge = merge->merged;
	}
	return (string_freeze(temp));
}
