/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 16:25:17 by hthomas           #+#    #+#             */
/*   Updated: 2022/01/14 14:02:46 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

void	display_message(t_data *data, int number, char *str_err)
{
	printf("%llu	%d number %s\n", get_time(data), number + 1, str_err);
}

int	check_philo(t_phil *philo)
{
	if (philo->data->time_to_die
		< get_time(philo->data) - philo->time_last_eat)
	{
		philo->data->dead = true;
		display_message(philo->data, philo->index, "died");
		pthread_mutex_unlock(&philo->mutex);
		free_data(philo->data);
		exit(1);
		return (1);
	}
	return (0);
}

void	monitor(t_data *data)
{
	int	i;

	while (1)
	{
		ft_sleep(9);
		i = 0;
		while (data->count_eat != 0 && i < data->count_phil)
		{
			if (data->phil[i].eat_count != data->count_eat)
				break ;
			i++;
		}
		if (i == data->count_phil)
			return ;
		i = 0;
		while (i < data->count_phil)
		{
			if (data->count_eat == 0
				|| data->phil[i].eat_count != data->count_eat)
				if (check_philo(&data->phil[i]) == 1)
					return ;
			i++;
		}
	}
}

void	free_data(t_data *data)
{
	int	i;

	if (data && data->phil)
	{
		i = 0;
		while (i < data->count_phil)
		{
			pthread_mutex_destroy(&data->phil[i].mutex);
			pthread_join(data->phil[i].thread, NULL);
			i++;
		}
		if (data->phil)
			free(data->phil);
	}
}
