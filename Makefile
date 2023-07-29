

CC 					= 	gcc
BIN_DIR 		= 	bin
CFLAGS 			=
BIN 			  = 	${BIN_DIR}/main
SRCS 				= 	$(wildcard src/*.c)
BINS 				= 	$(SRCS:src/%.c=bin/%)
OBJS 				= 	$(wildcard obj/*.o)

all: ${BIN}

${BIN_DIR}/%: obj/%.o
	${CC} ${CFLAGS} -o $@ $^


.SECONDARY: obj/main.o


obj/%.o: src/%.c
	${CC} ${CFLAGS} -c -o $@ $^

.PHONY: clean all

.SILENT: all

clean:
	rm -f ${BINS} ${OBJS}



