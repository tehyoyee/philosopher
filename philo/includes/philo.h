/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:33:32 by taehykim          #+#    #+#             */
/*   Updated: 2022/09/06 16:33:33 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_person {
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_cnt;
	long long		eat_time_last;

	pthread_t		thread;
	struct s_rule	*rule;
}			t_person;

typedef struct s_rule {
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				death;
	int				eat_full;
	int				num_must_eat;
	long long		start_time;

	pthread_mutex_t	*fork;
	pthread_mutex_t	eat_cnt_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	time;
	pthread_mutex_t	*person_mutex;
	struct s_person	*person;
}			t_rule;

void		die_philo(t_rule *rule);
int			run_thread(t_rule *rule);
void		show_status(t_rule *rule, char *str, int id);
int			exit_error(char *msg);
int			ft_atoi(const char *str);
int			init_rule(int argc, char **argv, t_rule *rule);
long long	get_time(void);
void		eating_time(t_person *p);
void		sleeping_time(t_person *p);
void		ft_free_mutex(t_rule *rule);

#endif
