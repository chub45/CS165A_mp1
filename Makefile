CC = g++
CFlags = -c -g -Wall
DEPS = 
LDFLAGS = 
SOURCES = NaiveBayesClassifier.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = NaiveBayesClassifier

NaiveBayesClassifier: NaiveBayesClassifier.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm *.o NaiveBayesClassifier
