/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmicheli <rmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 15:27:13 by rmicheli          #+#    #+#             */
/*   Updated: 2022/01/15 17:21:48 by rmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	int i;
	i = number;
	sem_wait(data->sem);
	sem_wait(data->write);
	display_message(data, number, "has taken a fork");
	sem_post(data->write);
	sem_wait(data->sem);
	sem_wait(data->write);
	display_message(data, number, "has taken a fork");
	sem_post(data->write);
}

void	release_forks(t_data *data)
{
	sem_post(data->sem);
	sem_post(data->sem);
}
