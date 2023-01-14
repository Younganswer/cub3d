SHELL	= /bin/bash
SPINNER	= /-\|/
IDX		= 0

MODULE_SRCS	:= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJS	:= $(MODULE_SRC:.swift=.swiftmodule)

INCS	:= .
SRCS	:= interface.swift $(MODULE_SRC)
OBJS	:= $(SRCS:.swift=.o)

C_SRCS	:= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJS	:= $(C_SRCS:.c=.o)
CFLAGS	:= -O3

NAME	:= libmlx.dylib
#OPTI	:= -Ounchecked


all: $(NAME)


$(NAME): $(MODULE_OBJ) $(C_OBJS) $(OBJS)
	@printf "\bdone\n"
	@swiftc $(OPTI) -o $(NAME) -emit-library $(OBJS) $(C_OBJS) -lz -I$(INCS)
	@echo "Build ${NAME}: done"


%.o: %.swift
	${eval IDX = ${shell expr ${IDX} + 1}}
	${eval T_IDX = ${shell expr ${IDX} % 32}}
	${eval T_IDX = ${shell expr ${T_IDX} / 8 + 1}}
	${eval CHR = ${shell echo ${SPINNER} | cut -c ${T_IDX}}}
	@if [ ${IDX} = 1 ]; then\
		echo -n "Build dependencies in ${NAME} ...  ";\
	fi
	@printf "\b${CHR}"
	@swiftc $(OPTI) -parse-as-library -c $< -o $@ -I$(INCS)


%.swiftmodule: %.swift
	@swiftc $(OPTI) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<) -I$(INCS)


clean:
	@echo "Remove dependencies in ${NAME}"
	@rm -f $(OBJS) $(MODULE_OBJS) $(C_OBJS) *.swiftdoc *~


fclean: clean
	@echo "Remove ${NAME}"
	@rm -f $(NAME)