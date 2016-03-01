##
## Makefile for 102 in /home/bauren_a/Work/Tek1/Maths/102cipher
## 
## Made by Arthur
## Login   <bauren_a@epitech.net>
## 
## Started on  Sat Nov 28 04:13:09 2015 Arthur
## Last update Sat Nov 28 04:32:26 2015 Arthur
##

SRC	=	Main.cpp	\
		Matrix.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	102cipher

INCLUDE	=	./include/

CXXFLAGS	+=	-I$(INCLUDE)

CC	=	g++

RM	=	rm -rf

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
