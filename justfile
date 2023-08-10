
CC := "gcc"
DEFAULT := "bin/map"

SRCS := replace(`ls src`, "\n", " ")

build: (compile) (link DEFAULT) 

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

[windows]
@link target:
    echo "LINKING..."
    {{ CC }} -o {{ target }}.exe obj/*.c.o
    echo "DONE"
