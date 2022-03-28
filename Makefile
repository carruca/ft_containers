NAME			= ft_containers_tester

INC				= -I$(CONTAINER_DIR) -I$(ITER_DIR) -I$(TYPES_DIR) -I$(ALG_DIR) -I$(UTIL_DIR) -I$(TEST_DIR)

SRCS			= $(SRC)

OBJ_DIR			= obj/
OBJ				= $(patsubst $(TEST_DIR)%, $(OBJ_DIR)%, $(SRCS:.cpp=.o))
DEPS			= $(OBJ:.o=.d)

CXXFLAGS		= -Wall -Wextra -Werror -pedantic -O3 -MD $(INC) $(COMMONFLAGS) -std=c++98
CXX				= clang++
COMMONFLAGS		=
LDFLAGS			= $(COMMONFLAGS)

STD_FLAG		= -D USING_STD=1

DEBUG			= -g3
SANITIZE		= -fsanitize=address

OUTPUT_FT		= output_ft
OUTPUT_STD		= output_std
DIFF_OUTPUT		= diff_output

all:		$(NAME)
#all:		sanitize

-include	sources.mk headers.mk

-include	$(DEPS)

$(OBJ_DIR)%.o:	$(TEST_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(DEPS)
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

sanitize:	COMMONFLAGS += $(SANITIZE) $(DEBUG)
sanitize:	$(NAME)

run:		all
	./$(NAME)

ft:			$(NAME)
	./$(NAME) > $(OUTPUT_FT)

std:		CXXFLAGS += $(STD_FLAG)
std:		$(NAME)
	./$(NAME) > $(OUTPUT_STD)

test:
	$(MAKE) fclean std
	$(MAKE) fclean ft
	diff $(OUTPUT_STD) $(OUTPUT_FT) > $(DIFF_OUTPUT)

test_clean:
	$(RM) $(OUTPUT_STD) $(OUTPUT_FT) $(DIFF_OUTPUT)

tag:
	ctags $(SRC)

re:			fclean all

.SILENT: run tag fclean clean
.PHONY: all clean fclean re std ft test test_clean
