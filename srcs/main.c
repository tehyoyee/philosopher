/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:09 by taehykim          #+#    #+#             */
/*   Updated: 2022/09/06 16:30:10 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (argc != 5 && argc != 6)
		return (exit_error("incorrect argument number!"));
	if (init_rule(argc, argv, &rule))
		return (exit_error("argument"));
	run_thread(&rule);
}
