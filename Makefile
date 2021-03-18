NAME = minishell

SRC = *.c parser/*.c logic/*.c logic/liblist/*.c parser/fn_validation_for_argument/*.c
HEAD = libminishell.h strminishell.h parser/fn_validation_for_argument/validator.h

all : $(NAME)

$(NAME): $(SRC) $(HEAD)
	gcc $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean : clean

re: fclean all