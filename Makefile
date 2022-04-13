##
## EPITECH PROJECT, 2021
## makefile
## File description:
## makefile
##


SRC =	./src/main.c 

OBJ    =    $(SRC:.c=.o)

NAME   =    mysh

CFLAGS	+= -Wall -Wextra 

all:    $(NAME)

$(NAME):        $(OBJ)
	gcc -o $(NAME) $(OBJ) -lm

clean:
	 rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)


re:	fclean all

.PHONY: clean
	fclean
	re
