graf : graf.cc algorithms.cc random_graphs.cc
	g++ -o graf graf.cc random_graphs.cc algorithms.cc -I.

clean :
	rm -f *.o