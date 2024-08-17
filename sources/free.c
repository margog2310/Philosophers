/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:48:43 by mganchev          #+#    #+#             */
/*   Updated: 2024/08/17 19:52:43 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    free_table(t_table *table)
{
    if (table)
    {
        if (table->philos)
            free_arr(&table->philos);
        if (&table->dead_lock)
            pthread_mutex_destroy(&table->dead_lock);
        if (&table->meal_lock)
            pthread_mutex_destroy(&table->meal_lock);
        if (&table->write_lock)
            pthread_mutex_destroy(&table->write_lock);
        free(table);
    }
}
