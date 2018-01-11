CC=g++ -std=c++11
OPTS=
INCS=
LIBS=

%.o: %.cpp
	$(CC) $(OPTS) $(INCS) -c $<

go: main.o directedGraph.o
	$(CC) $(OPTS) $(INCS) -o $@ $^  $(LIBS)

run: go
	@./go

clean:
	rm -f go *.o 

