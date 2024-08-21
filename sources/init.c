/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:05:04 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/21 23:41:47 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	initialise_forks(char *argv[], pthread_mutex_t ***forks)
{
	int	i;
	int	num_of_forks;

	i = 0;
	num_of_forks = ft_atoi(argv[1]);
	*forks = malloc(num_of_forks * sizeof(pthread_mutex_t));
	if (!*forks)
		return (ft_putendl_fd("Error: Memory Allocation", 2), (void)0);
	while (i < num_of_forks)
	{
		(*forks)[i] = malloc(sizeof(pthread_mutex_t));
		if (!(*forks)[i])
			return (ft_putendl_fd("Error: Memory allocation", 2),
				destroy_forks(*forks), (void)0);
		pthread_mutex_init((*forks)[i], NULL);
		i++;
	}
}

t_philo	*initialise_philo(t_table *table, int id, char *argv[],
		bool meals_number)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return ((ft_putendl_fd("Error: Memory Allocation", 2),
				free_table(table)), NULL);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->num_of_philos = ft_atoi(argv[1]);
	if (meals_number)
		philo->num_of_meals = ft_atoi(argv[5]);
	else
		philo->num_of_meals = -1;
	philo->dead = &(table->dead);
	philo->eating = false;
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
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

void	initialise_table(char *argv[], t_table *table, bool meals_number)
{
	int	i;
	int	num_of_philos;

	num_of_philos = ft_atoi(argv[1]);
	table->philos = malloc(sizeof(t_philo *) * num_of_philos);
	if (!table->philos)
		return (ft_putendl_fd("Error: Memory allocation", 2),
			free_table(table), (void)0);
	initialise_locks(table);
	pthread_mutex_lock(&table->dead_lock);
	table->dead = false;
	pthread_mutex_unlock(&table->dead_lock);
	i = 0;
	while (i < num_of_philos)
	{
		table->philos[i] = initialise_philo(table, i + 1, argv,
				meals_number);
		if (!table->philos[i])
			return (ft_putendl_fd("Error: Memory allocation", 2),
				free_table(table), (void)0);
		i++;
	}
}
