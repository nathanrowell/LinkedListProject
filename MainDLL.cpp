
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "TaskManager.hpp"
using namespace std;

int main() {
	srand(time(NULL));
	TaskManager *list = new TaskManager("C:\\Users\\natha\\Downloads\\DLLTaskManager\\ListofTasks.txt");
}

