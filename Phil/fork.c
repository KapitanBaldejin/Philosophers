/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:28:25 by rmicheli          #+#    #+#             */
/*   Updated: 2022/01/14 14:08:01 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phil.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	i1;
	int	y;

	y = 0;
	i1 = 0;
	i = 1;
	if (argc == 2)
		i = 0;
	while (argv[i])
	{
		y = 0;
		i1 = 0;
		while (argv[i][i1])
		{
			if (argv[i][i1] < '0' || argv[i][i1] > '9')
				return (0);
			i1++;
		}
		i++;
	}
	return (1);
}

void	lock_forks(int number, t_data *data)
{
	pthread_mutex_lock(&data->phil[number].mutex);
	if (data->dead == false)
		display_message(data, number, "has taken a fork");
	if (number == data->count_phil - 1)
		pthread_mutex_lock(&data->phil[0].mutex);
	else
		pthread_mutex_lock(&data->phil[number + 1].mutex);
	if (data->dead == false)
		display_message(data, number, "has taken a fork");
}

void	release_forks(int number, t_data *data)
{
	pthread_mutex_unlock(&data->phil[number].mutex);
	if (number == data->count_phil - 1)
		pthread_mutex_unlock(&data->phil[0].mutex);
	else
		pthread_mutex_unlock(&data->phil[number + 1].mutex);
}
