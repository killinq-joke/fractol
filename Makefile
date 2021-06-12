CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	main.c
OBJS	=	$(SRCS:c=o)
NAME	=	fdf

.PHONY:		all
all		:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all
