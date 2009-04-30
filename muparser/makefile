MUP_OBJ=muParserBase.o muParser.o muParserInt.o\
	muParserBytecode.o muParserDLL.o\
	 muParserTest.o\
	muParserCallback.o muParserError.o\
	 muParserTokenReader.o

libmuparser.a:$(MUP_OBJ)
	$(AR) $@ *.o

.cpp.o:
	$(CXX) $< $(CXXFLAGS)

clean:
	$(RM) *.o


