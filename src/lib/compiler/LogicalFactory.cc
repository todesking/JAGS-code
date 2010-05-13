#include <config.h>

#include <compiler/LogicalFactory.h>
#include <compiler/NodeFactory.h>
#include <model/Model.h>
#include <graph/LogicalNode.h>
#include <graph/Node.h>
#include <graph/ScalarLogicalNode.h>
#include <graph/VectorLogicalNode.h>
#include <graph/ArrayLogicalNode.h>
#include <graph/VSLogicalNode.h>
#include <graph/LinkNode.h>
#include <util/dim.h>

#include <stdexcept>
#include <string>

using std::pair;
using std::map;
using std::vector;
using std::invalid_argument;
using std::runtime_error;
using std::string;

static bool lt(FunctionPtr const &arg1, FunctionPtr const &arg2)
{
    if (SCALAR(arg1) < SCALAR(arg2))
	return true;
    else if (LINK(arg1) < LINK(arg2))
	return true;
    else if (VECTOR(arg1) < VECTOR(arg2))
	return true;
    else if (ARRAY(arg1) < ARRAY(arg2))
	return true;
    else
	return false;
}

bool lt(LogicalPair const &arg1, LogicalPair const &arg2)
{
    // Order first by function
    if (lt(arg1.first, arg2.first)) {
	return true;
    }
    else if (lt(arg2.first, arg1.first)) {
	return false;
    }
    else {
	//Same function. Check parameters
	return lt(arg1.second, arg2.second);
    }
}

LogicalNode* LogicalFactory::newNode(FunctionPtr const &func, 
				     vector<Node const *> const &parents)
{
    LogicalNode *node = 0;
    if (SCALAR(func)) {
	unsigned int arglength = 1;
	for (unsigned int i = 0; i < parents.size(); ++i) {
	    if (parents[i]->length() > 1) {
		if (arglength == 1) {
		    arglength = parents[i]->length();
		}
		else if (parents[i]->length() != arglength) {
		    arglength = 0;
		    break;
		}
	    }
	}
	if (arglength == 0) {
	    throw runtime_error(string("Incompatible argument lengths for ") +
				func.name());
	}
	else if (arglength == 1) {
	    node = new ScalarLogicalNode(SCALAR(func), parents);
	}
	else {
	    node = new VSLogicalNode(SCALAR(func), parents);
	}
    }
    else if (LINK(func)) {
	bool ok = true;
	for (unsigned int i = 0; i < parents.size(); ++i) {
	    if (parents[i]->length() != 1) {
		ok = false;
		break;
	    }
	}
	if (ok) {
	    node = new LinkNode(LINK(func), parents);
	}
	else {
	    throw runtime_error("Invalid vector argument to " +	func.name());
	}
    }
    else if (VECTOR(func))
	node = new VectorLogicalNode(VECTOR(func), parents);
    else if (ARRAY(func))
	node = new ArrayLogicalNode(ARRAY(func), parents);
    else
	throw invalid_argument("Invalid function in getNode");
    return node;
}

Node* LogicalFactory::getNode(FunctionPtr const &func, 
			      vector<Node const *> const &parents,
			      Model &model)
{
    if (isNULL(func)) {
	throw invalid_argument("NULL function passed to getLogicalNode");
    }
    
    LogicalPair lpair(func, parents);
    map<LogicalPair, Node*, ltlogical>::iterator i = _logicalmap.find(lpair);

    if (i != _logicalmap.end()) {
	return i->second;
    }
    else {
	LogicalNode *lnode = newNode(func, parents);
	_logicalmap[lpair] = lnode;
	model.addNode(lnode);
	return lnode;
    }
}
