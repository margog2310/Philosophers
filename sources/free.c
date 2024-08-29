/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:48:43 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/29 19:34:27 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philos(t_philo *philos[])
{
	int	i;

	if (philos)
	{
		i = 0;
		while (philos[i])
		{
			free(philos[i]);
			i++;
		}
		free(philos);
	}
}

void	destroy_forks(pthread_mutex_t **forks)
{
	int	i;

	if (forks)
	{
		i = 0;
		while (forks[i])
			pthread_mutex_destroy(forks[i++]);
		free(forks);
	}
}

void	free_table(t_table *table)
{
	if (table)
	{
		if (table->philos)
			free(table->philos);
		pthread_mutex_destroy(&table->dead_lock);
		pthread_mutex_destroy(&table->meal_lock);
		pthread_mutex_destroy(&table->write_lock);
	}
}

void	free_all(t_table *table, pthread_mutex_t **forks)
{
	if (forks)
		destroy_forks(forks);
	if (table)
		free_table(table);
}
