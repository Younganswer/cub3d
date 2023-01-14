SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

SRCS_DIR	:= ./srcs
OBJS_DIR	:= ./objs
INCS_DIR	:= ./incs

MODULE_SRCS	:= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_SRCS	:= ${addprefix ${SRCS_DIR}/, ${MODULE_SRCS}}
MODULE_OBJS	:= ${MODULE_SRCS:${SRCS_DIR}/%.swift=${OBJS_DIR}/%.swiftmodule}

SRCS	:= interface.swift
SRCS	:= ${addprefix ${SRCS_DIR}/, ${SRCS}}
SRCS	:= ${SRCS} ${MODULE_SRCS}
OBJS	:= ${SRCS:${SRCS_DIR}/%.swift=${OBJS_DIR}/%.o}

C_SRCS	:= mlx_xpm.c mlx_png.c mlx_string_put.c
C_SRCS	:= ${addprefix ${SRCS_DIR}/, ${C_SRCS}}
C_OBJS	:= ${C_SRCS:${SRCS_DIR}/%.c=${OBJS_DIR}/%.o}

CC		:= gcc
CFLAGS	:= -O3

NAME	:= libmlx.dylib
#OPTI	:= -Ounchecked


all: ${NAME}


${NAME}: ${C_OBJS}
	@printf "\bdone\n"
	@swiftc ${OPTI} -o ${NAME} -emit-library ${OBJS} ${C_OBJS} -lz
	@echo "Build ${NAME}: done"


${OBJS_DIR}:
	@mkdir -p $@


${C_OBJS}: ${OBJS}


${OBJS}: ${MODULE_OBJS}


${MODULE_OBJS}: ${OBJS_DIR}


${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	${eval IDX = ${shell expr ${IDX} + 1}}
	${eval T_IDX = ${shell expr ${IDX} % 32}}
	${eval T_IDX = ${shell expr ${T_IDX} / 8 + 1}}
	${eval CHR = ${shell echo ${SPINNER} | cut -c ${T_IDX}}}
	@if [ ${IDX} = 1 ]; then\
		echo -n "Build dependencies in ${NAME} ...  ";\
	fi
	@printf "\b${CHR}"
	@${CC} ${CFLAGS} -c $< -o $@ -I${INCS_DIR}


${OBJS_DIR}/%.o: ${SRCS_DIR}/%.swift
	${eval IDX = ${shell expr ${IDX} + 1}}
	${eval T_IDX = ${shell expr ${IDX} % 32}}
	${eval T_IDX = ${shell expr ${T_IDX} / 8 + 1}}
	${eval CHR = ${shell echo ${SPINNER} | cut -c ${T_IDX}}}
	@if [ ${IDX} = 1 ]; then\
		echo -n "Build dependencies in ${NAME} ...  ";\
	fi
	@printf "\b${CHR}"
	@swiftc ${OPTI} -parse-as-library -c $< -o $@ -I${OBJS_DIR}


${OBJS_DIR}/%.swiftmodule: ${SRCS_DIR}/%.swift
	${eval IDX = ${shell expr ${IDX} + 1}}
	${eval T_IDX = ${shell expr ${IDX} % 32}}
	${eval T_IDX = ${shell expr ${T_IDX} / 8 + 1}}
	${eval CHR = ${shell echo ${SPINNER} | cut -c ${T_IDX}}}
	@if [ ${IDX} = 1 ]; then\
		echo -n "Build dependencies in ${NAME} ...  ";\
	fi
	@printf "\b${CHR}"
	@swiftc ${OPTI} -parse-as-library -c $< -o $@ -emit-module -module-name ${patsubst srcs/%.swift,%,$<} -module-link-name ${patsubst srcs/%.swift,%,$<} -I${OBJS_DIR}


clean:
	@echo "Remove dependencies in ${NAME}"
	@rm -rf ${OBJS_DIR}


fclean: clean
	@echo "Remove ${NAME}"
	@rm -rf ${NAME}