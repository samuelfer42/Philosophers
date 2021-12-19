/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safernan <safernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:57:19 by safernan          #+#    #+#             */
/*   Updated: 2021/12/19 19:06:53 by safernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_death2(t_struct *s)
{
	pthread_mutex_lock(&s->a.dead);
	if (s->a.stop)
	{
		pthread_mutex_unlock(&s->a.dead);
		return (1);
	}
	pthread_mutex_unlock(&s->a.dead);
	return (0);
}

void	stop(t_struct *s)
{
	int	i;

	i = -1;
	while (!check_death2(s))
		ft_usleep(1);
	while (++i < s->a.nb_philo)
		pthread_join(s->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&s->a.write_mutex);
	i = -1;
	while (++i < s->a.nb_philo)
		pthread_mutex_destroy(&s->ph[i].left_f);
	if (s->a.stop == 2)
		printf("Each philosopher ate %d time(s)\n", s->a.eat_limit);
	free(s->ph);
}

int	main(int argc, char **argv)
{
	t_struct		s;

	if (!(parse_args(argc, argv, &s)))
	{
		printf("Error: Bad arguments\n");
		printf("Usage: /philosophers <number of philosophers> <time to die> ");
		printf("<time to eat> <time to sleep> ");
		printf("[number of times each philosophers mut eat]\n");
		return (0);
	}
	s.ph = malloc(sizeof(t_philo) * s.a.nb_philo);
	if (!s.ph)
	{
		printf("Error Malloc");
		return (0);
	}
	if (!init(&s) || !thread_create(&s))
	{
		free(s.ph);
		return (0);
	}
	stop(&s);
}
