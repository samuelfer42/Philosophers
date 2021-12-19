/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safernan <safernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:57:19 by safernan          #+#    #+#             */
/*   Updated: 2021/12/19 19:18:09 by safernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# define INT_MAX 2147483647

typedef struct s_arg
{
	int						nb_philo;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						eat_limit;
	long int				start_time;
	pthread_mutex_t			write_mutex;
	pthread_mutex_t			dead;
	pthread_mutex_t			time_eat;
	pthread_mutex_t			finish;
	int						nb_philo_finish;
	int						stop;
}							t_arg;

typedef struct s_philo
{
	int						id;
	pthread_t				thread_id;
	pthread_t				thread_death_id;
	pthread_mutex_t			*right_f;
	pthread_mutex_t			left_f;
	t_arg					*p_arg;
	long int				ms_eat;
	unsigned int			nb_eat;
	int						finish;
}							t_philo;

typedef struct s_struct
{
	t_philo					*ph;
	t_arg					a;
}							t_struct;

int			init(t_struct *s);
long int	current_time(void);
int			ft_strlen(char *str);
int			parse_args(int argc, char **argv, t_struct *s);
int			is_number(char **argv, int i, int j);
int			ft_atoi(const char *str);
int			check_death2(t_struct *s);
void		stop(t_struct *s);
void		write_status(char *str, t_philo *ph);
void		sleeping(t_philo *ph);
void		think(t_philo *ph);
void		eat(t_philo *ph);
void		routine(t_philo *ph);
void		*is_dead(void	*data);
void		*thread(void *data);
int			thread_create(t_struct *s);
int			check_death(t_philo *ph, int i);
void		ft_usleep(long int time_in_ms);
void		mutex_init(t_struct *s);
#endif