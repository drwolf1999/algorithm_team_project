GPP = g++
CFLAGS = -DNDEBUG -lm -static -std=c++14 -DONLINE_JUDGE -DBOJ -O3 -O0

# generate runfile

main: doyeop.o file_manager.o main.cpp
	$(GPP) $(CFLAGS) -o main.exe doyeop.o file_manager.o main.cpp

# generate object file

doyeop.o: doyeop.h doyeop.cpp utils.o
	$(GPP) $(CFLAGS) -c -o doyeop.o doyeop.cpp

file_manager.o: file_manager.h file_manager.cpp
	$(GPP) $(CFLAGS) -c -o file_manager.o file_manager.cpp

# utils.o: utils.h
# 	$(GPP) $(CFLAGS) -c -o utils.o utils.h
	
# clean object, executer files
clean:
	rm *.o *.exe