/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safernan <safernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:57:19 by safernan          #+#    #+#             */
/*   Updated: 2021/12/19 19:04:55 by safernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->p_arg->dead);
	if (i)
		ph->p_arg->stop = i;
	if (ph->p_arg->stop)
	{
		pthread_mutex_unlock(&ph->p_arg->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->p_arg->dead);
	return (0);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = current_time();
	while ((current_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
