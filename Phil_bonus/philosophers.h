/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:28:03 by rmicheli          #+#    #+#             */
/*   Updated: 2022/01/15 14:46:41 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_phil
{
	pthread_t			*pth;
	pid_t				pid;
	int					index;
	int					lfork;
	int					rfork;
	int					eat_count;
	unsigned long long	time_last_eat;
	pthread_mutex_t		mutex;
	struct s_data		*data;
	unsigned long long	time_to_end_eating;
}						t_phil;

typedef struct s_data
{
	sem_t				*sem;
	sem_t				*dead1;
	sem_t				*write;
	sem_t				*eat;
	int					count_phil;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	time_to_start;
	int					count_eat;
	t_phil				*phil;
	int					*pid1;
}						t_data;

int					data_init(t_data *data, int argc, char **argv);
void				display_message(t_data *data, int number, char *str_err);
unsigned long long	get_time(t_data *data);
void				release_forks(t_data *data);
void				lock_forks(int number, t_data *data);
void				*monitor(void *phil);
void				free_data(t_data *data);
int					check_arg(int argc, char **argv);
bool				check_philo(t_phil *phil);
void				*monitor_eat_enough(void *data_v);
void				start_pr(t_data *data);
void				*phil_life(t_phil *phil);
int					ft_sleep(useconds_t n_milliseconds);
void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(const char *str);
unsigned long long	get_total_time(void);

#endif