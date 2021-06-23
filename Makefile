CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	main.c inits.c display.c handlers.c print.c utils.c
OBJS	=	$(SRCS:c=o)
NAME	=	fractol
LIB		=	libft.a
LIBSRCS	=	libft/*.c
LIBOBJS	=	libft/*.o


.PHONY:	all
all:	$(LIB) $(NAME)

bonus:	all

$(LIB):
	make -C libft/
	mv libft/$(LIB) .

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o:	%.c
	$(CC) $(CFLAGS) -c $< -Ilibft/

clean:
	make -C libft/ clean
	$(RM) $(OBJS) $(LIB)

fclean:		clean
	make -C libft/ fclean
	$(RM) $(NAME)

re:		fclean all

bonus:
