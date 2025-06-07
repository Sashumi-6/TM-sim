run: main.exe
	./$?

main.exe: file-main file-tm file-tape
	g++ $(wildcard *.cpp) -o $@

clean:
	rm -f main.exe valgrind.log test.exe

valgrind: clean
	g++ -g $(wildcard *.cpp) -o test.exe
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log ./test.exe

file-main:
	touch main.cpp

file-tm:
	touch turingMachine.cpp

file-tape:
	touch tape.cpp