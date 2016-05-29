CC= g++
CFLAG = -o
LIB_DIR = /usr/local/lib
RM = rm -f
demo: Trie.o demo.o
	${CC} -o demo demo.o Trie.o 
demo.o: demo.cc Trie.h
	${CC} -c demo.cc   
Trie.o: Trie.cc Trie.h
	${CC} -c Trie.cc   
clean:
	$(RM) *.o demo 
