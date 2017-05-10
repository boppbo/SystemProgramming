CC := g++
HEADERDIR := includes
SRCDIR := src
OBJDIR := objs
BINDIRTEST := debug

DEBUG := -g -DDEBUG
OPTIMIZE := -O2
CFLAGS = -Wall -Wextra -std=c++11 -march=native $(DEBUG) -c
LFLAGS = -Wall $(DEBUG)

AUTOMATDIR := Automat
BUFFERDIR := Buffer
COMMONDIR := Common
SYMBOLTABLEDIR := Symboltable
SCANNERDIR := Scanner
