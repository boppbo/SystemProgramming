include ../Constants.mk

makeTestParser: $(BINDIRTEST)/TestParser.o ParserOBJTarget
	$(CC) $(LFLAGS) -o $(BINDIRTEST)/TestParser.out $(<) $(OBJDIR)/*.o ../$(AUTOMATDIR)/$(OBJDIR)/*.o ../$(BUFFERDIR)/$(OBJDIR)/*.o ../$(COMMONDIR)/$(OBJDIR)/*.o ../$(SCANNERDIR)/$(OBJDIR)/*.o ../$(SYMBOLTABLEDIR)/$(OBJDIR)/*.o

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	$(CC) $(CFLAGS)  $(<) -o $(@)

$(BINDIRTEST)/TestParser.o : $(SRCDIR)/TestParser.cpp $(HEADERDIR)/Parser.h
	$(CC) $(CFLAGS) $(<) -o $(@)

.PHONY: cleanParser
cleanParser:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*

ParserOBJTarget: $(OBJDIR)/Leaf.o $(OBJDIR)/Node.o $(OBJDIR)/Parser.o $(OBJDIR)/Tree.o $(OBJDIR)/TreeVisitor.o $(OBJDIR)/TreeVisitorCodeGeneration.o $(OBJDIR)/TreeVisitorPrintTree.o $(OBJDIR)/TreeVisitorTypeCheck.o
