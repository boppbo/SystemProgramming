CC := g++
HEADERDIR := includes
SRCDIR := src
OBJDIR := objs
BINDIRTEST := debug

DEBUG := -g
OPTIMIZE := -O2
CFLAGS = -Wall -Wextra $(OPTIMIZE) -c
LFLAGS = -Wall $(OPTIMIZE)

AUTOMATDIR := Automat
BUFFERDIR := Buffer
COMMONDIR := Common
SYMBOLTABLEDIR := Symboltable
SCANNERDIR := Scanner
