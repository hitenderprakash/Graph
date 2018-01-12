/* Defines graph Node
 * Hitender Prakash
 */
 
#ifndef _GRAPH
#define _GRAPH

#include <string>
using namespace std;

class graphNode{
	public:
	string node_name;
	graphNode(string name):node_name(name){}
	friend bool operator==(const graphNode& a, const graphNode& b) {
		return (a.node_name == b.node_name);
	}
	friend bool operator<(const graphNode& a, const graphNode& b) {
		return (a.node_name < b.node_name);
	}
	friend bool operator>(const graphNode& a, const graphNode& b) {
		return (a.node_name > b.node_name);
	}
	friend ostream& operator<<(ostream& os,const graphNode &node){
		os << node.node_name;
		return os;  
	}
};

#endif
