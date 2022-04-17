NAME			= tester

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

OUTPUT_FT		= ft_output
OUTPUT_STD		= std_output
OUTPUT_DIFF		= diff_output

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

std:		CXXFLAGS += $(STD_FLAG)
std:		re

output_std:	std
	./$(NAME) > $(OUTPUT_STD)

output_ft:	re
	./$(NAME) > $(OUTPUT_FT)

test:		output_std
	$(MAKE) output_ft
	diff $(OUTPUT_STD) $(OUTPUT_FT) > $(OUTPUT_DIFF)

test_clean:
	$(RM) $(OUTPUT_STD) $(OUTPUT_FT) $(OUTPUT_DIFF)

tag:
	ctags $(SRCS)

re:			fclean all

.SILENT: run tag clean fclean test_clean
.PHONY: all clean fclean re std output_std run test test_clean sanitize
