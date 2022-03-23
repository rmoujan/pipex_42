NAME=pipex
CC=gcc
FLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=pipex.c\
OBJ = $(subst .c,.o,$(SRC))

all : $(NAME)
$(NAME):$(OBJ)

%.o : %.c

clean:
	$(RM) $(OBJ)

fclean:clean
	$(RM) $(NAME)
	
re:fclean all