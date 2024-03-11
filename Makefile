


SRC		= main.c \
		  parsing.c


SRCBONUS 	= 
NAME 		= lem-in
NAMEL		= ./libft/libft.a

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

${NAME}: ${NAMEL} ${SRC}
			@echo "${BLACKPURPLE}=============== CRÉATION CLIENT ==============${WHITE}" 
			gcc -g -Wall -Wextra -Werror  -o ${NAME} ${SRC} ${NAMEL}
			@echo "${BLACKPURPLE}============= FIN CRÉATION CLIENT ============${NEUTRE}" 


clean :
			@echo -n "${BLACKRED}"
			rm -f ${PO}
			@echo -n "${NEUTRE}"
			@cd libft && make clean

fclean :	clean
			@cd libft && make fclean
			@echo -n "${BLACKRED}"
			rm -f ${NAME}
			@echo -n "${NEUTRE}"

bonus :
			@make BONUS=42

re :		fclean all

rebonus : fclean bonus

.PHONY : all clean fclean re bonus