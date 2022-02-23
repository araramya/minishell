/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:02:43 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/24 00:51:46 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Convrts binary kind to string
 * 
 * @param kind 
 * @return const char* 
 */
const char	*binary_kind_to_string(t_binary_kind kind)
{
	if ((kind & BINARY_NONE) != 0)
		return ("BINARY_NONE");
	if ((kind & BINARY_EQUALS) != 0)
		return ("BINARY_EQUALS");
	return ("BINARY_UNKNOWN");
}

/**
 * @brief Converts token kind to binary kind
 * 
 * @param kind 
 * @return t_binary_kind 
 */
t_binary_kind	token_kind_to_binary_kind(t_token_kind kind)
{
	if ((kind & T_EQUALS) != 0)
		return (BINARY_EQUALS);
	return (BINARY_NONE);
}
