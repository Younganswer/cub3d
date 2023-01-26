SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

NAME	= cub3d

LIBS_DIR		= libs

LIBFT_DIR		:= ${LIBS_DIR}/libft
LIBFT_INCS_DIR	:= ${LIBFT_DIR}/incs
LIBFT			:= ${LIBFT_DIR}/libft.a

LIBGNL_DIR		:= ${LIBS_DIR}/libgnl
LIBGNL_INCS_DIR	:= ${LIBGNL_DIR}/incs
LIBGNL			:= ${LIBGNL_DIR}/libgnl.a

LIBMLX_DIR		:= ${LIBS_DIR}/libmlx
LIBMLX_INCS_DIR	:= ${LIBMLX_DIR}/incs
LIBMLX			:= ${LIBMLX_DIR}/libmlx.dylib

INCS_DIR	= incs
SRCS_DIR	= srcs
OBJS_DIR	= objs

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I${INCS_DIR} -I${LIBFT_INCS_DIR} -I${LIBGNL_INCS_DIR} -I${LIBMLX_INCS_DIR} -MD -O3
LDFLAGS	= -L${LIBFT_DIR} -lft -L${LIBGNL_DIR} -lgnl -L${LIBMLX_DIR} -lmlx -framework OpenGL -framework AppKit
AR		= ar rcs
RM		= rm -f

SRCS = 	cub3d.c \
		game/init_game.c \
		game/exit_game.c \
		game/key_pressed.c \
		game/mouse_moved.c \
		parse/parse.c \
		parse/parse_floor_ceiling.c \
		parse/parse_map.c \
		parse/parse_texture.c \
		raycast/raycast.c \
		raycast/dda.c \
		raycast/set_line.c \
		render/render.c \
		render/render_line.c
		
SRCS := ${addprefix ${SRCS_DIR}/, ${SRCS}}
OBJS := ${SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}
DEPS := ${OBJS:.o=.d}


all: ${NAME}


${NAME}: ${OBJS}
	@printf "\bdone\n"
	@${CC} ${LDFLAGS} -g -o ${NAME} ${OBJS}
	@install_name_tool -change libmlx.dylib @executable_path/${LIBMLX_DIR}/libmlx.dylib ${NAME}
	@echo "Build ${NAME}: done"


${OBJS}: ${LIBMLX}


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


${OBJS_DIR}:
	@echo "Build ${NAME}"
	@mkdir -p ${OBJS_DIR}
	@mkdir -p ${OBJS_DIR}/game
	@mkdir -p ${OBJS_DIR}/parse
	@mkdir -p ${OBJS_DIR}/raycast
	@mkdir -p ${OBJS_DIR}/render


${LIBFT}:
	@${MAKE} -C ${LIBFT_DIR}


${LIBGNL}: ${LIBFT}
	@${MAKE} -C ${LIBGNL_DIR}


${LIBMLX}: ${LIBGNL}
	@${MAKE} -C ${LIBMLX_DIR}


clean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${LIBFT_DIR} clean
	@make -C ${LIBGNL_DIR} clean
	@make -C ${LIBMLX_DIR} clean
	@rm -rf ${OBJS_DIR}


fclean:
	@echo "Remove dependencies in ${NAME}"
	@make -C ${LIBFT_DIR} fclean
	@make -C ${LIBGNL_DIR} fclean
	@make -C ${LIBMLX_DIR} fclean
	@echo "Remove ${NAME}"
	@rm -rf ${OBJS_DIR}
	@${RM} ${NAME}
	

re:
	@echo "Re-build ${NAME}"
	@make fclean
	@make all


.PHONY: all clean fclean re bonus


-include ${DEPS}