NAME=pipex
NAME2=pipex_bns
CC=gcc
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=pipex.c\
	operations.c\
	processes.c\
	handle_errors.c\
	operations2.c

SRCBNS=bns_pipex.c\
       operations_bounus.c\
	   handle_errors_bns.c\
	   forking_heredoc.c\
	   operations_heredoc.c\
	   operations2.c\
	   multi_pipesnew.c\
	   operations.c\
	   multpipes_tools.c\
	   ./gnl/get_next_line.c\
	   ./gnl/get_next_line_utils.c 


OBJ = $(subst .c,.o,$(SRC))
OBJBNS = $(subst .c,.o,$(SRCBNS))
lib = ./libft/libft.a
libobj = ./libft/*.o

all : $(NAME)

$(NAME):${OBJ}
	@make -C libft
	$(CC) $(OBJ) $(lib) -o $(NAME)

%.o : %.c
	${CC} -c ${CFLAGS} $< -o $@

bonus :$(NAME2)

$(NAME2):${OBJBNS}
	@make -C libft
	$(CC) $(OBJBNS) $(lib) -o $(NAME2)

%.o : %.c
	@${CC} -c ${CFLAGS} $< -o $@

clean:
	$(RM) $(OBJ) $(OBJBNS) $(libobj)

fclean:clean
	$(RM) $(NAME) $(NAME2) $(lib)
	
re:fclean all