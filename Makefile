appname:=foguetinha
compile:
	@g++ main.cpp -o $(appname)
	
run:
	@./foguetinha
	
all: compile run
