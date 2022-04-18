TEST_DIR		= test/

STACK_DIR		= stack/
STACK_TEST		= top.cpp							\
				  size.cpp							\
				  relationals.cpp

MAP_DIR			= map/
MAP_TEST		= lower_bound.cpp					\
				  upper_bound.cpp					\
				  create_empty.cpp					\
				  equal_range.cpp					\
				  size.cpp							\
				  find.cpp							\
				  value_comp.cpp					\
				  relationals.cpp					\
				  swap.cpp							\
				  insert.cpp						\
				  erase.cpp							\
				  count.cpp

VECTOR_DIR		= vector/
TEST_VECTOR		= old_test.cpp						\
				  constructor.cpp					\
				  swap.cpp							\
				  const_iterators.cpp				\
				  assign.cpp						\
				  size.cpp							\
				  insert.cpp						\
				  reserve.cpp

TEST_UTILS		= pair.cpp						\
				  equal.cpp						\
				  lexicographical_compare.cpp 	\
				  reverse_iterator.cpp

SRC				= $(addprefix $(TEST_DIR),						\
				  main.cpp										\
				  $(TEST_UTILS)									\
				  $(addprefix $(VECTOR_DIR), $(TEST_VECTOR))	\
				  $(addprefix $(MAP_DIR), $(MAP_TEST))			\
				  $(addprefix $(STACK_DIR), $(STACK_TEST)))

