// MyThread3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int mylesstest();
int mymoretest();

int main()
{
    std::cout << "Hello World!\n";

    //int a = 1;
    //int b = 2;
    //int c = a + b;

    //std::cout << "a + b = " << c << std::endl;

	//mylesstest();
	mymoretest();
}



#include <windows.h>
#include <iostream>

using namespace std;
static int g_value = 0;

DWORD WINAPI ThreadFunc(LPVOID lpParamter)
{
	for (int x = 0; x < 1000; x++)
	{

		g_value++;
		cout << "sub thread, g_value: " << g_value << endl;

	}

	return 0;
}

int mylesstest()
{
	HANDLE hThread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);

	for (int x = 0; x < 1000; x++)
	{

		g_value++;
		cout << "main thread, g_value: " << g_value << endl;

	}

	system("pause");
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file



#include <windows.h>
#include <iostream>

using namespace std;
HANDLE hMutex = NULL; 
#define NUM_THREAD 50

#define THREAD_SYNC

DWORD WINAPI FuncA(LPVOID lpParamter)
{
	for (int x = 0; x < 10; x++)
	{
#ifdef THREAD_SYNC
		WaitForSingleObject(hMutex, INFINITE);
#endif

		DWORD tid = GetCurrentThreadId();
		g_value++;
		cout << "thread func A, tid: " << tid << ", g_value: " << g_value << endl;

#ifdef THREAD_SYNC
		ReleaseMutex(hMutex);
#endif
	}
	return 0;
}


DWORD WINAPI FuncB(LPVOID lpParamter)
{
	for (int x = 0; x < 10; x++)
	{
#ifdef THREAD_SYNC
		WaitForSingleObject(hMutex, INFINITE);
#endif

		DWORD tid = GetCurrentThreadId();
		g_value++;
		cout << "thread func B, tid: " << tid << ", g_value: " << g_value << endl;

#ifdef THREAD_SYNC
		ReleaseMutex(hMutex);
#endif
	}
	return 0;
}

int mymoretest()
{
	HANDLE tHandle[NUM_THREAD];

	hMutex = CreateMutex(NULL, FALSE, L"davis_mutex");

	for (int x = 0; x < NUM_THREAD; x++)
	{
		if (x % 2)
		{
			tHandle[x] = CreateThread(NULL, 0, FuncA, NULL, 0, NULL);
		}
		else
		{
			tHandle[x] = CreateThread(NULL, 0, FuncB, NULL, 0, NULL);
		}
	}


	WaitForMultipleObjects(NUM_THREAD, tHandle, TRUE, INFINITE);

	if (hMutex)
		CloseHandle(hMutex);

	system("pause");
	return 0;
}


