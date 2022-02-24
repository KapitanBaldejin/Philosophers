/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:29:08 by rmicheli          #+#    #+#             */
/*   Updated: 2022/01/18 12:39:27 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIL_H
# define PHIL_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>
# include "../printf/ft_printf.h"

typedef struct s_phil
{
	pthread_t			thread;
	int					index;
//	int					lfork;
//	int					rfork;
	int					eat_count;
	unsigned long long	time_last_eat;
	pthread_mutex_t		mutex;
	struct s_data		*data;
//	unsigned long long	time_to_end_eating;
}						t_phil;

typedef struct s_data
{
	int					count_phil;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	time_to_start;
	int					count_eat;
	t_phil				*phil;
	bool				dead;
}						t_data;

void				data_init(t_data *data, int argc, char **argv);
void				display_message(t_data *data, int number, char *str_err);
unsigned long long	get_time(t_data *data);
void				release_forks(int number, t_data *data);
void				lock_forks(int number, t_data *data);
void				monitor(t_data *data);
void				free_data(t_data *data);
int					check_arg(int argc, char **argv);
void				free_data(t_data *data);
void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(const char *str);
int					ft_sleep(useconds_t n_milliseconds);
int					ft_printf(const char *string, ...);
unsigned long long	get_total_time(void);

#endif