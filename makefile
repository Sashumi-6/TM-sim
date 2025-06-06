run: main.exe
	./$?

main.exe: file-main
	g++ $(wildcard *.cpp) -o $@

clean:
	rm -f main.exe

file-main:
	touch main.cpp