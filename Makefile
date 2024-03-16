swim_mgr:main.o manage.o mem_list.o sha.o user_mgr.o
	gcc main.o manage.o mem_list.o sha.o user_mgr.o -o swim_mgr

main.o:main.c manage.o
	gcc -c main.c
	
manage.o:manage.c 
	gcc -c manage.c

mem_list.o:mem_list.c
	gcc -c mem_list.c

sha.o:sha.c
	gcc -c sha.c

user_mgr.o:user_mgr.c
	gcc -c user_mgr.c

clean:
	rm -rf *.o swim_mgr 
	rm mem_info_dat user_info.dat
