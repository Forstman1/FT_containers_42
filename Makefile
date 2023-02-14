# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sahafid <sahafid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 13:27:18 by sahafid           #+#    #+#              #
#    Updated: 2023/02/06 17:53:52 by sahafid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = main.cpp
OFILES = $(FILES:.cpp=.o)

CPP = c++
NAME = containers
FLAGS = -std=c++98 -Wall -Werror -Wextra
HEADERS = vector/vector.hpp stack/stack.hpp map/map.hpp 

all : $(NAME)

$(NAME) : main.cpp $(FILES) $(HEADERS)
	$(CPP) $(FLAGS) main.cpp $(FILES) -o $@

%.o:%.cpp
	@$(CPP) $(FLAGS) -c $< -o $@ 

clean:
	@rm -rf $(OFILES)

fclean: clean
	@rm -rf $(NAME)

re: fclean all