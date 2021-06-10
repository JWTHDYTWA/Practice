#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;
struct vertex;
struct arc;
struct dj_st;

struct vertex {
	vector<arc*> ways;
	string label;
	dj_st* dj = nullptr;
};
struct arc {
	vertex* par;
	vertex* tar;
	float value;
};
struct dj_st {
	float sum;
	vertex* back;
	bool done;
};

bool comp(arc* first, arc* second);

class uGraph
{
	vector<vertex*> index;
	map<string, vector<vertex*>> key;
	int unc = 1;
public:
	bool oriented;
	uGraph(bool o = true) {
		oriented = o;
	}
	vertex* operator[](int n) {
		return index[n];
	}
	vertex* operator[](string s);
	vertex* newVertex(const string L = "unnamed");
	arc* newArc(vertex* F, vertex* T, float V);
	void rmVertex(const string S);
	void rmVertex(vertex* V);
	void rmArc(vertex* from, vertex* to);
	void sortArcs();
	vertex* findByLabel(const string L);
	void print();
	void readFile(string S);
	const auto pathFind(vertex* from, vertex* to);
};


bool comp(arc* first, arc* second) {
	return first->value < second->value;
}

vertex* uGraph::operator[](string S) {
	return findByLabel(S);
}

vertex* uGraph::newVertex(const string L) {
	index.push_back(new vertex);
	if (L == "unnamed") {
		index.back()->label = "unnamed_" + to_string(unc);
		unc++;
	}
	else index.back()->label = L;
	if (key.find(L) == key.end()) {
		key[L] = vector<vertex*>();
	}
	key[L].push_back(index.back());
	return index.back();
}

arc* uGraph::newArc(vertex* F, vertex* T, float V) {
	if (F == NULL || T == NULL) return nullptr;
	arc* A = new arc{F,T,V};
	F->ways.push_back(A);
	T->ways.push_back(A);
	return A;
}

void uGraph::rmVertex(const string S) {
	if (key.count(S)) {
		for (auto i : key[S]) {
			while (!i->ways.empty()) {
				auto tmp = i->ways[0];
				for (unsigned j = 0; j < tmp->tar->ways.size(); j++) {
					if (tmp->tar->ways[j] == tmp) {
						tmp->tar->ways.erase(tmp->tar->ways.begin() + j--);
					}
				}
				for (unsigned j = 0; j < tmp->par->ways.size(); j++) {
					if (tmp->par->ways[j] == tmp) {
						tmp->par->ways.erase(tmp->par->ways.begin() + j--);
					}
				}
				delete tmp;
			}
			for (unsigned k = 0; k < index.size(); k++) {
				if (index[k] == i) {
					index.erase(index.begin() + k--);
				}
			}
			delete i;
		}
		key.erase(key.find(S));
	}
}

void uGraph::rmVertex(vertex* V) {
	while (!V->ways.empty()) {
		auto tmp = V->ways[0];
		for (unsigned j = 0; j < tmp->tar->ways.size(); j++) {
			if (tmp->tar->ways[j] == tmp) {
				tmp->tar->ways.erase(tmp->tar->ways.begin() + j--);
			}
		}
		for (unsigned j = 0; j < tmp->par->ways.size(); j++) {
			if (tmp->par->ways[j] == tmp) {
				tmp->par->ways.erase(tmp->par->ways.begin() + j--);
			}
		}
		delete tmp;
	}
	for (unsigned k = 0; k < index.size(); k++) {
		if (index[k] == V) {
			index.erase(index.begin() + k--);
		}
	}
	for (unsigned i = 0; i < key[V->label].size(); i++) {
		if (key[V->label][i] == V) {
			key[V->label].erase(key[V->label].begin() + i--);
		}
	}
	if (key[V->label].empty()) {
		key.erase(key.find(V->label));
	}
	delete V;
}

void uGraph::rmArc(vertex* from, vertex* to) {
	for (unsigned i = 0; i < from->ways.size(); i++) {
		if (from->ways[i]->tar == to) {
			from->ways.erase(from->ways.begin() + i--);
		}
		else if (oriented == false) {
			from->ways.erase(from->ways.begin() + i--);
		}
	}
}

void uGraph::sortArcs() {
	for (auto i : index) {
		sort(i->ways.begin(), i->ways.end(), comp);
	}
}

vertex* uGraph::findByLabel(const string L) {
	if (key.find(L) != key.end()) {
		return key[L][0];
	}
	else return nullptr;
}

void uGraph::print() {
	for (auto i : index) {
		cout << i->label << " --> ";
		for (auto j : i->ways) {
			if (j->tar != i) {
				cout << j->tar->label << "(" << j->value << ") ";
			}
			else if (oriented == false) {
				cout << j->par->label << "(" << j->value << ") ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void uGraph::readFile(string S) {
	ifstream FS;
	FS.open(S);
	while (!FS.eof()) {
		string tmp;
		FS >> tmp;
		if (tmp == "ver") {
			string name;
			FS >> name;
			newVertex(name);
		}
		else if (tmp == "arc") {
			string from, to;
			float val;
			FS >> from >> to >> val;
			newArc(findByLabel(from), findByLabel(to), val);
		}
	}
	FS.close();
}

const auto uGraph::pathFind(vertex* from, vertex* to) {
	sortArcs();
	for (auto i : index) {
		i->dj = new dj_st{FLT_MAX,nullptr,false};
	}
	from->dj->sum = 0;
	queue<vertex*> pending;
	pending.push(from);
	while (!pending.empty()) {
		auto current = pending.front();
		for (auto i : current->ways) {
			vertex* j;
			if (oriented == true) {
				j = i->tar;
			}
			else {
				j = i->tar != current ? i->tar : i->par;
			}
			if (i->tar != current) {
				float tmp = current->dj->sum + i->value;
				if (tmp < i->tar->dj->sum) {
					i->tar->dj->sum = tmp;
					i->tar->dj->back = current;
				}
				if (i->tar->dj->done == false) {
					pending.push(i->tar);
				}
			}
		}
		current->dj->done = true;
		pending.pop();
	}
	stack<pair<vertex*,float>> out;
	vertex* cur = to;
	while (cur != from && cur != nullptr) {
		out.push(make_pair(cur,cur->dj->sum));
		cur = cur->dj->back;
	}
	for (auto i : index) {
		delete i->dj;
		i->dj = nullptr;
	}
	return out;
}