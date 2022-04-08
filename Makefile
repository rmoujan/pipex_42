NAME=pipex
CC=gcc
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=pipex.c\
	operations.c

OBJ = $(subst .c,.o,$(SRC))
lib = ./libft/libft.a
libobj = ./libft/*.o

all : $(NAME) 

$(NAME):${OBJ}
	@make -C libft
	$(CC) $(OBJ) $(lib) -o $(NAME)
%.o : %.c
	@${CC} -c ${CFLAGS} $< -o $@

clean:
	$(RM) $(OBJ) $(libobj)

fclean:clean
	$(RM) $(NAME) $(lib)
	
re:fclean all