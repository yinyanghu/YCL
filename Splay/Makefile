all:		splay test gen


test:		stl.cpp
	g++ stl.cpp -O2 -o stl


splay:		BU.cpp BUS.cpp TD.cpp TDS.cpp PBU.cpp PTD.cpp
	g++ BU.cpp -O2 -o Splay_BU
	g++ TD.cpp -O2 -o Splay_TD
	g++ BUS.cpp -O2 -o Splay_BUS
	g++ TDS.cpp -O2 -o Splay_TDS
	g++ PBU.cpp -O2 -o Splay_PBU
	g++ PTD.cpp -O2 -o Splay_PTD


gen:		gen.cpp
	g++ gen.cpp -O3 -o gen

clean:
	rm Splay_BU Splay_TD
	rm stl gen
	rm Splay_PBU Splay_PTD
	rm Splay_BUS Splay_TDS
	rm in me std
