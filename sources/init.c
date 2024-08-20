/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:05:04 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/20 19:12:17 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialise_forks(char *argv[], pthread_mutex_t **forks[])
{
	int	i;
	int	num_of_forks;

	i = 0;
	num_of_forks = ft_atoi(argv[1]);
	while (i < num_of_forks)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!forks[i])
		{
			ft_putendl_fd("Error: Memory Allocation", 2);
			destroy_forks(forks);
			return ;
		}
		pthread_mutex_init(forks[i], NULL);
		i++;
	}
}

void	initialise_waiter(t_table *table)
{
	pthread_t	waiter_id;

	pthread_create(&waiter_id, NULL, monitor, (void *)&table);
	pthread_join(waiter_id, NULL);
}

t_philo	*initialise_philo(t_table *table, int id, char *argv[],
		bool meals_number)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return ((ft_putendl_fd("Error: Memory Allocation", 2),
				free_table(table)), NULL);
	pthread_create(&philo->thread, NULL, routine, (void *)&philo);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_of_philos = ft_atoi(argv[1]);
	if (meals_number)
		philo->num_of_meals = ft_atoi(argv[5]);
	else
		philo->num_of_meals = -1;
	philo->eating = false;
	philo->dead = &(table->dead);
	philo->last_meal = get_current_time();
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->start_time = get_current_time();
	philo->write_lock = &(table->write_lock);
	philo->meal_lock = &(table->meal_lock);
	philo->dead_lock = &(table->dead_lock);
	return (philo);
}

void	initialise_locks(t_table *table)
{
	pthread_mutex_init(&table->dead_lock, NULL);
	pthread_mutex_init(&table->meal_lock, NULL);
	pthread_mutex_init(&table->write_lock, NULL);
}

void	initialise_table(char *argv[], t_table **table, bool meals_number)
{
	int	i;
	int	num_of_philos;

	num_of_philos = ft_atoi(argv[1]);
	*table = malloc(sizeof(t_table) + sizeof(t_philo) * num_of_philos);
	if (!*table)
		return (ft_putendl_fd("Error: Memory Allocation", 2), (void)0);
	initialise_locks(*table);
	(*table)->dead = false;
	i = 0;
	while (i < num_of_philos)
	{
		(*table)->philos[i] = initialise_philo(*table, i + 1, argv,
				meals_number);
		if (!(*table)->philos[i])
			return (ft_putendl_fd("Error: Memory Allocation", 2),
				free_table(*table), (void)0);
		i++;
	}
}
