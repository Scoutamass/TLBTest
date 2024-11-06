#include <chrono>
#include <iostream>
/*
1. The timer I'm using measures milliseconds, so operations have to take 100s of milliseconds at least to be measured accurately
5. All you have to do is to make the loop do something, in my case I'm setting the values in the array
6. The process moving to different CPUs will increase the number of TLB misses, effectively increasing the runtime of the program
7. THis will make the code take longer by some amount based on the size of the array, but since every test has to do this, the results should be uneffected. I could initialize the array before starting my timer, but I don't think it would make a difference
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