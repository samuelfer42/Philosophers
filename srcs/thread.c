/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safernan <safernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:57:19 by safernan          #+#    #+#             */
/*   Updated: 2021/12/19 18:58:15 by safernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*is_dead(void	*data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->p_arg->time_to_die + 1);
	pthread_mutex_lock(&ph->p_arg->time_eat);
	pthread_mutex_lock(&ph->p_arg->finish);
	if (!check_death(ph, 0) && !ph->finish && ((current_time() - ph->ms_eat) \
		>= (long)(ph->p_arg->time_to_die)))
	{
		pthread_mutex_unlock(&ph->p_arg->time_eat);
		pthread_mutex_unlock(&ph->p_arg->finish);
		pthread_mutex_lock(&ph->p_arg->write_mutex);
		write_status("died\n", ph);
		pthread_mutex_unlock(&ph->p_arg->write_mutex);
		check_death(ph, 1);
	}
	pthread_mutex_unlock(&ph->p_arg->time_eat);
	pthread_mutex_unlock(&ph->p_arg->finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo					*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		ft_usleep(ph->p_arg->time_to_eat / 10);
	while (!check_death(ph, 0))
	{
		pthread_create(&ph->thread_death_id, NULL, is_dead, data);
		routine(ph);
		pthread_detach(ph->thread_death_id);
		if ((int)++ph->nb_eat == ph->p_arg->eat_limit)
		{
			pthread_mutex_lock(&ph->p_arg->finish);
			ph->finish = 1;
			ph->p_arg->nb_philo_finish++;
			if (ph->p_arg->nb_philo_finish == ph->p_arg->nb_philo)
			{
				pthread_mutex_unlock(&ph->p_arg->finish);
				check_death(ph, 2);
			}
			pthread_mutex_unlock(&ph->p_arg->finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	thread_create(t_struct *s)
{
	int	i;

	i = 0;
	while (i < s->a.nb_philo)
	{
		s->ph[i].p_arg = &s->a;
		if (pthread_create(&s->ph[i].thread_id, NULL, thread, &s->ph[i]) != 0)
		{
			printf("Error Pthread");
			return (0);
		}
		i++;
	}
	return (1);
}
