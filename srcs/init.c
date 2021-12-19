/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safernan <safernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:57:19 by safernan          #+#    #+#             */
/*   Updated: 2021/12/19 19:11:45 by safernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init(t_struct *s)
{
	int	i;

	i = 0;
	s->a.start_time = current_time();
	s->a.stop = 0;
	s->a.nb_philo_finish = 0;
	mutex_init(s);
	while (i < s->a.nb_philo)
	{
		s->ph[i].id = i + 1;
		s->ph[i].ms_eat = s->a.start_time;
		s->ph[i].nb_eat = 0;
		s->ph[i].finish = 0;
		s->ph[i].right_f = NULL;
		pthread_mutex_init(&s->ph[i].left_f, NULL);
		if (s->a.nb_philo == 1)
			return (1);
		if (i == s->a.nb_philo - 1)
			s->ph[i].right_f = &s->ph[0].left_f;
		else
			s->ph[i].right_f = &s->ph[i + 1].left_f;
		i++;
	}
	return (1);
}

void	mutex_init(t_struct *s)
{
	pthread_mutex_init(&s->a.write_mutex, NULL);
	pthread_mutex_init(&s->a.dead, NULL);
	pthread_mutex_init(&s->a.time_eat, NULL);
	pthread_mutex_init(&s->a.finish, NULL);
}

long int	current_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	if (gettimeofday(&current_time, NULL) == -1)
	{
		printf ("Error Gettimeofday");
		return (0);
	}
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
