APP := btctl


all: 
	gcc -g btctl.c -o $(APP)

format:
	find . -regex '.*\.\(c\|h\)' -exec clang-format -style=file -i {} \;

clean:
	rm -rf $(APP)

