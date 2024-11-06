#include <chrono>
#include <iostream>
/*
1. The timer I'm using measures milliseconds

*/
using namespace std;
int testTime(int size, int loops)
{
	int *test = new int[size];
	auto start = chrono::system_clock::now();
	for(int i = 0; i < loops; i++) for(int j = 0; j < size; j++) test[j] = i;
	auto end = chrono::system_clock::now();
	delete test;
	return chrono::duration_cast<chrono::milliseconds>(end - start).count();;
}

int main()
{
	for(int i = 1; i < 1024 * 1024 * 1024; i *= 2)
	{
		int time = testTime(i, 100000000);
		if(i * sizeof(int) < 1024) cout << i * sizeof(int) << "B\t" << time << "\t" << time / (1.0 * i) << "\n";
		else if(i * sizeof(int)/1024 < 1024) cout << i * sizeof(int)/1024 << "KB\t" << time << "\t" << time / (1.0 * i) << "\n";
		else if(i * sizeof(int)/1024/1024 < 1024) cout << i * sizeof(int)/1024/1024 << "MB\t" << time << "\t" << time / (1.0 * i) << "\n";
		else cout << i * sizeof(int)/1024/1024/1024 << "GB\t" << time << "\t" << time / (1.0 * i) << "\n";
	}
}