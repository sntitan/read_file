obj_file_reader = readin_file_ele.o
file_root_path = ./func
file_ut_path = ./ut
file_reader : $(obj_file_reader)
	cc -o file_reader $(obj_file_reader)

readin_file_ele.o : $(file_root_path)/readin_file_ele.c $(file_root_path)/readin_file_ele.h
	cc -c $(file_root_path)/readin_file_ele.c

clean :
	rm $(obj_file_reader)

ut_file_file_ele_obj = readin_file_ele.o ut_readin_file_ele.o
ut_readin_file_ele : $(ut_file_file_ele_obj)
	cc -o readin_file_ut $(ut_file_file_ele_obj)

clean_ut_read_file_ele :
	rm $(ut_file_file_ele_obj) 

ut_readin_file_ele.o : $(file_ut_path)/ut_readin_file_ele.c
	cc -c $(file_ut_path)/ut_readin_file_ele.c
