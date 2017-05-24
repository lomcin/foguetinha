appname:=foguetinha
compile:
	@g++ main.cpp \
	-I /usr/include/opencv \
	-L /usr/lib \
	`pkg-config --cflags --libs opencv` \
	-o $(appname)
	
run:
	@./$(appname)
	
all: compile run
