
stat1: parta.c
	gcc -Wall -g -o stat1 parta.c

clean:
	rm -f stat1

readPointCloudData: pointcloud.c
	gcc -Wall -g -o readPointCloudData pointcloud.c