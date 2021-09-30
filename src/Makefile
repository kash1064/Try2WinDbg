EXE := main.exe
SOURCE_DIR := cpp
MINGW_CPP := x86_64-w64-mingw32-g++

%.exe: ${SOURCE_DIR}/%.cpp
	${MINGW_CPP} $< -o $@

all: ${EXE}