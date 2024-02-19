CXX			= c++
NAME		= ircserv
RM			= rm -rf

CXXFLAGS	= -Wall -Wextra -Werror -MD -MP -g -std=c++98 -pedantic

MAKEFLAGS	= -j$(nproc)

INCLUDES	= -I ./incl
SRCS_DIR	= srcs
SRCS	=	${SRCS_DIR}/main.cpp \
			${SRCS_DIR}/Channel.cpp \
			${SRCS_DIR}/Client.cpp \
			${SRCS_DIR}/HelpingFunctions.cpp \
			${SRCS_DIR}/Response.cpp \
			${SRCS_DIR}/Server.cpp \
			${SRCS_DIR}/ServerExecutor.cpp \
			${SRCS_DIR}/ServerLoop.cpp \
			${SRCS_DIR}/ServerMessageHandling.cpp \

OBJS_DIR	= objs
OBJS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.o))
DEPS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.cpp=.d))

all		: $(NAME)

run		:
		@make --no-print-directory re
		@make --no-print-directory clean
		@clear;
		@echo '/connect 127.0.0.1 1111 1234'
		./${NAME} 1111 1234

test	:
		@make --no-print-directory re
		@make --no-print-directory clean
		@clear;
		@echo '/connect 127.0.0.1 1111 1234'
		valgrind --track-fds=yes ./${NAME} 1111 1234

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

.PHONY: all clean fclean re run test
