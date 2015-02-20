##
## Makefile for  in /home/maret_a/Projets/AbstractVM/cpp_abstractvm/sources
## 
## Made by Adrien Maret
## Login   <maret_a@epitech.net>
## 
## 
## Started on  19/02/2014 15:26
##

CXX	=	clang++

SRCS	=	ReflectedFlood.cpp \
		Mitm.cpp \
		Addresses.cpp\
		DnsSpoof.cpp \
		Core.cpp \
		main.cpp

CXXFLAGS=	-Wall -W -Wextra -std=c++11

OBJS	=	$(SRCS:.cpp=.o)

NAME	=	sniff

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CXX) -o $(NAME) $(OBJS) -ltins -lpthread

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
