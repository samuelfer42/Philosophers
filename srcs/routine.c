/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safernan <safernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:57:19 by safernan          #+#    #+#             */
/*   Updated: 2021/12/19 19:18:44 by safernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	write_status(char *str, t_philo *ph)
{
	long int		time;

	time = -1;
	time = current_time() - ph->p_arg->start_time;
	if (time >= 0 && time <= INT_MAX && !check_death(ph, 0))
	{
		printf("%ld ", time);
		printf("Philo %d %s", ph->id, str);
	}
}

void	sleeping(t_philo *ph)
{
	pthread_mutex_lock(&ph->p_arg->write_mutex);
	write_status("is sleeping\n", ph);
	pthread_mutex_unlock(&ph->p_arg->write_mutex);
	ft_usleep(ph->p_arg->time_to_sleep);
}

void	think(t_philo *ph)
{
	pthread_mutex_lock(&ph->p_arg->write_mutex);
	write_status("is thinking\n", ph);
	pthread_mutex_unlock(&ph->p_arg->write_mutex);
}

void	eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->p_arg->write_mutex);
	write_status("is eating\n", ph);
	pthread_mutex_lock(&ph->p_arg->time_eat);
	ph->ms_eat = current_time();
	pthread_mutex_unlock(&ph->p_arg->time_eat);
	pthread_mutex_unlock(&ph->p_arg->write_mutex);
	ft_usleep(ph->p_arg->time_to_eat);
	pthread_mutex_unlock(ph->right_f);
	pthread_mutex_unlock(&ph->left_f);
}

void	routine(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_f);
	pthread_mutex_lock(&ph->p_arg->write_mutex);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->p_arg->write_mutex);
	if (!ph->right_f)
	{
		ft_usleep(ph->p_arg->time_to_die * 2);
		return ;
	}
	pthread_mutex_lock(ph->right_f);
	pthread_mutex_lock(&ph->p_arg->write_mutex);
	write_status("has taken a fork\n", ph);
	pthread_mutex_unlock(&ph->p_arg->write_mutex);
	eat(ph);
	sleeping(ph);
	think(ph);
}
