#include <iostream>
#include <windows.h>

struct Stack_item {
	Stack_item* next;
	std::string inf;
};

struct Stack {
public:
	Stack_item* sp;
	Stack() {
		sp = NULL;
	}
	void Push(std::string inf) {
		Stack_item* p_Temp = new Stack_item;
		p_Temp->inf = inf;
		p_Temp->next = sp;
		sp = p_Temp;
	}
	void Delete() {
		Stack_item* p_Temp = sp;
		sp = sp->next;
		delete p_Temp;
	}
	bool IsEmpty() {
		if (sp == NULL) return true;
		return false;
	}
	void Show() {
		Stack_item* pCurrent = sp;
		while (pCurrent != NULL) {
			std::cout << pCurrent->inf << " ";
			pCurrent = pCurrent->next;
		}
	}


};