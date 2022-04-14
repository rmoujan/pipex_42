NAME=pipex
bonus=pipex_bns
CC=gcc
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=pipex.c\
	operations.c\
	processes.c\
	handle_errors.c

SRCBNS=bns_pipex.c\
       operations_bounus.c\
	   handle_errors_bns.c


OBJ = $(subst .c,.o,$(SRC))
OBJBNS = $(subst .c,.o,$(SRCBNS))
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