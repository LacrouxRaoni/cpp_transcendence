NAME    =       pongApi.out

SRC_DIR         =	src

SYSTEM_DIR		=	system/
CONTROLLERS_DIR	=	controllers/
DTO_DIR			=	model/dtos/
SERVICE_DIR		=	model/services/
ENTITY_DIR		=	model/entities/
REPOSITORY_DIR	=	model/repositories/

PATH_OBJ        =	obj

HEADERS         =	includes/


CC   			=	c++
RM   			=	rm -rf
FLAGS			=	-Wall -Wextra -Werror -std=c++17
FLAG_PISTACHE	=	-lpistache
FLAG_LIBCURL	=	-lcurl
FLAG_LIBPQ		=	-lpq
FLAG_CPP_JWT	=	-lcrypto
FLAG_SSL		=	-lssl



SRC_FILES		=	$(SYSTEM_DIR)Main.cpp \
					$(SYSTEM_DIR)ApiSetup.cpp \
					$(CONTROLLERS_DIR)UserController.cpp \
					$(CONTROLLERS_DIR)ExceptionController.cpp \
					$(DTO_DIR)UserDto.cpp \
					$(SERVICE_DIR)UserService.cpp \
					$(ENTITY_DIR)UserEntity.cpp \
					$(REPOSITORY_DIR)UserRepository.cpp


SRC				=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ				=	$(SRC:$(SRC_DIR)/%.cpp=$(PATH_OBJ)/%.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	@echo done!!
	@$(CC) $(FLAGS) $(OBJ) -g -o $(NAME) $(FLAG_PISTACHE) $(FLAG_LIBCURL) $(FLAG_LIBPQ) $(FLAG_CPP_JWT) $(FLAG_SSL)

$(PATH_OBJ)/%.o:	$(SRC_DIR)/%.cpp
	@mkdir -p $(PATH_OBJ)
	@mkdir -p $(PATH_OBJ)/$(SYSTEM_DIR)
	@mkdir -p $(PATH_OBJ)/$(CONTROLLERS_DIR)
	@mkdir -p $(PATH_OBJ)/$(DTO_DIR)
	@mkdir -p $(PATH_OBJ)/$(SERVICE_DIR)
	@mkdir -p $(PATH_OBJ)/$(ENTITY_DIR)
	@mkdir -p $(PATH_OBJ)/$(REPOSITORY_DIR)
	$(CC) -g $(FLAGS) -c -I $(HEADERS) -o $@ $<

clean:
	$(RM) $(PATH_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean rer