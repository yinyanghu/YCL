all:		splay test gen


test:		stl.cpp
	g++ stl.cpp -O2 -o stl


splay:		splay_bottom_up.cpp splay_top_down.cpp splay_bottom_up_size.cpp splay_top_down_size.cpp
	g++ splay_bottom_up.cpp -O2 -o Splay_BU
	g++ splay_top_down.cpp -O2 -o Splay_TD
	g++ splay_bottom_up_size.cpp -O2 -o Splay_BUS
	g++ splay_top_down_size.cpp -O2 -o Splay_TDS


gen:		gen.cpp
	g++ gen.cpp -O3 -o gen

clean:
	rm Splay_BU Splay_TD stl gen
	rm Splay_BUS Splay_TDS
	rm in me std
