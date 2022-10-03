#include "Node.h"

//added default constructor with no input
Node::Node() {
}

Node::Node(string s) {
  // DONE FOR YOU
  data = s;
}

Node::~Node() {
  // "DONE" FOR YOU
  //
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}



string Node::getData() {
  // DONE FOR YOU
  return data;
}

void Node::setRank(int r) {
  // DONE FOR YOU
  rank = r;
}

int Node::getRank() {
  return rank;
}

//done
void Node::clear() {
  // clear sets the color to WHITE, the discovery/finish time and rank
  // to -1, and sets the predecessor to NULL.
  color = WHITE;
  discovery_time = -1;
  completion_time = -1;
  rank = -1;
  predecessor = shared_ptr<Node>(NULL);
}

void Node::setColor(int search_color, int time) {
  // setColor sets the 'color' of a node. Be sure to set the
  // appropriate time variable depending on what the new color is: set
  // discovery_time if the node is now GRAY, and completion_time if
  // the node is now BLACK. If it is now WHITE, this should be
  // equivalent to calling clear().
  color = search_color;

  if (color == GRAY) {
    discovery_time = time;
  }
  else if (color == BLACK) {
    completion_time = time;
  }
  else {
    clear();
  }
}

void Node::getDiscoveryInformation(int& thecolor, int& disco_time, 
				   int& finish_time, int& bfs_rank) {
    // getDiscoveryInformation gets the color, discovery time, and
  // finish time to 'color', 'disco_time', 'finish_time', and
  // 'bfs_rank' respectively.
  //
  // 'disco_time' and 'finish_time' are only meaningful if the search
  // was dfs (though there is no reason to not use these for debugging
  // purposes).
  //
  // 'bfs_rank' is only meaningful if bfs was the most recent search.
  thecolor = color;
  disco_time = discovery_time;
  finish_time = completion_time;
  bfs_rank = rank;
}

// isAncestor returns true if the given node is reachable by
// traversing the other node's predecessor list. It is like
// searching through a linked list. You can do this iteratively
// (with a cursor) or recursively by calling isAncestor on non-null
// predecessors.
bool Node::isAncestor(shared_ptr<Node> other) {
  bool found_ancestor;

  //one of these three conditions will execute each time
  if (this->predecessor == NULL) {//root node case
    found_ancestor = false;
  }
  else if (this->predecessor == other) {//we found the ancestor
    found_ancestor = true;
  }
  else {//if neither terminating condtion execute, there are more ancestors to explore
    found_ancestor = this->predecessor->isAncestor(other);
  }

  return found_ancestor; //return the result of our recursion
}

// Sets the predecessor node in the spanning tree. The predecessor
// node was the node that we were exploring when we first discovered
// a node (e.g. it was WHITE when we found it).
void Node::setPredecessor(shared_ptr<Node> other) {
  predecessor = other;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  // DONE FOR YOU
  out << node.data;
  return out;
}