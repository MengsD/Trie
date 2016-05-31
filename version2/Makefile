CC= g++
RM = rm -f
demo: Trie.o demo.o
	${CC} -g -o demo demo.o Trie.o 
demo.o: demo.cc Trie.h
	${CC} -g -c demo.cc   
Trie.o: Trie.cc Trie.h
	${CC} -g -c Trie.cc   
clean:
	$(RM) *.o demo 
