priorityq.o: priorityq.c ../../include/sorted_list.h \
 ../../include/dlist.h priorityq.h
priorityq_test.o: priorityq_test.c priorityq.h \
 ../../include/sorted_list.h ../../include/dlist.h
