#ifndef GRAPH_H__
#define GRAPH_H__

#include <vector>
#include <set>
#include <string>
#include <memory>
#include "Edge.h"
#include "Node.h"

// Node colors are described at the bottom of the file.
#define WHITE 1
#define GRAY 2
#define BLACK 3

// Edge types are described at the bottom of the file.
#define UNDISCOVERED_EDGE 9
#define TREE_EDGE 10
#define BACK_EDGE 11
#define FORWARD_EDGE 12
#define CROSS_EDGE 13

using namespace std;


class Graph {
public:
  // The first block of public members are implemented for you.
  Graph();
  ~Graph();
  vector<shared_ptr<Node>> getNodes();
  vector<shared_ptr<Edge>> getEdges();
  int getClock();
  void addNode(shared_ptr<Node> n);
  void addEdge(shared_ptr<Edge> e);
  void removeNode(shared_ptr<Node> n);
  void removeEdge(shared_ptr<Edge> e);
  bool isDirected();
  void setDirected(bool val);
  set<shared_ptr<Edge>> getAdjacentEdges(shared_ptr<Node> n);
  friend std::ostream &operator << (std::ostream& out, Graph graph);

  // clear resets all nodes to have WHITE color, with -1 discovery and
  // finish times and rank. Resets all edges to type
  // UNDISCOVERED_EDGE. It resets the graph clock to 0.
  void clear();

  // tick is an OPTIONAL debugging method. Use this after every time
  // you increment the clock. You might pass in a string
  // to describe what just happened. If you are having trouble,
  // consider using this function as a place to track your algorithm's
  // progress. Print out your graph on each tick. If you want to get
  // very fancy, you can output your graph in 'dot' format. This is
  // the same format we used in the B-Tree assignment for debugging.
  //
  // This function is 100% optional, though.
  void tick(string message);

  // dfs(start) runs a depth-first search from the indicated start
  // node, and explores all reachable nodes. This ignores unreachable
  // nodes. When this function returns, all explored nodes are colored
  // BLACK, all unreachable nodes are WHITE. All explored nodes have
  // correct discovery/exit time information. All edges have correct
  // edge types (unfollowed edges should remain UNDISCOVERED).
  //
  // For a DFS, mark nodes GRAY when we first discover them, and BLACK
  // when we exit (finish) them.
  void dfs(shared_ptr<Node>);

  // bfs(start) runs a breadth-first search starting from the given
  // node. It sets the 'rank' value on all nodes to something
  // appropriate: -1 for unreachable nodes, 0 for the start node, 1
  // for nodes that are one edge from the start node, and so forth.
  //
  // For a BFS, mark nodes GRAY when they are enqueued, and BLACK when
  // they are dequeued.
  void bfs(shared_ptr<Node> start);

  // bfs(start, target) has the same requirements as the other version
  // of `bfs`, except this one stops after the target node is
  // reached. If found, the target node should be marked BLACK, and
  // its rank should be correctly set on exit. If it is not found, the
  // target node should remain WHITE with a rank of -1.
  void bfs(shared_ptr<Node> start, shared_ptr<Node> target);

private:
  bool directed;
  vector<shared_ptr<Node>> nodes;
  vector<shared_ptr<Edge>> edges;
  // The next two vectors may be used in your search algorithms.
  vector<shared_ptr<Edge>> search_edges;
  vector<shared_ptr<Node>> search_nodes;
  // The clock is used to set discovery/finish times. Increment it by
  // one every time a Node color changes to GRAY or BLACK.
  int clock;
};

#endif  // GRAPH_H__

/*

  Node color tells us if we have discovered a node, if we're in the
  middle of finishing a node, or if we've finished a node. They are:

  WHITE: Node has not yet been reached by the search.

  GRAY: Node has been reached by the search but is not yet complete.

  BLACK: Node has been completely explored.


  Edge type tells us information about how the path was discovered
  during a depth-first search, and it also might give us valuable
  information about the shape of the graph. There are four kinds of
  edges, though it is not necessary to use all of them all of the
  time. They are:

  TREE: A tree edge from A to B indicates that B was discovered via A.

  BACK: A back edge from C to A indicates that A was discovered before
  C, and C was discovered while A was still being explored.

  FORWARD: A forward edge from A to C indicates that C was completely
  examined when we found it, and A is an ancestor of C in the DFS
  spanning tree.

  CROSS: A cross edge from A to C indicates the C was completely
  examined when we found it, and A is NOT an ancestor of C in the DFS
  spanning tree.

  These edge types are summarized graphically at
  http://en.wikipedia.org/wiki/Depth-first_search and does a much
  better job than words can do.

  To determine edge types, you need to use both the discovery
  information (the color of the ending node) and the predecessor
  information (to distinguish between Cross and Forward edges).

  Tree edges are when the end node is white.

  Back edges are when the end node is gray.

  Forward and cross edges are when the end node is black. If the start
  node is an ancestor of the end node, it is a forward edge. Otherwise
  it is a cross edge.

 */