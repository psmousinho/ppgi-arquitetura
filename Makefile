CC = g++

all:
	$(CC) ./src/Main-LoopFusion.cpp -std=c++11 -o Main-LoopFusion
	$(CC) ./src/Main-RightLoop.cpp -std=c++11 -o Main-RightLoop
	$(CC) ./src/Main-RightLoopFusion.cpp -std=c++11 -o Main-RightLoopFusion
	$(CC) ./src/Main-Wrong.cpp -std=c++11 -o Main-Wrong
	$(CC) ./src/Main-RightLoopFusionParallel.cpp -std=c++11 -fopenmp -o Main-RightLoopFusionParallel
	$(CC) ./src/reportAnalyzer.cpp -std=c++11 -o reportAnalyzer