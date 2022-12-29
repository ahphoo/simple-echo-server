CC=gcc
CFLAGS= -Wall
INC= -Iinc/
SOURCE=./src/
BIN=./bin/

LIBNAMES=echo_lib.c rio_lib.c
LIBS=$(addprefix $(SOURCE)/, $(LIBNAMES))

PROG=echo_client echo_server
LIST=$(addprefix $(BIN)/, $(PROG))

all: $(LIST)

$(BIN)/%:  $(SOURCE)%.c
	$(CC) -o $@ $(INC) $< $(CFLAGS) $(LIBS)

clean:
	rm $(BIN)*
