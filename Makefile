base:
	clang++ -fsanitize=undefined -fsanitize=bounds --std=c++20 main.cpp -o build/main.exe
	./build/main.exe

md5:
	clang++ -fsanitize=undefined -fsanitize=bounds --std=c++20 main.cpp md5.cpp -o build/main.exe
	./build/main.exe