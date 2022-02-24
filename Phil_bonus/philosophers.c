/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 15:46:48 by rmicheli          #+#    #+#             */
/*   Updated: 2022/01/20 20:33:20 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	free_data(t_data *data)
{
	free(data->pid1);
	if (data->phil)
		free(data->phil);
	sem_unlink("FORK");
	sem_unlink("DEAD");
	sem_unlink("WRITE");
	sem_unlink("EAT");
}

void	eat(int number, t_data *data)
{
	int	time_to_end_eating;

	lock_forks(number, data);
	sem_wait(data->write);
	display_message(data, number, "is eating");
	sem_post(data->write);
	data->phil->eat_count++;
	data->phil->time_last_eat = get_time(data);
	time_to_end_eating = data->phil->time_last_eat + data->time_to_eat;
	ft_sleep(data->time_to_eat);
	release_forks(data);
}

void	sleep_phil(t_data *data, int number)
{
	int i;

	i = number;
	sem_wait(data->write);
	display_message(data, number, "is sleeping");
	sem_post(data->write);
	ft_sleep(data->time_to_sleep);
}

void	*phil_life(t_phil *phil)
{
	pthread_t	pth;

	pthread_create(&pth, NULL, &monitor, phil);
	while (1)
	{
		eat(phil->index, phil->data);
		sleep_phil(phil->data, phil->index);
		sem_wait(phil->data->write);
		display_message(phil->data, phil->index, "is thinking");
		sem_post(phil->data->write);
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;
	pthread_t	tid;

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
	if (data_init(&data, argc, argv) == 1)
		return (0);
	start_pr(&data);
	if (pthread_create(&tid, NULL, &monitor_eat_enough, &data) != 0)
		return (1);
	i = 0;
	sem_wait(data.dead1);
	while (i < data.count_phil)
		kill(data.phil[i++].pid, SIGTERM);
	free_data(&data);
	return (0);
}
