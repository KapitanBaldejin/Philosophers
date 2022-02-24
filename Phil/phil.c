/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:46:48 by rmicheli          #+#    #+#             */
/*   Updated: 2022/01/19 18:27:38 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	ft_sleep(useconds_t n_milliseconds)
{
	useconds_t		before;
	useconds_t		after;

	before = get_total_time();
	after = before;
	while (after - before < n_milliseconds)
	{
		if (usleep(500) == -1)
			return (-1);
		after = get_total_time();
	}
	return (0);
}

void	eat(int number, t_data *data)
{
//	int	time_to_end_eating;

	if (data->dead == false)
		lock_forks(number, data);
	if (data->dead == false)
		display_message(data, number, "is eating");
	data->phil[number].eat_count++;
	data->phil[number].time_last_eat = get_time(data);
//	time_to_end_eating = data->phil[number].time_last_eat + data->time_to_eat;
	ft_sleep(data->time_to_eat);
	release_forks(number, data);
}

void	sleep_phil(t_data *data, int number)
{
//	int	time_to_end_sleeping;

	display_message(data, number, "is sleeping");
	ft_sleep(data->time_to_sleep);
}

void	*phil_life(void *phil1)
{
	t_phil	*phil;

	phil = (t_phil *)phil1;
	while (phil->data->dead == false)
	{
		if (phil->data->dead == false)
			eat(phil->index, phil->data);
		if (phil->data->count_eat != 0
			&& phil->eat_count == phil->data->count_eat)
			return (NULL);
		if (phil->data->dead == false)
			sleep_phil(phil->data, phil->index);
		if (phil->data->dead == false)
			display_message(phil->data, phil->index, "is thinking");
	}
	return (NULL);
}

bool	start_pr(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_phil)
	{
		if (pthread_create(&data->phil[i].thread, NULL,
				&phil_life, &(data->phil[i])))
			return (false);
		i= i + 2;
	}
	ft_sleep(1);
	i = 1;
	while (i < data->count_phil)
	{
		if (pthread_create(&data->phil[i].thread, NULL,
				&phil_life, &(data->phil[i])))
			return (false);
		i = i + 2;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error: arguments are entered incorrectly\n", 1);
		return (0);
	}
	if (check_arg(argc, argv) == 0)
	{
		ft_putstr_fd("Error: invalid value\n", 1);
		return (0);
	}
	data_init(&data, argc, argv);
	start_pr(&data);
	monitor(&data);
	ft_sleep(1);
	free_data (&data);
	return (0);
}
