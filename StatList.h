#pragma once
#include <string>
#include <iostream>

struct Sub_List_Item {
public:
	int inf;
	Sub_List_Item* left;
	Sub_List_Item* right;
};

struct Sub_List {
	Sub_List_Item* pHeadSub;
	Sub_List() {
		pHeadSub = new Sub_List_Item();
		pHeadSub->left = pHeadSub;
		pHeadSub->right = pHeadSub;
	}
	Sub_List(std::string s) {
		pHeadSub = new Sub_List_Item();
		pHeadSub->left = pHeadSub;
		pHeadSub->right = pHeadSub;
		Sub_List_Item* pCurrent = pHeadSub;
		size_t pos = 0;
		std::string token;
		while ((pos = s.find(' ')) != std::string::npos) {
			if (s[0] == ' ') { s.erase(0, 1); continue; }
			token = s.substr(0, pos);
			Sub_List_Item* pTemp = new Sub_List_Item();
			pTemp->left = pCurrent;
			pTemp->right = pCurrent->right;
			pCurrent->right->left = pTemp;
			pCurrent->right = pTemp;
			pTemp->inf = stoi(token);
			pCurrent = pTemp;
			s.erase(0, pos);
		}
		if (s != "") {
			Sub_List_Item* pTemp = new Sub_List_Item();
			pTemp->left = pCurrent;
			pTemp->right = pCurrent->right;
			pCurrent->right->left = pTemp;
			pCurrent->right = pTemp;
			pTemp->inf = stoi(s);
		}
	}
};

struct Main_List_Item {
	Sub_List* pSub;
	Main_List_Item* left;
	Main_List_Item* right;
};

struct Main_List {
public:
	Main_List_Item* pHead;
	Main_List() {
		pHead = new Main_List_Item();
		pHead->pSub = new Sub_List();
		pHead->left = pHead;
		pHead->right = pHead;
	}
};

	int Push_Main_After(Main_List* list, int t, Sub_List* inf) {
		if (t < 0) return 0;
		Main_List_Item* pCurrent = list->pHead;
		Main_List_Item* pTemp = new Main_List_Item();
		for (int i = 0; i < t; i++) {
			if (pCurrent->right == list->pHead) return 0;
			pCurrent = pCurrent->right;
		}
		pTemp->left = pCurrent;
		pTemp->right = pCurrent->right;
		pCurrent->right->left = pTemp;
		pCurrent->right = pTemp;
		pTemp->pSub = inf;
		return 1;
	}

	int Push_Main_Before(Main_List* list, int t, Sub_List* inf) {
		if (t < 1) return 0;
		Main_List_Item* pCurrent = list->pHead;
		Main_List_Item* pTemp = new Main_List_Item();
		for (int i = 0; i < t; i++) {
			if (pCurrent->right == list->pHead) return 0;
			pCurrent = pCurrent->right;
		}
		pCurrent->left->right = pTemp;
		pTemp->left = pCurrent->left;
		pTemp->right = pCurrent;
		pCurrent->left = pTemp;
		pTemp->pSub = inf;
		return 1;
	}

	int Push_After(Main_List* list, int t1, int t2, int inf) {
		if (t2 < 0 || t1 < 0) return 0;
		Main_List_Item* pMain = list->pHead;
		for (int i = 0; i < t1; i++) {
			pMain = pMain->right;
			if (pMain == list->pHead) return 2;
		}
		Sub_List_Item* pCurrent = pMain->pSub->pHeadSub;
		Sub_List_Item* pTemp = new Sub_List_Item();
		for (int i = 0; i < t2; i++) {
			if (pCurrent->right == pMain->pSub->pHeadSub) return 0;
			pCurrent = pCurrent->right;
		}
		pTemp->left = pCurrent;
		pTemp->right = pCurrent->right;
		pCurrent->right->left = pTemp;
		pCurrent->right = pTemp;
		pTemp->inf = inf;
		return 1;
	}
	int Push_Before(Main_List* list, int t1, int t2, int inf) {
		if (t2 < 1 || t1 < 1) return 0;
		Main_List_Item* pMain = list->pHead;
		for (int i = 0; i < t1; i++) {
			pMain = pMain->right;
			if (pMain == list->pHead) return 2;
		}

		Sub_List_Item* pCurrent = pMain->pSub->pHeadSub;
		Sub_List_Item* pTemp = new Sub_List_Item();
		for (int i = 0; i < t2; i++) {
			if (pCurrent->right == pMain->pSub->pHeadSub) return 0;
			pCurrent = pCurrent->right;
		}
		pCurrent->left->right = pTemp;
		pTemp->left = pCurrent->left;
		pTemp->right = pCurrent;
		pCurrent->left = pTemp;
		pTemp->inf = inf;
		return 1;
	}
	std::string Delete_Sub(Main_List* list, int inf1, int inf2) {
		Main_List_Item* pMain = list->pHead->right;
		while (pMain != list->pHead) {
			if (pMain->pSub->pHeadSub->right->inf == inf1) {
				Sub_List_Item* pCurrent = pMain->pSub->pHeadSub->right;
				while (pCurrent != pMain->pSub->pHeadSub) {
					if (pCurrent->inf == inf2) {
						pCurrent->left->right = pCurrent->right;
						pCurrent->right->left = pCurrent->left;
						delete(pCurrent);
						return "The elemetn of Sub list was deleted.";
					}
					pCurrent = pCurrent->right;
				}
			}
			pMain = pMain->right;
		}
		return "The element of Sub list not found!";
	}

	std::string Delete_Main(Main_List* list, int inf) {
		Main_List_Item* pMain = list->pHead->right;
		while(pMain != list->pHead) {
			if (pMain->pSub->pHeadSub->right->inf == inf) {
				Sub_List_Item* pDel;
				Sub_List_Item* pCurrent = pMain->pSub->pHeadSub->right;
				while (pCurrent != pMain->pSub->pHeadSub) {
					pDel = pCurrent;
					pCurrent = pCurrent->right;
					pDel->left->right = pDel->right;
					pDel->right->left = pDel->left;
					delete(pDel);
				}
				pMain->left->right = pMain->right;
				pMain->right->left = pMain->left;
				delete(pMain);
				return "The element of Main list was deleted.";
			}
			pMain = pMain->right;
		}
		return "The element of Main list not found!";	
	}

	std::string Show(Main_List* list) {
		std::string str;
		Main_List_Item* pMain = list->pHead->right;
		Sub_List_Item* pCurrent;
		while(pMain != list->pHead) {
			pCurrent = pMain->pSub->pHeadSub->right;
			while (pCurrent != pMain->pSub->pHeadSub) {
				str += " || " + std::to_string(pCurrent->inf) + " || ";
				pCurrent = pCurrent->right;
			}
			pMain = pMain->right;
			str += "\n";
		}
		return str;
	}

	std::string Get_right(Main_List* list, int inf) {
		Main_List_Item* pMain = list->pHead->right;
		Sub_List_Item* pCurrent;
		int i = 1;
		int j = 1;
		while (pMain!= list->pHead) {
			pCurrent = pMain->pSub->pHeadSub->right;
			while (pCurrent != pMain->pSub->pHeadSub) {
				if (pCurrent->inf == inf) return "The number with inf: | " + std::to_string(pCurrent->inf) + " | has index (on right side): | [" + std::to_string(j) + "]["+std::to_string(i)+"].";
				pCurrent = pCurrent->right;
				i++;
			}
			pMain = pMain->right;
			j++; i = 1;
		}
		return "The number with inf : | " + std::to_string(inf) + " | not found. ";
	}

	std::string Get_left(Main_List* list, int inf) {
		Main_List_Item* pMain = list->pHead->left;
		Sub_List_Item* pCurrent;
		int i = 1;
		int j = 1;
		while (pMain != list->pHead) {
			pCurrent = pMain->pSub->pHeadSub->left;
			while (pCurrent != pMain->pSub->pHeadSub) {
				if (pCurrent->inf == inf) return "The number with inf: | " + std::to_string(pCurrent->inf) + " | has index (on left side): | [" + std::to_string(j) + "][" + std::to_string(i) + "].";
				pCurrent = pCurrent->left;
				i++;
			}
			pMain = pMain->left;
			j++; i = 1;
		}
		return "The number with inf : | " + std::to_string(inf) + " | not found. ";
	}