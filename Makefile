# include libft/Makefile
NAME=pipex
CC=gcc
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=pipex.c

OBJ = $(subst .c,.o,$(SRC))

sub-make:
	make -C libft

all : $(NAME) 

$(NAME):${OBJ} libft/libft.a
	$(CC) $(OBJ) -o $(NAME)
%.o : %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	$(RM) $(OBJ) libft/*.o

fclean:clean
	$(RM) $(NAME) 
	
re:fclean all

# /////



# all: $(NAME)

# # $(NAME): ${OBJ}
# # 	$(CC) $(OBJ) -o $(NAME)

# $(NAME): $(OBJ)
# 	@$(CC) $(OBJ) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# %.o: %.c
# 		@${CC} -c ${CFLAGS} -I/usr/local/include $< -o $@

# # %.o: %.c
# # 		${CC} -c ${CFLAGS} $< -o $@

# clean :
# 	$(RM) $(OBJ)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all