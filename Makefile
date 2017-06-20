appname:=foguetinha
compile:
	@g++ main.cpp \
	-I /usr/include/opencv \
	-L /usr/lib \
	`pkg-config --cflags --libs opencv` \
	-o $(appname)
	
run:
	@./$(appname) entrada.txt > saida.txt
	#gedit saida.txt &
	gnuplot5-qt plot.gnu -persist
	
all: compile run
