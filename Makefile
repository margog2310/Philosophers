# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/17 17:56:31 by mganchev          #+#    #+#              #
#    Updated: 2024/08/29 23:11:04 by mganchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
BONUS_NAME = philo_bonus

INCLUDE = ./include

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -lpthread -lrt

SRCDIR =./sources
BONUS_SRCDIR =./bonus
OBJDIR =./build

SRCS = $(SRCDIR)/main.c $(SRCDIR)/check_args.c $(SRCDIR)/init.c $(SRCDIR)/monitor.c \
$(SRCDIR)/routine.c $(SRCDIR)/time.c $(SRCDIR)/free.c $(SRCDIR)/utils.c
BONUS_SRCS = 

OBJS = $(OBJDIR)/main.o $(OBJDIR)/check_args.o $(OBJDIR)/init.o $(OBJDIR)/monitor.o \
$(OBJDIR)/routine.o $(OBJDIR)/time.o $(OBJDIR)/free.o $(OBJDIR)/utils.o
BONUS_OBJS = 

all: $(OBJDIR) $(NAME)

bonus: $(OBJDIR) $(BONUS_NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(OBJDIR)/%_bonus.o: $(BONUS_SRCDIR)/%._bonusc
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
clean:
	@rm -rf $(OBJDIR)

fclean:
	@rm -rf $(OBJDIR)
	@rm -f $(NAME) $(BONUS_NAME)

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

re: fclean all
