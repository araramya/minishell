/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:26:44 by araramya          #+#    #+#             */
/*   Updated: 2022/03/10 13:42:10 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle signals by doing nothing
 * 
 * @param sig 
 */
void	signal_do_nothing(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

/**
 * @brief Handle signals by restarting the input
 * 
 * @param sig 
 */
void	signal_reprompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Handle a signal by exiting
 * 
 * @param sig 
 */
void	signal_interupt(int sig)
{
	write(1, "\n", 1);
	exit(sig);
}
