all: gen parsort sort parconvex_hull convex_hull

sort: sort.cpp
	g++ -o sort sort.cpp

parsort: parsort.cpp
	g++ -pthread -o parsort parsort.cpp

gen: gen.cpp
	g++ -o gen gen.cpp

convex_hull: convex_hull.cpp
	g++ -o convex_hull convex_hull.cpp

parconvex_hull: parconvex_hull.cpp
	g++ -pthread -o parconvex_hull parconvex_hull.cpp

.phony: all
