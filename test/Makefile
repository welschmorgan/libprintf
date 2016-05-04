INC_DIR=includes
COMM_DIR=common
TPL_DIR=template

TSTS=$(shell find . -maxdepth 1 -mindepth 1 -type d | grep -v "$(COMM_DIR)\|$(TPL_DIR)" )
HDRS=$(shell find . -maxdepth 1 -name "*.h") $(shell find common -maxdepth 1 -name "*.h")
SRCS=$(shell find . -maxdepth 1 -name "*.c")
CSRCS=$(shell find common -maxdepth 1 -name "*.c")
OBJS=$(patsubst %.c,%.o,$(SRCS))
COBJS=$(patsubst %.c,%.o,$(CSRCS))
APPS=$(patsubst %.c,%.run,$(SRCS))
NOBJS=$(shell echo $(OBJS) $(COBJS) | wc -w)

LIBFT_DIR=../libft
LIBFTPRINTF_DIR=..

CFLAGS = -Wall -Wextra -Werror -I. -I.. -I$(LIBFT_DIR)/$(INC_DIR) -I$(LIBFTPRINTF_DIR)/$(INC_DIR) -I$(COMM_DIR) -g
LDFLAGS = -L$(LIBFT_DIR)/ -L$(LIBFTPRINTF_DIR)/ -lft -lftprintf

CC = clang
LD = $(CC)

SHELL=/bin/bash
COUNT=0
VOID_STDERR=2>/dev/null

common/%.o: common/%.c
	@PRCT=$$( echo "scale=1; $(COUNT) / $(NOBJS) * 100.0" | bc $(VOID_STDERR) ); \
	printf "\r\033[K[$(CC)|%s%%] Compiling %s into %s ... " "$$PRCT" "$<" "$@"; \
	$(CC) $(CFLAGS) -c -o $@ $^; \
	$(eval COUNT = $(shell echo "$(COUNT) + 1" | bc) ) \
	printf "\r\033[K[$(CC)|%s%%] Compiled %s into %s ... " "$$PRCT" "$<" "$@"; \

%.o: %.c
	@PRCT=$$( echo "scale=1; $(COUNT) / $(NOBJS) * 100.0" | bc $(VOID_STDERR) ); \
	printf "\r\033[K[$(CC)|%s%%] Compiling %s into %s ... " "$$PRCT" "$<" "$@"; \
	$(CC) $(CFLAGS) -c -o $@ $^; \
	$(eval COUNT = $(shell echo "$(COUNT) + 1" | bc) ) \
	printf "\r\033[K[$(CC)|%s%%] Compiled %s into %s ... " "$$PRCT" "$<" "$@"; \

%.run: %.o $(COBJS)
	@PRCT=$$( echo "scale=1; $(COUNT) / $(NOBJS) * 100.0" | bc $(VOID_STDERR) ); \
	printf "\r\033[K[$(CC)|%s%%] Linking $@" "$$PRCT" ; \
	$(LD) -o $@ $^ $(LDFLAGS) ; \
	printf "\r\033[K[$(CC)|%s%%] Linked $@\n" "$$PRCT";

all: $(COBJS) $(OBJS) $(APPS)
	@for TEST in $(TSTS); do make -C $$TEST -f ../$(TPL_DIR)/Makefile; done

clean:
	@NOBJS=$$(find . -mindepth 1 -maxdepth 1 -name "*.o" | wc -w | sed 's/ //g' ); \
	[ $$NOBJS -gt 0 ] && echo "common: removing $$NOBJS object(s): $(OBJS) $(COBJS)."; \
	rm -f $(OBJS) $(COBJS)
	@for TEST in $(TSTS); do make clean -C $$TEST -f ../$(TPL_DIR)/Makefile; done

fclean: clean
	@NAPPS=$$(find . -mindepth 1 -maxdepth 1 -name "*.run" | grep -v "dSYM" | wc -w | sed 's/ //g' ); \
	[ $$NAPPS -gt 0 ] && echo "common: removing $$NAPPS target(s)."; \
	rm -f $(APPS)
	@for TEST in $(TSTS); do make fclean -C $$TEST -f ../$(TPL_DIR)/Makefile; done

run:
	@RUNS=$$(find . -name "*.run" -type f); \
	printf "Starting %d tests ...\n" $$(echo $$RUNS | wc -w); \
	for APP in $$RUNS; do \
		echo Starting test $$APP ...; \
		$$APP; \
		echo; \
	done

re: fclean all

.PHONY: clean fclean re all
