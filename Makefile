NAME=pipex
CC=gcc
CFLAGS= -Wall -Wextra -Werror
RM = rm -f
SRC=pipex.c

OBJ = $(subst .c,.o,$(SRC))
lib = ./libft/libft.a
libobj = ./libft/*.o

all : $(NAME) 

$(NAME):${OBJ}
	make -C libft
	$(CC) $(OBJ) $(lib) -o $(NAME)
%.o : %.c
	${CC} -c ${CFLAGS} $< -o $@

clean:
	$(RM) $(OBJ) $(libobj)

fclean:clean
	$(RM) $(NAME) $(lib)
	
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