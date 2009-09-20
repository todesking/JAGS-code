#include <config.h>
#include <graph/Graph.h>
#include <graph/GraphMarks.h>
#include <graph/Node.h>
#include <graph/StochasticNode.h>
#include <graph/DeterministicNode.h>

#include <stdexcept>
#include <vector>
#include <set>
#include <algorithm>

using std::vector;
using std::set;
using std::invalid_argument;
using std::logic_error;
using std::reverse;

Graph::Graph()
    : _nodes(), _stoch_nodes()
{
}


Graph::~Graph()
{
}

void Graph::add(StochasticNode *snode)
{
    if (!snode) {
      throw invalid_argument("Attempt to add null node to graph");
    }
    if (!this->contains(snode)) {
      _nodes.insert(snode);
      _stoch_nodes.insert(snode);
    }
}

void Graph::add(Node *node)
{
  if (!node) {
    throw invalid_argument("Attempt to add null node to graph");
  }
  if (!this->contains(node)) {
    _nodes.insert(node);
  }
}

void Graph::remove(StochasticNode *snode)
{
    if (this->contains(snode)) {
       _stoch_nodes.erase(snode);
       _nodes.erase(snode);
    }
}

void Graph::remove(Node *node)
{
  if (this->contains(node)) {
      _nodes.erase(node);
  }
}

void Graph::clear()
{
    _nodes.clear();
}

bool Graph::contains(Node const *node) const
{
    return  _nodes.find(const_cast<Node*>(node)) != _nodes.end();
}

unsigned int Graph::size() const
{
  return _nodes.size();
}

#include <graph/NodeError.h>
bool Graph::isClosed() const
{
    //Determine whether any nodes in the graph have children or
    //parents outside the graph 

    for (set<Node*>::iterator i = _nodes.begin(); i != _nodes.end(); i++) {
    
	// Check parents
	vector<Node const *> const &parents = (*i)->parents();
	for (vector<Node const *>::const_iterator j = parents.begin(); 
	     j != parents.end(); j++) 
	{
	    if (!this->contains(*j)) {
	        throw NodeError(*i, "Bad parent"); //debuggin
		return false;
	    }
	}

	// Check children
	StochasticNodeSet const *sch = (*i)->stochasticChildren();
	for (StochasticNodeSet::iterator k = sch->begin(); k != sch->end(); k++)
	{
	    if (!this->contains(*k)) {
	        throw NodeError(*k, "is bad stochastic child"); //debuggin
		return false;
	    }
	}

	set<DeterministicNode*> const *dch = (*i)->deterministicChildren();
	for (set<DeterministicNode*>::iterator k = dch->begin(); k != dch->end(); k++)
	{
	    if (!this->contains(*k)) {
	        throw NodeError(*k, "is bad deterministic child"); //debuggin
		return false;
	    }
	}
    }
    return true;
}

StochasticNodeSet const &Graph::stochasticNodes() const
{
    return _stoch_nodes;
}

set<Node*> const &Graph::nodes() const
{
    return _nodes;
}

void Graph::getNodes(vector<Node*> &nodes) const
{
  for (set<Node*>::iterator p = _nodes.begin();
       p != _nodes.end(); p++)
    {
      nodes.push_back(*p);
    }
}

/* Helper function for Graph::getSortedNodes. Returns true
   if node has any children in set S */
static bool childInSet(Node *node, set<Node*> const &S)
{
    for (set<StochasticNode *>::const_iterator j = node->stochasticChildren()->begin(); 
	 j != node->stochasticChildren()->end(); ++j) 
    {
	if (S.count(*j)) {
	    return true;
	}
    }
    for (set<DeterministicNode *>::const_iterator j = node->deterministicChildren()->begin(); 
	 j != node->deterministicChildren()->end(); ++j) 
    {
	if (S.count(*j)) {
	    return true;
	}
    }
    return false;
}


void Graph::getSortedNodes(set<Node*> &S, vector<Node*> &sortednodes) 
{
    /* 
       Return a vector of nodes whose ordering follows the partial
       ordering of the set.  If a is after b then there is never a
       path from a to b.
    */

    if (!sortednodes.empty()) {
	throw logic_error("vector not empty in getSortedNodes");
    }

    sortednodes.reserve(S.size());

    while (!S.empty()) {

	bool loopcheck = false;

	set<Node*>::iterator i = S.begin();
	while (i != S.end()) {
	    if (childInSet(*i, S)) {
		++i;
	    }
	    else {
		loopcheck = true;
		sortednodes.push_back(*i);
		set<Node*>::iterator j = i;
		++i;
		S.erase(j);
	    }
	}
	
	if (!loopcheck) {
	    //We did not add any nodes to sortednodes on this pass
	    throw logic_error("Failure in Graph::getSortedNodes. Directed cycle in graph");
	}
    }

    reverse(sortednodes.begin(), sortednodes.end());
}

void Graph::getSortedNodes(vector<Node*> &sortednodes) const
{
    set<Node*> S = _nodes;
    getSortedNodes(S, sortednodes);
}
