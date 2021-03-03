NAME = minishell

SRC = *.c parser/*.c logic/*.c logic/liblist/*.c parser/fn_validation_for_argument/*.c
OBJ = *.o
HEAD = libminishell.h

all:
	cd libasm && make && make clean
	gcc $(SRC) libasm/libasm.a -o $(NAME)

clean:
	rm -rf $(NAME)