CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SRCS	=	main.c
OBJS	=	$(SRCS:c=o)
NAME	=	fractol
LIB		=	libft.a

.PHONY:	all
all:	$(LIB) $(NAME)

$(LIB):
	make -C libft/
	mv libft/$(LIB) .

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -lmlx -framework OpenGL -framework AppKit -g -fsanitize=address  -o $(NAME)

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
