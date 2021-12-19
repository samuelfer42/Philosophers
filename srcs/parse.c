/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safernan <safernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:57:19 by safernan          #+#    #+#             */
/*   Updated: 2021/12/19 19:06:15 by safernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	parse_args(int argc, char **argv, t_struct *s)
{
	if ((argc == 5 || argc == 6) && is_number(argv, 0, 1))
	{
		s->a.nb_philo = ft_atoi(argv[1]);
		s->a.time_to_die = ft_atoi(argv[2]);
		s->a.time_to_eat = ft_atoi(argv[3]);
		s->a.time_to_sleep = ft_atoi(argv[4]);
		s->a.eat_limit = -1;
		if (argc == 6)
			s->a.eat_limit = ft_atoi(argv[5]);
		if (s->a.nb_philo <= 0 || s->a.time_to_die <= 0)
			return (0);
		if (s->a.time_to_eat <= 0 || s->a.time_to_sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}

int	is_number(char **argv, int i, int j)
{
	while (argv[j])
	{
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9' || ft_strlen(argv[j]) > 10)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	nb;

	nb = 0;
	i = -1;
	while (str[++i])
		nb = (nb * 10) + (str[i] - 48);
	return (nb);
}
