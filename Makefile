

CC          = 	gcc
BIN_DIR     = 	bin
CFLAGS      =   -Wall
BIN         = 	${BIN_DIR}/main
SRCS        = 	$(wildcard src/*.c)
OBJS        = 	$(SRCS:src/%.c=obj/%.o)

all: ${BIN}

${BIN}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^


.SECONDARY: obj/main.o


obj/%.o: src/%.c
	${CC} ${CFLAGS} -c -o $@ $^

.PHONY: clean all

.SILENT: all

clean:
	rm -f ${BIN} ${OBJS}



