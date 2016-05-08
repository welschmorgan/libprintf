NAME=libftprintf.a
NAME_D=libftprintf_d.a

LIBFT_DIR=./libft

LIBFT_INC_DIR=$(LIBFT_DIR)/includes
LIBFT_OBJ_DIR=$(LIBFT_DIR)/objs
LIBFT_SRC_DIR=$(LIBFT_DIR)/srcs

INC_DIR=./includes
SRC_DIR=./srcs
OBJ_DIR=./objs

UNITS=$(patsubst %.c,$(SRC_DIR)/%.c,$(shell ls $(SRC_DIR) | grep .c))
HEADERS=$(patsubst %.h,$(INC_DIR)/%.h,$(shell ls $(INC_DIR) | grep .h))
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(UNITS))
OBJS_D=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%_d.o,$(UNITS))
NUM_OBJS=`echo "$(OBJS)" | wc -w`

PP_CFLAGS=-g -pg -fno-omit-frame-pointer -O2 -DNDEBUG -fno-inline-functions -fno-inline-functions-called-once -fno-optimize-sibling-calls
DBG_CFLAGS=-g -ggdb -D_DEBUG
RLS_CFLAGS=-O3 -DNDEBUG

CFLAGS=-I$(LIBFT_INC_DIR) -I$(INC_DIR) -Wall -Werror -Wextra -std=c89 -D_XOPEN_SOURCE=500

CC=gcc
LD=ar -rcs

default: $(NAME)
all: debug release

debug: $(NAME_D)

release: $(NAME)

$(NAME): $(OBJS)
	@printf "\nLink %s (%d objects)\n" "$@" "$(NUM_OBJS)"
	@$(LD) $@ $^

$(NAME_D): $(OBJS_D)
	@printf "\nLink %s (%d objects)\n" "$@" "$(NUM_OBJS)"
	@$(LD) $@ $^


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\r\033[KCompile '%s'" $^
	@$(CC) -o $@ $(CFLAGS) -c $^

$(OBJ_DIR)/%_d.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@printf "\r\033[KCompile '%s'" $^
	@$(CC) -o $@ $(CFLAGS) -ggdb -c $^

test:
	make -C $@

clean:
	@printf "Removing %d objects\n" "$(NUM_OBJS)"
	@make clean -C test
	@rm -f $(OBJS)

fclean: clean
	@printf "Removing %s\n" "$(NAME)"
	@make fclean -C test
	@rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all re clean fclean test debug release default
