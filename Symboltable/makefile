include ../Constants.mk

makeTestSymboltable: $(BINDIRTEST)/TestSymboltable.o SymboltableOBJTarget
	$(CC) $(LFLAGS) -o $(BINDIRTEST)/SymboltableTest.out ../$(COMMONDIR)/$(OBJDIR)/*.o $(OBJDIR)/*.o $(<)

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	$(CC) $(CFLAGS)  $(<) -o $(@)

$(BINDIRTEST)/TestSymboltable.o: $(SRCDIR)/TestSymboltable.cpp $(HEADERDIR)/Symboltable.h
	$(CC) $(CFLAGS) $(<) -o $(@)


.PHONY: cleanSymboltable SymboltableOBJTarget
cleanSymboltable:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*

SymboltableOBJTarget: $(OBJDIR)/StringTable.o $(OBJDIR)/Symboltable.o $(OBJDIR)/Token.o
