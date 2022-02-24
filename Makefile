NAME = philo
 
CFILES =	Phil/fork.c Phil/init.c Phil/monitor.c \
			Phil/phil.c Phil/utils.c
 
BONUS =		Phil_bonus/fork.c Phil_bonus/init.c Phil_bonus/utils.c \
			Phil_bonus/monitor.c Phil_bonus/philosophers.c
 
OBJECTS = $(CFILES:.c=.o)
 
OBJECTS_C = $(BONUS:.c=.o)
 
CC = gcc
 
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
 
$(NAME): $(OBJECTS) Phil/phil.h $(CFILES)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
 
bonus: $(OBJECTS_C) Phil_bonus/philosophers.h $(BONUS)
	$(CC) $(CFLAGS) $(OBJECTS_C) -o philo_bonus
 
clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_C)
 
fclean: clean
	rm -f $(NAME)
	rm -f philo_bonus

re: fclean all
 
call: all clean