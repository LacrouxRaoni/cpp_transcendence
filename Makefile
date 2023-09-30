NAME    =       pongApi.out

SRC_DIR         =	src
PATH_OBJ        =	obj

HEADERS         =	includes/


CC   			=	c++
RM   			=	rm -rf
FLAGS			=	-Wall -Wextra -Werror -std=c++17
FLAG_PISTACHE	=	-lpistache


SRC_FILES		=	main.cpp \
					pistacheHandler.cpp



SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ				=	$(SRC:$(SRC_DIR)/%.cpp=$(PATH_OBJ)/%.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	@echo done!!
	@$(CC) $(FLAGS) $(OBJ) -g -o $(NAME) $(FLAG_PISTACHE)

$(PATH_OBJ)/%.o:	$(SRC_DIR)/%.cpp
	@mkdir -p $(PATH_OBJ)
	$(CC) -g $(FLAGS) -c -I $(HEADERS) -o $@ $<

clean:
	$(RM) $(PATH_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean rer