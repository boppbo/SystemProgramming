CC := g++
HEADERDIR := includes
SRCDIR := src
OBJDIR := objs
BINDIRTEST := debug

DEBUG := -g
OPTIMIZE := -O2
CFLAGS = -Wall -Wextra $(DEBUG) -c
LFLAGS = -Wall $(DEBUG)

AUTOMATDIR := Automat
BUFFERDIR := Buffer
COMMONDIR := Common
SYMBOLTABLEDIR := Symboltable
SCANNERDIR := Scanner
