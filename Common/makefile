include ../Constants.mk

makeTestCommon: $(BINDIRTEST)/TestCommon.o CommonOBJTarget
	$(CC) $(LFLAGS) -o $(BINDIRTEST)/CommonTest.out $(OBJDIR)/*.o $(<)

$(OBJDIR)/deque.o :  $(SRCDIR)/Collections/deque.cpp $(HEADERDIR)/Collections/deque.h 
	$(CC) $(CFLAGS) $(<) -o $(@)

$(OBJDIR)/trackingDeque.o :  $(SRCDIR)/Collections/trackingDeque.cpp $(HEADERDIR)/Collections/trackingDeque.h $(HEADERDIR)/Collections/deque.h 
	$(CC) $(CFLAGS) $(<) -o $(@)

$(OBJDIR)/cstring.o : $(SRCDIR)/cstring.cpp $(HEADERDIR)/cstring.h
	$(CC) $(CFLAGS) $(<) -o $(@)

$(BINDIRTEST)/TestCommon.o : $(SRCDIR)/TestCommon.cpp $(HEADERDIR)/cstring.h $(HEADERDIR)/Collections/deque.h
	$(CC) $(CFLAGS) $(<) -o $(@)


.PHONY: cleanCommon CollectionTarget CommonOBJTarget
cleanCommon:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIRTEST)/*

CollectionTarget : $(OBJDIR)/deque.o $(OBJDIR)/trackingDeque.o 

CommonOBJTarget: CollectionTarget $(OBJDIR)/cstring.o