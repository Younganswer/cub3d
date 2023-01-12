SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

NAME	= cub3d

LIBS_DIR		= ./libs

LIBFT_DIR		:= ${LIBS_DIR}/libft
LIBFT_INCS_DIR	:= ${LIBFT_DIR}/incs
LIBFT			:= ${LIBFT_DIR}/libft.a

GNL_DIR			:= ${LIBS_DIR}/libgnl
GNL_INCS_DIR	:= ${GNL_DIR}/incs
GNL				:= ${GNL_DIR}/libgnl.a

INCS_DIR	= ./incs
SRCS_DIR	= ./srcs
OBJS_DIR	= ./objs

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I${INCS_DIR} -I${LIBFT_INCS_DIR} -I${GNL_INCS_DIR} -MD
LDFLAGS	= -L${LIBFT_DIR} -lft -L${GNL_DIR} -lgnl
AR		= ar rcs
RM		= rm -f

SRCS = 	cub3d.c
		
SRCS := ${addprefix ${SRCS_DIR}/, ${SRCS}}
OBJS := ${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}
DEPS := ${OBJS:.o=.d}


all: ${NAME}


${OBJS_DIR}:
	@echo "Build ${NAME}"
	@mkdir -p ${OBJS_DIR}


${LIBFT}:
	@make -C ${LIBFT_DIR}


${GNL}:
	@make -C ${GNL_DIR}


${NAME}: ${LIBFT} ${GNL} ${OBJS}
	@printf "\bdone\n"
	${eval IDX = 0}
	@${CC} ${LDFLAGS} -g -o ${NAME} ${OBJS}
	@echo "Build ${NAME}: done"


${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	${eval IDX = ${shell expr ${IDX} + 1}}
	${eval T_IDX = ${shell expr ${IDX} % 32}}
	${eval T_IDX = ${shell expr ${T_IDX} / 8 + 1}}
	${eval CHR = ${shell echo ${SPINNER} | cut -c ${T_IDX}}}
	@if [ ${IDX} = 1 ]; then\
		echo -n "Build dependencies in ${NAME} ...  ";\
	fi
	@printf "\b${CHR}"
	@${CC} ${CFLAGS} -g -c $< -o $@


clean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${LIBFT_DIR} clean
	@make -C ${GNL_DIR} clean
	@rm -rf ${OBJS_DIR}


fclean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${LIBFT_DIR} fclean
	@make -C ${GNL_DIR} fclean
	@echo "Remove ${NAME}"
	@rm -rf ${OBJS_DIR}
	@${RM} ${NAME}
	

re:
	@echo "Re-build ${NAME}"
	@make fclean
	@make all


.PHONY: all clean fclean re bonus


-include ${DEPS}