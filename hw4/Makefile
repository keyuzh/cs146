all: every srm unrm trash

every: every.c
	gcc every.c -o every -g

srm: srm.c helper.c
	gcc srm.c helper.c -o srm -g

unrm: unrm.c helper.c
	gcc unrm.c helper.c -o unrm -g

trash: trash.c helper.c
	gcc trash.c helper.c -o trash -g

clean:
	rm -f every srm unrm trash
