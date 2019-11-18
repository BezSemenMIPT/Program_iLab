#pragma once
#include<queue>

template <typename T>struct tree {
	T key, height, dif;//dif is optimal to be in {-1; 0 ; 1}
	tree* lhs, *rhs, *par;
};

template <typename T> class SearchTree {
	tree<T>* top = new tree<T>;
	bool isBST(tree<T>* node, int minKey, int maxKey);
	//methods of balance
	void left_rotate(tree<T>* pp, tree<T>* V);
	void right_rotate(tree<T>* pp, tree<T>* V);
public:
	SearchTree(T top_data);
	SearchTree(const SearchTree&);
	SearchTree& operator=(const SearchTree&);
	void push(const T& elem);
	void remove(const T& elem);
	void balance(tree<T>* const V);
	const bool exists(const T& elem);
	tree<T>* minimum(tree<T>* const V);
	tree<T>* next(tree<T>* const V);
	const bool verification();
	~SearchTree();
};

template<typename T> SearchTree<T>& SearchTree<T>:: operator=(const SearchTree<T>& copy_t) {
	std::queue<tree<T>*> q;
	tree<T>* Node;
	if (this != &copy_t) {
		Node = this->top;
		if (Node->lhs != NULL) q.push(this->top->lhs);
		if (Node->rhs != NULL) q.push(this->top->rhs);
		while (!q.empty()) {
			Node = q.front();
			q.pop();
			if (Node->lhs != NULL) q.push(Node->lhs);
			if (Node->rhs != NULL) q.push(Node->rhs);
			delete Node;
		}
		this->top->par = NULL;
		this->top->dif = 0;
		this->top->height = 1;
		this->top->key = copy_t.top->key;
		this->top->lhs = NULL;
		this->top->rhs = NULL;
		Node = copy_t.top;
		if (Node->lhs != NULL) q.push(Node->lhs);
		if (Node->rhs != NULL) q.push(Node->rhs);
		while (!q.empty()) {
			Node = q.front();
			this->push(Node->key);
			q.pop();
			if (Node->lhs != NULL) q.push(Node->lhs);
			if (Node->rhs != NULL) q.push(Node->rhs);
		}
	}
	//Test if copying is correct
	int flag = 1;
	Node = copy_t.top;
	if (Node->lhs != NULL) q.push(Node->lhs);
	if (Node->rhs != NULL) q.push(Node->rhs);
	while (!q.empty()) {
		Node = q.front();
		flag = this->exists(Node->key);
		q.pop();
		if (Node->lhs != NULL) q.push(Node->lhs);
		if (Node->rhs != NULL) q.push(Node->rhs);
	}
	if (flag == 1) std::cout << "copying is correct" << std::endl;
	else std::cout << "copying is wrong" << std::endl;
	return *this;
}

template<typename T> SearchTree<T>::SearchTree(const SearchTree<T>& copy_t) {
	std::queue<tree<T>*> q;
	tree<T>* Node;
	this->top->par = NULL;
	this->top->dif = 0;
	this->top->height = 1;
	this->top->key = copy_t.top->key;
	this->top->lhs = NULL;
	this->top->rhs = NULL;
	Node = copy_t.top;
	if (Node->lhs != NULL) q.push(Node->lhs);
	if (Node->rhs != NULL) q.push(Node->rhs);
	while (!q.empty()) {
		Node = q.front();
		this->push(Node->key);
		q.pop();
		if (Node->lhs != NULL) q.push(Node->lhs);
		if (Node->rhs != NULL) q.push(Node->rhs);
	}
}

template<typename T> const bool SearchTree <T> ::verification(){
	tree<T>* min, *max, *temp;
	temp = top;
	min = minimum(top);
	temp = top;
	while (temp->rhs != NULL) temp = temp->rhs;
	max = temp;
	return isBST(top, min->key, max->key);
}

template<typename T> bool SearchTree <T> ::isBST(tree<T>* node, int minKey, int maxKey) {
	if (node == nullptr) return true;
	if (node->key < minKey || node->key > maxKey) return false;
	return isBST(node->lhs, minKey, node->key - 1) && isBST(node->rhs, node->key + 1, maxKey);
}

template<typename T> void SearchTree <T> ::left_rotate(tree<T>* pp, tree<T>* V) {
	if (V->dif <= 0) {
		if (pp->lhs->rhs != NULL) {
			V = pp->lhs;
			pp->lhs = pp->lhs->rhs;
			if (pp->lhs != NULL) pp->lhs->par = pp;
			if ((pp->lhs == NULL) && (pp->rhs == NULL)) pp->dif = 0;
			else if (pp->lhs == NULL) pp->dif = 1;
			else if (pp->rhs == NULL) pp->dif = -1;
			else pp->dif = pp->rhs->height - pp->lhs->height;
			if (pp->dif > 0) pp->height = pp->rhs->height + 1;
			else pp->lhs != NULL ? pp->height = pp->lhs->height + 1 : pp->height = 1;
		}
		else if (pp->lhs->rhs == NULL) {
			if (pp->rhs != NULL) {
				pp->height = pp->rhs->height + 1;
				pp->dif = (-1)*pp->rhs->height;
			}
			else {
				pp->height = 1;
				pp->dif = 0;
				pp->lhs = NULL;
				pp->rhs = NULL;
			}
			pp->lhs = NULL;
		}
		if (pp == top) top = V;
		V->par = pp->par;
		if (V->par != NULL) {
			if (V->par->key < V->key) V->par->rhs = V;
			else V->par->lhs = V;
		}
		pp->par = V;
		V->rhs = pp;
		if ((V->lhs == NULL) && (V->rhs == NULL)) V->dif = 0;
		else if (V->lhs == NULL) V->dif = 1;
		else if (V->rhs == NULL) V->dif = -1;
		else V->dif = V->rhs->height - V->lhs->height;
		if (V->dif > 0) V->height = V->rhs->height + 1;
		else V->height = V->lhs->height + 1;
	}
	else {
		pp = V;
		V = V->rhs;
		V->par = pp->par;
		if (V->par != NULL) V->par->lhs = V;
		pp->par = V;
		pp->rhs = V->lhs;
		V->lhs = pp;
		--pp->height;
		if ((pp->lhs == NULL) && (pp->rhs == NULL)) pp->dif = 0;
		else if (pp->lhs == NULL) pp->dif = 1;
		else if (pp->rhs == NULL) pp->dif = -1;
		else pp->dif = pp->rhs->height - pp->lhs->height;
		if (V->rhs != NULL) V->dif = V->rhs->height - V->lhs->height;
		else V->dif = -1;
		if (V->dif > 0) V->height = V->rhs->height + 1;
		else V->height = V->lhs->height + 1;
		pp = V->par;

		if (pp == top) top = V;
		V->par = pp->par;
		if (V->par != NULL) V->par->rhs = V;
		pp->par = V;
		pp->lhs = V->rhs;
		V->rhs = pp;
		if ((pp->lhs == NULL) && (pp->rhs == NULL)) pp->dif = 0;
		else if (pp->lhs == NULL) pp->dif = 1;
		else if (pp->rhs == NULL) pp->dif = -1;
		else pp->dif = pp->rhs->height - pp->lhs->height;
		if (pp->dif > 0) pp->height = pp->rhs->height + 1;
		else pp->lhs != NULL ? pp->height = pp->lhs->height + 1 : pp->height = 1;
		if (V->lhs != NULL) V->dif = V->rhs->height - V->lhs->height;
		else V->dif = 1;
		if (V->dif > 0) V->height = V->rhs->height + 1;
		else V->height = V->lhs->height + 1;
	}
}

template<typename T> void SearchTree <T> ::right_rotate(tree<T>* pp, tree<T>* V) {
	if (V->dif >= 0) {
		if (pp->rhs->lhs != NULL) {
			V = pp->rhs;
			pp->rhs = pp->rhs->lhs;
			if (pp->rhs != NULL) pp->rhs->par = pp;
			if ((pp->lhs == NULL) && (pp->rhs == NULL)) pp->dif = 0;
			else if (pp->lhs == NULL) pp->dif = 1;
			else if (pp->rhs == NULL) pp->dif = -1;
			else pp->dif = pp->rhs->height - pp->lhs->height;
			if (pp->dif > 0) pp->height = pp->rhs->height + 1;
			else pp->lhs != NULL ? pp->height = pp->lhs->height + 1 : pp->height = 1;
		}
		else if (pp->rhs->lhs == NULL) {
			if (pp->lhs != NULL) {
				pp->height = pp->lhs->height + 1;
				pp->dif = (-1)*pp->lhs->height;
			}
			else {
				pp->height = 1;
				pp->dif = 0;
				pp->lhs = NULL;
				pp->rhs = NULL;
			}
			pp->rhs = NULL;
		}
		if (pp == top) top = V;
		V->par = pp->par;
		if (V->par != NULL) {
			if (V->par->key < V->key) V->par->rhs = V;
			else V->par->lhs = V;
		}
		pp->par = V;
		V->lhs = pp;
		if ((V->lhs == NULL) && (V->rhs == NULL)) V->dif = 0;
		else if (V->lhs == NULL) V->dif = 1;
		else if (V->rhs == NULL) V->dif = -1;
		else V->dif = V->rhs->height - V->lhs->height;
		if (V->dif > 0) V->height = V->rhs->height + 1;
		else V->height = V->lhs->height + 1;
	}
	else {
		pp = V;
		V = V->lhs;
		V->par = pp->par;
		if (V->par != NULL) V->par->rhs = V;
		pp->par = V;
		pp->lhs = V->rhs;
		V->rhs = pp;
		--pp->height;
		if ((pp->lhs == NULL) && (pp->rhs == NULL)) pp->dif = 0;
		else if (pp->lhs == NULL) pp->dif = 1;
		else if (pp->rhs == NULL) pp->dif = -1;
		else pp->dif = pp->rhs->height - pp->lhs->height;
		if (V->lhs != NULL) V->dif = V->rhs->height - V->lhs->height;
		else V->dif = 1;
		if (V->dif > 0) V->height = V->rhs->height + 1;
		else V->height = V->lhs->height + 1;
		pp = V->par;

		if (pp == top) top = V;
		V->par = pp->par;
		if (V->par != NULL) V->par->lhs = V;
		pp->par = V;
		pp->rhs = V->lhs;
		V->lhs = pp;
		if ((pp->lhs == NULL) && (pp->rhs == NULL)) pp->dif = 0;
		else if (pp->lhs == NULL) pp->dif = 1;
		else if (pp->rhs == NULL) pp->dif = -1;
		else pp->dif = pp->rhs->height - pp->lhs->height;
		if (pp->dif > 0) pp->height = pp->rhs->height + 1;
		else pp->lhs != NULL ? pp->height = pp->lhs->height + 1 : pp->height = 1;
		if (V->rhs != NULL) V->dif = V->rhs->height - V->lhs->height;
		else V->dif = -1;
		if (V->dif > 0) V->height = V->rhs->height + 1;
		else V->height = V->lhs->height + 1;
	}
}

template<typename T> void SearchTree <T> ::balance(tree<T>* const V_c) {
	tree<T>* V = V_c;
	tree<T>* pp = V->par;
	do {
		pp = V->par;
		if (pp == NULL) break;
		if (pp->lhs == NULL) {
			pp->dif = pp->rhs->height;
			pp->height = pp->rhs->height + 1;
		}
		else if (pp->rhs == NULL) {
			pp->dif = (-1)*pp->lhs->height;
			pp->height = pp->lhs->height + 1;
		}
		else {
			pp->dif = pp->rhs->height - pp->lhs->height;
			if (pp->dif > 0) pp->height = pp->rhs->height + 1;
			else pp->height = pp->lhs->height + 1;
		}
		if (pp->dif == -2) {
			left_rotate(pp, V);
		}
		if (pp->dif == 2) {
			right_rotate(pp, V);
		}
		V = V->par;
	} while ((V != top)&&(V != NULL));
}

template<typename T> tree<T>* SearchTree <T> ::minimum(tree<T>* const V) {
	tree<T>* p = V;
	while (1) {
		if (p->lhs == NULL) return p;
		p = p->lhs;
	}
}

template<typename T> tree<T>* SearchTree <T> ::next(tree<T>* const V) {
	tree<T>* p = V;
	tree<T>* temp;
	if ((p->rhs == NULL) && (p->lhs == NULL) && (p->par == NULL)) return NULL;
	if (p->rhs != NULL) return minimum(p->rhs);
	temp = p->par;
	while ((temp != NULL) && (p == temp->rhs)) {
		p = temp;
		temp = temp->par;
	}
	return temp;
}

template<typename T> const bool SearchTree <T> ::exists(const T& elem) {
	tree<T>* p = top;
	while (p != NULL) {
		if (p->key == elem) return true;
		else if (p->key > elem) p = p->lhs;
		else if (p->key < elem) p = p->rhs;
	}
	return false;
}

template<typename T> void SearchTree <T> ::remove(const T& elem) {
	tree<T>* p = top;
	tree<T>* n;
	tree<T>* temp, *temp_1;
	while (1) {
		if (p->key > elem) p = p->lhs;
		else if (p->key < elem) p = p->rhs;
		else if (p->key == elem) {
			n = next(p);
			if (n != NULL) {
				if (n->height < p->height) {
					p->key = n->key;
					temp = n->rhs;
					temp_1 = n->par;
					if (n->key < n->par->key) {
						if (n->par != NULL)n->par->lhs = n->rhs;
					}
					else {
						if (n->par != NULL)n->par->rhs = n->rhs;
					}
					if (n->rhs != NULL) n->rhs->par = n->par;
					delete n;
					if ((temp_1->lhs == NULL) && (temp_1->rhs == NULL)) temp_1->dif = 0;
					else if (temp_1->lhs == NULL) temp_1->dif = 1;
					else if (temp_1->rhs == NULL) temp_1->dif = -1;
					if (temp_1->dif > 0) temp_1->height = temp_1->rhs->height + 1;
					else temp_1->lhs != NULL ? temp_1->height = temp_1->lhs->height + 1 : temp_1->height = 1;
					balance(temp_1);
					break;
				}
				else {
					temp = p->lhs;
					temp_1 = p->par;
					p->par->lhs = temp;
					if (temp != NULL)temp->par = p->par;
					delete p;
					if (temp != NULL) balance(temp);
					else if (temp_1->rhs != NULL)balance(temp_1->rhs);
					else balance(temp_1);
					break;
				}
			}
			else {
				if (p != top) {
					p->par->rhs = p->lhs;
					if (p->lhs != NULL)	p->lhs->par = p->par;
					temp = p->par;
					delete p;
					if (temp->rhs != NULL)	balance(temp->rhs);
					else {
						if (temp->lhs != NULL) balance(temp->lhs);
						else balance(temp);
					}
					break;
				}
				else {
					if (p->lhs != NULL) {
						top->key = p->lhs->key;
						top->lhs = NULL;
						delete p->lhs;
					}
					else {
						delete p;
						top = NULL;
					}
					break;
				}
			}
		}
	}
}

template<typename T> void SearchTree <T> ::push(const T& elem) {
	tree<T>* p = top;
	tree<T>* newNode = new tree<T>;
	int flag = 0;
	newNode->key = elem;
	newNode->lhs = NULL;
	newNode->rhs = NULL;
	newNode->dif = 0;
	newNode->height = 1;
	while (p != NULL) {
		if (elem < p->key) {
			if (p->lhs == NULL) {
				newNode->par = p;
				p->lhs = newNode;
				break;
			}
			p = p->lhs;
		}
		else if (elem > p->key) {
			if (p->rhs == NULL) {
				newNode->par = p;
				p->rhs = newNode;
				break;
			}
			p = p->rhs;
		}
		else {
			flag = 1;
			break;
		}
	}
	if (flag == 0) balance(newNode);
}

template<typename T> SearchTree <T> ::~SearchTree() {
	if (top == NULL) return;
	std::queue<tree<T>*> q;
	q.push(top);
	while (!q.empty()) {
		tree<T>* Node = q.front();
		q.pop();
		if (Node->lhs != NULL) q.push(Node->lhs);
		if (Node->rhs != NULL) q.push(Node->rhs);
		delete Node;
	}
}

template<typename T> SearchTree <T> ::SearchTree(T top_data) {
	top->par = NULL;
	top->dif = 0;
	top->height = 1;
	top->key = top_data;
	top->lhs = NULL;
	top->rhs = NULL;
}