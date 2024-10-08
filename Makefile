display: display.c pointcloud.c bmp.c util.c
	gcc -Wall -g -o display display.c pointcloud.c bmp.c util.c -lm

stat1: parta.c pointcloud.c util.c bmp.c
	gcc -Wall -g -o stat1 parta.c pointcloud.c util.c bmp.c -lm 

clean:
	rm -f display stat1

