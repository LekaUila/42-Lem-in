# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 15:13:59 by lflandri          #+#    #+#              #
#    Updated: 2024/04/08 15:18:03 by lflandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



ifndef BONUS
SRC		= Mandatory/main.c \
		  Mandatory/parsing.c \
		  Mandatory/checkPath.c \
		  Mandatory/algo.c \
		  Mandatory/antsSwitcher.c \
		  Mandatory/algo_recurcive.c
endif

ifdef BONUS
SRC		= Bonus/main.c \
		  Bonus/parsing.c \
		  Bonus/checkPath.c \
		  Bonus/hook_file.c \
		  Bonus/AMI_function.c \
		  Bonus/draw_image.c \
		  Bonus/algo.c \
		  Bonus/antsSwitcher.c \
		  Bonus/algo_recurcive.c
endif


NAME 		= lem-in
NAMEL		= ./libft/libft.a
NAMEMLX		= ./minilibx-linux/libmlx_Linux.a

MAKEFLAGS	= --no-print-directory

#couleur
BLACK		=\\e[0;30m
GREY		=\\e[1;30m
BLACKRED	=\\e[0;31m
PINK		=\\e[1;31m
BLACKGREEN	=\\e[0;32m
WHITEGREEN	=\\e[1;32m
ORANGE		=\\e[0;33m
YELLOW		=\\e[1;33m
BLACKBLUE	=\\e[0;34m
WHITEBLUE	=\\e[1;34m
BLACKPURPLE	=\\e[0;35m
WHITEPURPLE	=\\e[;1;35m
BLACKCYAN	=\\e[0;36m
WHITECYAN	=\\e[1;36m
WHITEGREY	=\\e[0;37m
WHITE		=\\e[1;37m

NEUTRE		= \\e[0;m

#effect
BLINK		=\\e[5m

RESET		=\\e[25m

all :		${NAME}
			@echo "${WHITEGREEN}PROGRAMME \"${BLINK}${NAME}${RESET}\" PRET POUR EXECUTION !${NEUTRE}"

${NAMEL}:
			@cd libft && make

ifdef BONUS

${NAME}: ${NAMEL} ${NAMEMLX} ${SRC}
			@echo "${BLACKPURPLE}=============== CRÉATION LEM-IN ==============${WHITE}" 
			gcc -g -Wall -Wextra -Werror ${SRC} -Lminilibx-linux -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz ${NAMEL} ${NAMEMLX} -o ${NAME}
			@echo "${BLACKPURPLE}============= FIN CRÉATION LEM-IN ============${NEUTRE}" 
endif

ifndef BONUS
${NAME}: ${NAMEL} ${SRC}
			@echo "${BLACKPURPLE}=============== CRÉATION LEM-IN ==============${WHITE}" 
			gcc -g -Wall -Wextra -Werror ${SRC}  ${NAMEL} -o ${NAME}
			@echo "${BLACKPURPLE}============= FIN CRÉATION LEM-IN ============${NEUTRE}"
endif

${NAMEMLX}:
			@echo "${BLACKPURPLE}=============== CRÉATION MINILIBX ============${WHITE}" 
			@cd minilibx-linux && make
			@echo "${BLACKPURPLE}============= FIN CRÉATION MINILIBX ==========${NEUTRE}" 
			@echo "${WHITEGREEN}Bibliotheque \"${BLINK}libmlx_Linux.a${RESET}\" PRET À L'EMPLOIE !${NEUTRE}"

bonus :
			@make BONUS=42

clean :
			@echo -n "${BLACKRED}"
			rm -f ${PO}
			@echo -n "${NEUTRE}"
			@cd libft && make clean

fclean :	clean
			@cd minilibx-linux && make clean
			@cd libft && make fclean
			@echo -n "${BLACKRED}"
			rm -f ${NAME}
#			rm -f ${NAMEV}
			@echo -n "${NEUTRE}"

# bonus : 	${NAMEV}
# 			@echo "${WHITEGREEN}PROGRAMME \"${BLINK}${NAMEV}${RESET}\" PRET POUR EXECUTION !${NEUTRE}"


re :		fclean all

# rebonus : fclean bonus

# reall : fclean all bonus

.PHONY : all clean fclean re bonus
