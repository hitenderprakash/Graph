#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <utility>
#include "directedGraph.h"
using namespace std;

//defining methods declered in directedGraph.h
void directedGraph::addNode(graphNode node){
	unordered_set<graphNode> temp;
	graph.insert({node,temp});
}
void directedGraph::addNode(string nodename){
	addNode(graphNode(nodename));
}

//check if node exists
bool directedGraph::nodeExists(graphNode node){
	if(graph.find(node)!=graph.end()){
		return true;
	}
	else{
		return false;
	}
}
bool directedGraph::nodeExists(string nodename){
	return (nodeExists(graphNode(nodename)));
}

//display graph nodes
void directedGraph::displayGraphNodes(){
	for(auto it=graph.begin();it!=graph.end();it++){
		cout<<"\n"<<it->first.node_name;
	}
	cout<<"\n";
}

//find total number of nodes in graph
int directedGraph::nodeCount(){
	return graph.size();
}

//add edge 
int directedGraph::addEdge(graphNode sourceNode, graphNode destNode){
	if(nodeExists(sourceNode)&& nodeExists(destNode)){
		auto sourceIt=graph.find(sourceNode);
		if(sourceIt->second.find(destNode)!=sourceIt->second.end()){
			return -1; //edge already exists
		}
		sourceIt->second.insert(destNode);
		return 0; //success
	}
	else if(!nodeExists(sourceNode) && !nodeExists(destNode)){
		return 2; //source and dest nodes does not exists
	}
	else if(!nodeExists(sourceNode)){
		return 1; //source does not exists
	}
	else if(!!nodeExists(sourceNode)){
		return 3; //dest does not exist
	}
}

int directedGraph::addEdge(string sourceNodeName, string destNodeName){
	return addEdge(graphNode(sourceNodeName), graphNode(destNodeName));
}
//check if edge exists
bool directedGraph::edgeExists(graphNode sourceNode, graphNode destNode){
	if(nodeExists(sourceNode)&& nodeExists(destNode)){
		auto it=graph.find(sourceNode);
		if(it->second.find(destNode)!=it->second.end()){
			return true;
		}
		else { return false;}
	}
	else{
		return false;
	}
	
}
bool directedGraph::edgeExists(string sourceNodeName, string destNodeName){
	return edgeExists(graphNode(sourceNodeName), graphNode(destNodeName));
}

void directedGraph::displayGraph(){
	for(auto it=graph.begin();it!=graph.end();it++){
		cout<<"\n"<<it->first.node_name<<"-->";
		for(auto i=it->second.begin();i!=it->second.end();i++){
			cout<<i->node_name<<" ";
		}
	}
	cout<<"\n";
}

