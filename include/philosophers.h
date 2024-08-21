/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:56:03 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/21 21:47:30 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX 200

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				num_of_philos;
	int				num_of_meals;
	bool			eating;
	bool			*dead;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
}					t_philo;

typedef struct s_table
{
	bool			dead;

	pthread_t		waiter_id;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			**philos;
}					t_table;

// check args
int					ft_isdigit(int c);
bool				is_number(char **args);
bool				is_positive(char **args, bool meals_number);
bool				check_args(char **args, bool meals_number);
// init
void				init(char *argv[], t_table *table, int meals_number,
						pthread_mutex_t **forks);
void				initialise_forks(char *argv[], pthread_mutex_t ***forks);
void				initialise_locks(t_table *table);
t_philo				*initialise_philo(t_table *table, int id, char *argv[],
						bool meals_number);
void				initialise_table(char *argv[], t_table *table,
						bool meals_number);
// routine
int					ft_usleep(size_t milliseconds);
size_t				get_current_time(void);
void				print_message(char *msg, t_philo *philo);
void				assign_forks(t_philo *philos[], pthread_mutex_t **forks,
						int num_of_philos);
int					is_dead_loop(t_philo *philo);
int					thinking(t_philo *philo);
int					sleeping(t_philo *philo);
int					eating(t_philo *philo);
void				*routine(void *ptr);
// monitor
void				print_message(char *msg, t_philo *philo);
bool				philo_is_dead(t_philo *philo);
bool				is_dead(t_table *table);
bool				finished_eating(t_table *table);
void				*monitor(void *ptr);
// utils
void				free_table(t_table *table);
void				free_philos(t_philo *philos[]);
void				destroy_forks(pthread_mutex_t **forks);
void				free_all(t_table *table, pthread_mutex_t **forks);
long long			ft_atoi(const char *str);
int					ft_usleep(size_t milliseconds);
void				ft_putendl_fd(char *s, int fd);

#endif