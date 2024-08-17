/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:56:03 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/17 23:52:18 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

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
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos[];
}					t_table;

// check args
bool				is_number(char **args);
bool				is_positive(char **args, bool meals_number);
// init
void				initialise_forks(char *argv[], pthread_mutex_t **forks[]);
void				initialise_locks(t_table *table);
t_philo				*initialise_philo(t_table *table, int id, char *argv[],
						bool meals_number);
void				initialise_table(char *argv[], t_table **table,
						bool meals_number);
// routine
int					ft_usleep(size_t milliseconds);
size_t				get_current_time(void);
void				print_message(char *msg, t_philo *philo);
void				assign_forks(t_philo *philos[], pthread_mutex_t *forks[],
						int num_of_philos);
int					thinking(t_philo *philo);
int					sleeping(t_philo *philo);
int					eating(t_philo *philo);
void				routine(t_philo *philo);
// monitor
void				print_message(char *msg, t_philo *philo);
bool				philo_is_dead(t_philo *philo);
bool				is_dead(t_table *table);
bool				finished_eating(t_table *table);
void				*monitor(void *ptr);
// utils
void				free_arr(char **arr);
void				free_table(t_table *table);
long long			ft_atoi(const char *str);
int					ft_usleep(size_t milliseconds);
void				ft_putendl_fd(char *s, int fd);
void				*ft_realloc(void *ptr, size_t old_size, size_t new_size);

#endif