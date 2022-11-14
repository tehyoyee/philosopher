/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:09 by taehykim          #+#    #+#             */
/*   Updated: 2022/11/14 16:11:49 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*checker(void *arg)
{
	int		i;
	t_rule	*rule;

	rule = (t_rule *)arg;
	i = 0;
	while (i++ < rule->num_philo)
		waitpid(-1, NULL, 0);
	sem_post(rule->sem_done);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_rule	rule;

	if (argc != 5 && argc != 6)
		return (exit_error("incorrect argument number"));
	if (init_rule(argc, argv, &rule))
		return (exit_error("incorrect argument"));
	pthread_create(&rule.checker, NULL, checker, &rule);
	pthread_detach(rule.checker);
	sem_wait(rule.sem_done);
	end_process(&rule);
}
