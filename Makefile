# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/17 17:56:31 by mganchev          #+#    #+#              #
#    Updated: 2024/08/17 21:19:05 by mganchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDE = ./include

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRCDIR =./sources
OBJDIR =./build

SRCS = $(SRCDIR)/main.c $(SRCDIR)/check_args.c $(SRCDIR)/routine.c $(SRCDIR)/time.c \
$(SRCDIR)/free.c $(SRCDIR)/utils.c

OBJS = $(OBJDIR)/main.o $(OBJDIR)/check_args.o $(OBJDIR)/routine.o $(OBJDIR)/time.o \
$(OBJDIR)/free.o $(OBJDIR)/utils.o

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@
	
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lft -o $(NAME)

clean:
	@rm -rf $(OBJDIR)

fclean:
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all

leaks: all