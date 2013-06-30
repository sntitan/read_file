obj_path = ./obj
obj_file_reader = readin_file_ele.o
file_root_path = ./func
file_ut_path = ./ut
file_reader : $(obj_file_reader)
	cc -o file_reader $(obj_file_reader)

readin_file_ele.o : $(file_root_path)/readin_file_ele.c $(file_root_path)/readin_file_ele.h
	cc -c $(file_root_path)/readin_file_ele.c
ele_analys.o : $(file_root_path)/ele_analys.c $(file_root_path)/ele_analys.h
	cc -c $(file_root_path)/ele_analys.c

clean :
	rm $(obj_file_reader)

ut_readin_file_ele_obj = readin_file_ele.o ut_readin_file_ele.o
ut_readin_file_ele : $(ut_readin_file_ele_obj)
	cc -o readin_file_ut $(ut_readin_file_ele_obj)
clean_ut_read_file_ele :
	rm $(ut_readin_file_ele_obj) 
ut_readin_file_ele.o : $(file_ut_path)/ut_readin_file_ele.c
	cc -c $(file_ut_path)/ut_readin_file_ele.c

ut_ele_analys_obj = ele_analys.o ut_ele_analys.o readin_file_ele.o
ut_ele_analys : $(ut_ele_analys_obj)
	cc -o ele_analys_ut $(ut_ele_analys_obj)
clean_ut_ele_analys :
	rm $(ut_ele_analys_obj)
ut_ele_analys.o : $(file_ut_path)/ut_ele_analys.c
	cc -c $(file_ut_path)/ut_ele_analys.c
