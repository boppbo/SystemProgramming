include ../Constants.mk

makeTestAutomat: $(BINDIRTEST)/TestAutomat.o AutomatOBJTarget 
	$(CC) $(LFLAGS) -o $(BINDIRTEST)/AutomatTest.out $(OBJDIR)/*.o $(<) 
	
$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	$(CC) $(CFLAGS)  $(<) -o $(@)

$(BINDIRTEST)/TestAutomat.o :  $(SRCDIR)/TestAutomat.cpp $(HEADERDIR)/Automat.h
	$(CC) $(CFLAGS) $(<) -o $(@)

.PHONY: cleanAutomat AutomatOBJTarget
cleanAutomat:
	rm -f objs/*.o
	rm -f debug/*
	
AutomatOBJTarget: $(OBJDIR)/Automat.o
