// Nathan Rowell Section 013
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;

DLL::DLL(){
    first = nullptr;
    last = nullptr;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}

DLL::DLL(string t, int p, int h, int m){
    DNode *newNode = new DNode(t,p,h,m);
    first = newNode;
    last = newNode;
    numTasks = 1;
    tothrs += newNode->task->hr;
    totmin += newNode->task->min;

}

DLL::~DLL(){
    DNode *current = first;
    DNode *temp = new DNode();
    while (current != nullptr) {
        temp = current->next;
        delete temp;
        current = current->next;


    }
	
}

void DLL::push(string n, int p, int h, int m) {
    DNode *current = first;
    DNode *newNode = new DNode(n,p,h,m);
    if (current == nullptr) {
        first = newNode;
        last = newNode;
        addTime(first->task->hr,first->task->min);
    }
    else {
        while (current->next != nullptr and current->task->priority < p) {
            current = current->next;



        }
        while (current->next != nullptr and current->next->task->priority == p) {
            current = current->next;
        }
        DNode *temp = current->next;
        current->next = newNode;
        newNode->prev = current;
        newNode->next = temp;
        if (current->next->next == nullptr)
            last = newNode;
        addTime(newNode->task->hr,newNode->task->min);
    }
    tothrs += h;
    totmin += m;
    numTasks++;

	
}

Task *DLL::pop() {
    DNode *temp = first;
    first = first->next;
    first->prev = nullptr;
    numTasks--;
    temp->next = nullptr;
    temp->prev = nullptr;
    removeTime(temp->task->hr,temp->task->min);
    return temp->task;

	
}

int DLL::remove(int tn) {
	DNode *current = first;
    while (current != nullptr) {
        if (current->task->tasknum == tn) {
            removeTime(current->task->hr,current->task->min);
            numTasks--;
            if (current->next == nullptr) {
                current->prev->next = nullptr;
            }
            else if (current->prev == nullptr) {
                current->next->prev = nullptr;
            }
            else {
                DNode *temp = current->next;
                current->prev->next = current->next;
                temp->prev = current->prev;
            }

            return tn;
        }
        current = current->next;
    }
    return -1;
}

void DLL::addTime(int h, int m) {
    tothrs += h;
    totmin += m;
	
}

void DLL::removeTime(int h, int m) {
    tothrs -= h;
    totmin -= m;
	
}

void DLL::moveUp(int t) {
    DNode *current = first;
    DNode *temp;
    while (current != nullptr) {
        if (current->task->tasknum == t) {
            if (current == first) {
                first = current->next;
                first->prev = nullptr;
                last->next = current;
                last = current;
                current->next = nullptr;
            }
            else {
                int priorityPrev = current->prev->task->priority;
                if (priorityPrev < current->task->priority) {
                    current->task->priority = priorityPrev;
                }
                temp = current->prev;
                current->prev->prev->next = current;
                current->prev = current->prev->prev;
                temp->next=current->next;
                current->next=temp;
                temp->prev=current;


            }
        }
        current = current->next;
    }
	
}

void DLL::moveDown(int t) {
    int index = 0;
    DNode *current = last;
    cout << last->task->tasknum;
    DNode *temp;
    while (current != nullptr) {
        if (current->task->tasknum == t) {
            if (current == last) {

                first->prev = current;
                last->prev->next = nullptr;
                current->next = first;
                current = first;
            }
            else {
                int priorityPrev = current->next->task->priority;
                if (priorityPrev > current->task->priority) {
                    current->task->priority = priorityPrev;
                }


                temp = current->next;
                current->next->next->prev=current;
                temp->prev=current->prev;
                current->prev->next=temp;
                current->prev=temp;
                current->next=current->next->next;
                temp->next=current;



            }
        }
        current = current->prev;
    }

}

void DLL::changePriority(int tn, int newp) {
	DNode *current = first;
    while (current != NULL) {
        if (current->task->tasknum == tn) {
            current->task->priority = newp;
        }
        current = current->next;
    }
}

void DLL::listDuration(int *th, int *tm,int tp) {
    DNode *current = first;
    while (current != NULL) {
        if (current->task->priority == tp) {
            *th += current->task->hr;
            *tm += current->task->min;
        }
        current = current->next;
    }
	
}

void DLL::printList() {
    cout << "Total Time Required: "<<tothrs<< ":"<<totmin<<endl;
    DNode *current = first;
    while (current != nullptr) {
        current->task->printTask();
        current = current->next;
    }
	
}

void DLL::printList(int p) {
    tothrs = 0;
    totmin = 0;
    DNode *current = first;
    while (current != NULL) {
        if (current->task->priority == p) {
            addTime(current->task->hr,current->task->min);
        }
        current = current->next;
    }
    cout << p <<": Total Time Required: "<< tothrs << ":"<< totmin <<endl;
    current = first;
    while (current != NULL) {
        if (current->task->priority == p) {
            current->task->printTask();
        }
        current = current->next;
    }
}
