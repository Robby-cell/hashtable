
CC := "gcc"
DEFAULT := "bin/map"

build: (compile) (link DEFAULT) 

SRCS := replace(`ls src`, "\n", " ")

[unix]
compile:
    @for file in {{ SRCS }}; do \
        echo "COMPILING src/$file" ; \
        {{ CC }} -c -o obj/{{ "$file" }}.o src/{{ "$file" }} ; \
        echo "COMPILED src/{{ "$file" }} -> obj/{{ "$file" }}.o" ; \
    done ;
    
[unix]
@link target:
    echo "LINKING..."
    {{ CC }} -o {{ target }} obj/*.c.o
    echo "DONE"

#[windows]
default:
    @echo "Why are you on windows"
