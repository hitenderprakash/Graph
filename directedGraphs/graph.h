#ifndef _GRAPH
#define _GRAPH

#include <string>
using namespace std;

class graphNode{
	public:
	string node_name;
	graphNode(string name):node_name(name){}
	bool friend operator==(const graphNode& a, const graphNode& b) {
		return (a.node_name == b.node_name);
	}
	bool friend operator<(const graphNode& a, const graphNode& b) {
		return (a.node_name < b.node_name);
	}
	bool friend operator>(const graphNode& a, const graphNode& b) {
		return (a.node_name > b.node_name);
	}
};

#endif
