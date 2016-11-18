include ../Constants.mk

makeTestBuffer: $(BINDIRTEST)/TestBuffer.o BufferOBJTarget
	$(CC) $(LFLAGS) -o $(BINDIRTEST)/BufferTest.out ../$(COMMONDIR)/$(OBJDIR)/*.o $(OBJDIR)/*.o $(<)

$(OBJDIR)/GenericBuffer.o : $(SRCDIR)/GenericBuffer.cpp $(HEADERDIR)/GenericBuffer.h ../$(COMMONDIR)/$(HEADERDIR)/Collections/deque.h
	$(CC) $(CFLAGS) $(<) -o $(@)

$(OBJDIR)/Buffer.o :  $(SRCDIR)/Buffer.cpp $(HEADERDIR)/Buffer.h $(HEADERDIR)/GenericBuffer.h ../$(COMMONDIR)/$(HEADERDIR)/Collections/deque.h
	$(CC) $(CFLAGS) $(<) -o $(@)

$(BINDIRTEST)/TestBuffer.o :  $(SRCDIR)/TestBuffer.cpp $(HEADERDIR)/Buffer.h $(HEADERDIR)/GenericBuffer.h ../$(COMMONDIR)/$(HEADERDIR)/Collections/deque.h
	$(CC) $(CFLAGS) $(<) -o $(@)

# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren
cleanBuffer:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIRTEST)/*
	

# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer GesamtProjekt loeschen und dann neu erzeugen
BufferOBJTarget: $(OBJDIR)/GenericBuffer.o $(OBJDIR)/Buffer.o

	