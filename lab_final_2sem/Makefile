all: main.o database.o deliver.o order.o storage.o
	g++ main.o database.o deliver.o order.o storage.o -o a.out

main.o: main.cpp
	g++ -c main.cpp -IAll_hpp_files

database.o: All_cpp_files/database.cpp
	g++ -c All_cpp_files/database.cpp -IAll_hpp_files

deliver.o: All_cpp_files/deliver.cpp
	g++ -c All_cpp_files/deliver.cpp -IAll_hpp_files

order.o: All_cpp_files/order.cpp
	g++ -c All_cpp_files/order.cpp -IAll_hpp_files

storage.o: All_cpp_files/storage.cpp
	g++ -c All_cpp_files/storage.cpp -IAll_hpp_files

clean:
	rm *.o
	rm a.out