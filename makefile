CC = gcc
CPLUS = g++
#Using -Ofast instead of -O3 might result in faster code, but is supported only by newer GCC versions
CFLAGS = -std=c++11 -lm -pthread -O3 -march=native -Wall -funroll-loops -Wno-unused-result -lboost_serialization
MYSQLFLAGS = `mysql_config --cflags --libs`

all: word2vec word2phrase distance word-analogy compute-accuracy

word2vec : word2vec.c
	$(CPLUS) word2vec.c -o word2vec $(MYSQLFLAGS) $(CFLAGS)
word2phrase : word2phrase.c
	$(CC) word2phrase.c -o word2phrase $(CFLAGS)
distance : distance.c
	$(CC) distance.c -o distance $(CFLAGS)
word-analogy : word-analogy.c
	$(CC) word-analogy.c -o word-analogy $(CFLAGS)
compute-accuracy : compute-accuracy.c
	$(CC) compute-accuracy.c -o compute-accuracy $(CFLAGS)
	chmod +x *.sh
SynonymMap : SynonymMap.cpp
	$(CPLUS) SynonymMap.cpp -o generateSynonymMap $(MYSQLFLAGS) $(CFLAGS)

clean:
	rm -rf word2vec word2phrase distance word-analogy compute-accuracy
