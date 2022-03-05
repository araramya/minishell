/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:12:53 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/05 10:36:00 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Converts token kind to redirect kind.
 * 
 * @param kind 
 * @return t_redirect_kind 
 */
t_redirect_kind	token_kind_to_redirect_kind(t_token_kind kind)
{
	if ((kind & T_LESS) != 0)
		return (R_LEFT);
	if ((kind & T_GREAT) != 0)
		return (R_RIGHT);
	if ((kind & T_DOUBLE_GREAT) != 0)
		return (R_DOUBLE_RIGHT);
	return (R_NONE);
}

/**
 * @brief Converts redirect kind to string.
 * 
 * @param kind 
 * @return const char* 
 */
const char	*redirect_kind_to_string(t_redirect_kind kind)
{
	if ((kind & R_NONE) != 0)
		return ("R_NONE");
	if ((kind & R_LEFT) != 0)
		return ("R_LEFT");
	if ((kind & R_RIGHT) != 0)
		return ("R_RIGHT");
	if ((kind & R_DOUBLE_RIGHT) != 0)
		return ("R_DOUBLE_RIGHT");
	return ("R_UNKNOWN");
}
