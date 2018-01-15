//defining methods declered in directedGraph.h
//Hitender Prakash

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include "directedGraph.h"
using namespace std;

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

//add node to the graph
void directedGraph::addNode(graphNode node){
	if(!nodeExists(node)){
		unordered_set<graphNode> temp;
		graph.insert({node,temp});
	}
}
void directedGraph::addNode(string nodename){
	addNode(graphNode(nodename));
}
//delete node
void directedGraph::deleteNode(graphNode node){
	if(!nodeExists(node)){
		return;
	}
	else{
		auto it=graph.find(node);
		graph.erase(it);	
		//also delete it from other's neighbor list
		for(auto it=graph.begin();it!=graph.end();it++){
			auto temp=it->second.find(node);
			if(temp!=it->second.end()){it->second.erase(node);}
		}
	}	
}

void directedGraph::deleteNode(string nodename){
	deleteNode(graphNode(nodename));
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
	else if(!nodeExists(sourceNode)){
		return 3; //dest does not exist
	}
}

int directedGraph::addEdge(string sourceNodeName, string destNodeName){
	return addEdge(graphNode(sourceNodeName), graphNode(destNodeName));
}

//delete edge
void directedGraph::deleteEdge(graphNode sourceNode, graphNode destNode){
	if(edgeExists(sourceNode, destNode)){
		auto it=graph.find(sourceNode);
		it->second.erase(destNode);
	}
}

void directedGraph::deleteEdge(string sourceNodeName, string destNodeName){
	deleteEdge(graphNode(sourceNodeName),graphNode(destNodeName));
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
		cout<<"\n"<<it->first<<"-->";
		for(auto i=it->second.begin();i!=it->second.end();i++){
			cout<<*i<<" ";
		}
	}
	cout<<"\n";
}

bool directedGraph::detectCycle_dfs(graphNode cur,unordered_set<graphNode> &explored,unordered_map<graphNode,int> onPath,unordered_set<graphNode> &loop,int depth){
	if(explored.find(cur)!=explored.end()){return false;}
	auto it=graph.find(cur);
	onPath[cur]=depth++;
	for(auto i=it->second.begin();i!=it->second.end();i++){
		if(onPath[*i]){
			for(auto j=onPath.begin();j!=onPath.end();j++){
				if(j->second >= onPath[*i]){loop.insert(j->first);}
			}
			return true;
		}
		bool temp=detectCycle_dfs(*i,explored, onPath,loop, depth);
		if(temp){return true;}
	}
	explored.insert(cur);
	return false;
}

bool directedGraph::getNodesSetInCycle(unordered_set<graphNode> &loop){
	unordered_set<graphNode> explored;
	
	unordered_map<graphNode,int> onPath;
	for(auto it=graph.begin();it!=graph.end();it++){
		if(explored.find(it->first)!=explored.end()){continue;}
		bool cycle=detectCycle_dfs(it->first,explored,onPath,loop,1);
		if(cycle){break;}	
	}
	if(loop.size()==0){return false;}	
	else{
		return true;
	}
}

bool directedGraph::hasCycle(){
	unordered_set<graphNode> loop;
	return getNodesSetInCycle(loop);
}

vector<graphNode> directedGraph::getNodesInCycle(){
	unordered_set<graphNode> loop;
	bool cycle= getNodesSetInCycle(loop);
	vector<graphNode> result;
	if(cycle){
		for(auto i=loop.begin();i!=loop.end();i++){
			result.push_back(*i);
		}
	}
	return result;
}

void directedGraph::removeAllCycles(){
	unordered_set<graphNode> explored;
	while(1){
		unordered_set<graphNode> loop;
		unordered_map<graphNode,int> onPath;
		for(auto it=graph.begin();it!=graph.end();it++){
			if(explored.find(it->first)!=explored.end()){continue;}
			bool hasCycle=detectCycle_dfs(it->first,explored,onPath,loop,1);
			if(hasCycle){break;}	
		}
		if(loop.size()==0){break;}	
		else{
			for(auto i=loop.begin();i!=loop.end();i++){
				deleteNode(*i);
			}
		}	
	}
}

//helper function used in topological sort method	
void directedGraph::recursiveTSHelper(unordered_map<graphNode,unordered_set<graphNode>> ::iterator it,unordered_set<graphNode> &visited,stack<graphNode> &resultStack){
	if(visited.find(it->first)!=visited.end()){return;}
	visited.insert(it->first);
	for(auto i=it->second.begin();i!=it->second.end();i++){
		auto itr=graph.find(*i);
		if(itr!=graph.end()){
			recursiveTSHelper(itr,visited,resultStack);
		}
	}
	resultStack.push(it->first);
}

//topological sort of graph ( require directed acyclic graph, if graph has cycle then result may be unpredictible)    
vector<graphNode> directedGraph::topologicalSort(){
	vector<graphNode> result;
	unordered_set<graphNode> visited;
	stack<graphNode> resultStack;
	for(auto it=graph.begin();it!=graph.end();it++){
		recursiveTSHelper(it,visited, resultStack);
	}
	while(!resultStack.empty()){ 
		result.push_back(resultStack.top());
		resultStack.pop();
	}
	return result;
	
}

//method to give level order of toological sort
//require output of topological sort as input  
vector<vector<graphNode>> directedGraph::levelOrder(vector<graphNode> &vec){
	unordered_map<graphNode,int> mp;
	for(int i=0;i<vec.size();i++){
		mp[vec[i]]=1;
	}
	int mx=0;
	for(int i=0;i<vec.size();i++){
		int val=mp[vec[i]];
		mx=max(mx,val);
		auto it=graph.find(vec[i]);
		if(it!=graph.end()){
			for(auto i=it->second.begin();i!=it->second.end();i++){
				mp[*i]=max(mp[*i],val+1);
				mx=max(mx,mp[*i]);
			}
		}
	}
	vector<vector<graphNode>> resultvec(mx);
	for(auto i=mp.begin();i!=mp.end();i++){
		resultvec[i->second-1].push_back(i->first);
	}	
	return 	resultvec;
}

//BFS on a given node
vector<vector<graphNode>> directedGraph::BFS(graphNode node){
	vector<vector<graphNode>> BFSResult;
	if(graph.find(node)==graph.end()){
		return BFSResult;
	}
	queue<graphNode> q;
	unordered_set<graphNode> discovered;
	q.push(node);

	while(!q.empty()){
		int qsz=q.size();
		vector<graphNode> level;
		for(int i=0;i<qsz;i++){
			graphNode cur=q.front();
			q.pop();
			level.push_back(cur);
			
			auto it=graph.find(cur);
			for(auto i=it->second.begin();i!=it->second.end();i++){
				if(discovered.find(*i)==discovered.end()){
					q.push(*i);
					discovered.insert(*i);
				}
			}	
		}
		BFSResult.push_back(level);	
	}
	return BFSResult;
}

vector<vector<graphNode>> directedGraph::BFS(string nodename){
	return BFS(graphNode(nodename));
}

//method to generate the directed graph from given vector of edges
//input is a vector of pairs like [ [a,b],[c,d]] , pair [a,b] represent edge a->b
//also require a reference of directedGraph to be generated (which initially is empty)
void directedGraph::generateDirectedGraphWithEdges(vector<pair<string,string>>& edges){
	for(int i=0;i<edges.size();i++){
		addNode(edges[i].first);
		addNode(edges[i].second);
		addEdge(edges[i].first,edges[i].second);
	}       
}


 

