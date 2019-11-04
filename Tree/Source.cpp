#include<iostream>
#include<vector>

//AVL - tree
template <typename T>struct tree {
	T key, height, dif;//dif is optimal to be in {-1; 0 ; 1}
	tree* lhs, *rhs, *par;
};

template <typename T> class SearchTree { 
	tree<T>* top = new tree<T>;
	bool isBST(tree<T>* node, int minKey, int maxKey);
public: 
		SearchTree(); 
		SearchTree(const SearchTree&)=delete; 
		SearchTree& operator=(const SearchTree&)=delete;
		void push(const T& elem);
		void remove(const T& elem);
		void balance(tree<T>* const V);
		bool exists(const T& elem);
		tree<T>* minimum(tree<T>* const V);
		tree<T>* next(tree<T>* const V);
		bool verification();
		~SearchTree();
};

template<typename T> bool SearchTree <T> ::verification() {
	tree<T>* min, *max, *temp;
	temp = top;
	min = minimum(top);
	temp = top;
	while (temp->rhs != NULL) temp = temp->rhs;
	max = temp;
	return isBST(top, min->key, max->key);
}

template<typename T> bool SearchTree <T> :: isBST(tree<T>* node, int minKey, int maxKey) {
	if (node == nullptr) return true;
	if (node->key < minKey || node->key > maxKey) return false;
	return isBST(node->lhs, minKey, node->key - 1) && isBST(node->rhs, node->key + 1, maxKey);
}

template<typename T> void SearchTree <T> ::balance(tree<T>* const V_c) {
	tree<T>* V = V_c;
	tree<T>* pp = V->par, *temp = pp->par;
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
		temp = pp->par;
		if (pp->dif == -2) {
			if (V->dif <= 0) {
				if (pp->lhs->rhs != NULL) {
					pp->lhs = pp->lhs->rhs;
					pp->lhs->rhs->par = pp;
				}
				if (pp->lhs->rhs == NULL) {
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
					pp->rhs->lhs = NULL;
				}
				pp->par = V;
				V->rhs = pp;
				V->par = temp;
				if (pp == top) top = V;
				V->par = pp->par;
				if (V->par != NULL) V->par->lhs = V;
				pp->par = V;
				V->rhs = pp;
				V->dif = V->rhs->height - V->lhs->height;
				if (V->dif > 0) V->height = V->rhs->height + 1;
				else V->height = V->lhs->height + 1;

			}
			else {
				temp = pp->par;
				V->par = V->rhs;
				V->par->lhs = V;
				temp->lhs = V->par;
				V->par->par = temp;
				V->rhs = V->par->lhs;
				V->par->lhs->par = V;
			}
		}
		if (pp->dif == 2) {
			if (V->dif >= 0) {
				if (pp->rhs->lhs != NULL) {
					pp->rhs = pp->rhs->lhs;
					pp->rhs->lhs->par = pp;
				}
				if (pp->rhs->lhs == NULL) {
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
				if (V->par != NULL) V->par->rhs = V;
				pp->par = V;
				V->lhs = pp;
				V->dif = V->rhs->height - V->lhs->height;
				if (V->dif > 0) V->height = V->rhs->height + 1;
				else V->height = V->lhs->height + 1;
			}
			else {
				temp = V->par;
				V->par = V->lhs;
				V->par->rhs = V;
				temp->rhs = V->par;
				V->par->par = temp;
				V->lhs = V->par->rhs;
				V->par->rhs->par = V;
			}
		}
		V = V->par;
	} while (temp != NULL);
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
	if ((p->rhs == NULL) && (p->lhs==NULL) && (p->par == NULL)) return NULL;
	if (p->rhs != NULL) return minimum(p->rhs);
	temp = p->par;
	while ((temp != NULL) && (p == temp->rhs)) {
		p = temp;
		temp = temp->par;
	}
	return temp;	
}

template<typename T> bool SearchTree <T> ::exists(const T& elem) {
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
	tree<T>* temp;
	while (1) {
		if (p->key > elem) p = p->lhs;
		else if (p->key < elem) p = p->rhs;
		else if (p->key == elem) {
			n = next(p);
			if (n->height < p->height) {
				p->key = n->key;
				temp = n->rhs;
				n->par->rhs = n->rhs;
				n->rhs->par = n->par;
				delete n;
				balance(temp);
				break;
			}
			else {//p doesn't have right child
				temp = p->lhs;
				p->par->lhs = temp;
				temp->par = p->par;
				delete(p);
				balance(temp);
			}
		}
	}
}

template<typename T> void SearchTree <T> :: push(const T& elem) {
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
	tree<T>* del_past = minimum(top), * del_next;
	while (1) {
		del_next = next(del_past);
		if(del_past->par != NULL) del_past->par->lhs = NULL;
		if(del_past->rhs != NULL) del_past->rhs->par = NULL;
		if (del_next == NULL) break;
		delete(del_past);
		del_past = del_next;
	}
}

template<typename T> SearchTree <T> ::SearchTree() {
	T x;
	tree<T>* temp = top;
	int N;//number of vertixes
	std::cin >> N;
	std::cin >> x;
	top->par = NULL;
	top->dif = 0;
	top->height = 1;
	top->key = x;
	top->lhs = NULL;
	top->rhs = NULL;
	for (int i = 1; i < N; i++) {
		std::cin >> x;
		push(x);
	}
}


int main() {
	SearchTree<int> a;
	a.verification() ? std::cout << true << std::endl : std::cout << false << std::endl;
	a.push(4);
	a.remove(2);
}




















