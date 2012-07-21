all:		splay test gen


test:		stl.cpp
	g++ stl.cpp -O2 -o stl


splay:		splay_bottom_up.cpp splay_top_down.cpp
	g++ splay_bottom_up.cpp -O2 -o Splay_BU
	g++ splay_top_down.cpp -O2 -o Splay_TD


gen:		gen.cpp
	g++ gen.cpp -O3 -o gen

clean:
	rm Splay_BU Splay_TD stl gen
	rm in me std
