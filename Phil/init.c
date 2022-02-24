/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:28:22 by rmicheli          #+#    #+#             */
/*   Updated: 2022/01/18 16:33:49 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

unsigned long long	get_total_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long)tv.tv_sec * 1000) + ((long)tv.tv_usec / 1000));
}

unsigned long long	get_time(t_data *data)
{
	return ((get_total_time() - data->time_to_start));
}

void	init_phil(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count_phil)
	{
		data->phil[i].index = i;
		data->phil[i].eat_count = 0;
		data->phil[i].data = data;
		data->phil[i].time_last_eat = 0;
		pthread_mutex_init(&data->phil[i].mutex, NULL);
		i++;
	}
}

void	data_init(t_data *data, int argc, char **argv)
{
	data->count_phil = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->count_eat = ft_atoi(argv[5]);
		if (data->count_eat == 0)
			exit (1);
	}
	else
		data->count_eat = 0;
	data->phil = NULL;
	data->dead = false;
	data->time_to_start = get_time(data);
	data->phil = (t_phil *)malloc(sizeof(t_phil) * data->count_phil);
	if (!data->phil)
		exit(1);
	init_phil(data);
}
