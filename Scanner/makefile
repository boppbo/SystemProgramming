include ../Constants.mk

OBJS = $(OBJDIR)/Token.o $(OBJDIR)/Scanner.o

makeTestScanner: $(BINDIRTEST)/TestScanner.o $(OBJS)
	$(CC) $(LFLAGS) -o $(BINDIRTEST)/TestScanner.out $(<) $(OBJDIR)/*.o ../$(AUTOMATDIR)/$(OBJDIR)/*.o ../$(BUFFERDIR)/$(OBJDIR)/*.o ../$(COMMONDIR)/$(OBJDIR)/*.o ../$(SYMBOLTABLEDIR)/$(OBJDIR)/*.o

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	$(CC) $(CFLAGS)  $(<) -o $(@)

$(BINDIRTEST)/TestScanner.o : $(SRCDIR)/TestScanner.cpp $(HEADERDIR)/Scanner.h
	$(CC) $(CFLAGS) $(<) -o $(@)

.PHONY: cleanScanner
cleanScanner:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*


