/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:33:32 by taehykim          #+#    #+#             */
/*   Updated: 2022/11/14 16:12:25 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_person {
	int				id;
	int				eat_cnt;
	long long		eat_time_last;

	struct s_rule	*rule;
}			t_person;

typedef struct s_rule {
	int				*pids;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	long long		start_time;

	pthread_t		checker;
	sem_t			*sem_done;
	sem_t			*sem_forks;
	sem_t			*sem_eat_cnt;
	sem_t			*sem_time;

	struct s_person	*person;
}					t_rule;

void		destroy_sem(void);
void		run_process(t_person *p);
int			end_process(t_rule *rule);
void		show_status(t_rule *rule, char *str, int id);
int			exit_error(char *msg);
int			ft_atoi(const char *str);
int			init_rule(int argc, char **argv, t_rule *rule);
long long	get_time(void);
void		eating_time(t_person *p);
void		sleeping_time(t_person *p);
void		ft_free_mutex(t_rule *rule);

#endif
