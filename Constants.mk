CC := g++
HEADERDIR := includes
SRCDIR := src
OBJDIR := objs
BINDIRTEST := debug

DEBUG := -g -DDEBUG
OPTIMIZE := -O2
CFLAGS = -Wall -Wextra -std=c++11 -march=native $(OPTIMIZE) -c
LFLAGS = -Wall $(OPTIMIZE)

AUTOMATDIR := Automat
BUFFERDIR := Buffer
COMMONDIR := Common
SYMBOLTABLEDIR := Symboltable
SCANNERDIR := Scanner
PARSERDIR := Parser
