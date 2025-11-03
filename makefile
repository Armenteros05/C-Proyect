all: main map_viewer

main: main.c map.c vehicle.c
	gcc main.c map.c vehicle.c -o main -lpthread

map_viewer: map_viewer.c map.c
	gcc map_viewer.c map.c -o map_viewer -lpthread

clean:
	rm -f main map_viewer
