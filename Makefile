NAME					=					gd

CPP						=					g++
CPP_FLAGS				=					-std=c++17 -m64 -g -Wall -Werror -Wextra

LIB						=					-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

RM						=					rm -rf

INCLUDE_DIR				=					./include
INCLUDE_FILES			=					engine.hpp
INCLUDE					=					$(addprefix $(INCLUDE_DIR)/, $(INCLUDE_FILES))

SRC_DIR					=					./
SRC_FILES				=					main.cpp
SRC						=					$(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR					=					./obj
OBJ						=					$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

RESET					= 					\033[0m
GREEN		 			= 					\033[38;5;46m

$(OBJ_DIR)/%.o:			$(SRC_DIR)/%.cpp
						$(CPP) $(CPP_FLAGS) -c $< -o $@

all:					$(NAME)

$(NAME):				$(OBJ_DIR) $(OBJ) $(INCLUDE)
						$(CPP) $(CPP_FLAGS) $(OBJ) $(LIB) -o $(NAME)
						@echo "$(GREEN)Executable OK!	$(RESET)"

$(OBJ_DIR):
						@mkdir -p $(OBJ_DIR)

run:					all
						./$(NAME)

runv:					all
						valgrind -q --leak-check=full --show-leak-kinds=all -s --track-origins=yes ./$(NAME)

clean:
						@$(RM) $(OBJ_DIR)
						@echo "$(GREEN)Object files removed $(RESET)"

fclean:					clean
						@$(RM) $(NAME)
						@echo "$(GREEN)Executable removed $(RESET)"

re:						fclean all

.PHONY:					all clean fclean re