#ifndef RUNTIME_MATH_EDGE_H
#define RUNTIME_MATH_EDGE_H

/**
 * Implements an edge consisting of two vertices.
 */
struct Edge
{
	/** Holds the edge vertices. */	
	Vector3 _vectex[2];
	/** */
	int32 _count;
public:
	Edge() {};
	Edge(Vector3 v1, Vector3 v2)
	{
		_vertex[0] = v1;
		_vertex[1] = v2;
		_count = 0;
	}
public:
	/**
	 * Compares this edge with another.
	 *
	 * @param e The other edge.
	 * @return true if the two edges are identical, false otherwise.
	 */
	bool operator== (const Edge& e) const
	{
		return (((e._vertex[0] == _vertex[0]) && (e._vertex[1] == _vertex[1])) || ((e._vertex[0] == _vertex[1]) && (e._vertex[1] == _vertex[0])));
	}
}

#endif
