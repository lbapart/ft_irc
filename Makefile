CXX			= c++
NAME		= ircserv
RM			= rm -rf

CXXFLAGS	= -Wall -Wextra -Werror -MD -MP -g - pedantic -std=c++98

MAKEFLAGS	= -j$(nproc)

INCLUDES	= -I ./incl
SRCS_DIR	= srcs
#SRCS	= ${SRCS_DIR}/main.cpp

SRCS		= $(wildcard $(SRCS_DIR)/*.cpp)

OBJS_DIR	= objs
OBJS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
DEPS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.d))

all		: $(NAME)

run		:
		@make --no-print-directory re
		@make --no-print-directory clean
		@clear;
		./${NAME} 1111 1234

$(NAME)	: $(OBJS)
		$(CXX) -o $@ $^

objs/%.o: %.cpp
		@mkdir -p $(dir $@)
		${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

clean	:
		$(RM) $(OBJS_DIR)

fclean	:
		$(RM) $(OBJS_DIR) $(NAME)

re		:
		$(RM) $(OBJS_DIR) $(NAME)
		make all

-include $(DEPS)

.PHONY: all clean fclean re run
