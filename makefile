SHELL := pwsh -NoProfile
CXX = g++
TARGET = recipe

CFLAGS := -Wall -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

$(TARGET):
	g++ -o recipe.exe main.cpp DataBase.cpp sqlite3.o $(CFLAGS)

sqlite:
	gcc -c sqlite3.c

clean:
	del obj\*.o
	del obj\deps\*.d
	del *.exe
	del *.db

include $(wildcard $(DEPS))