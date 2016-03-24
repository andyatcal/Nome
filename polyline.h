/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#ifndef __POLYLINE_H__
#define __POLYLINE_H__

#include <vector>
#include <glm/glm.hpp>
#include "mesh.h"

using namespace std;
using namespace glm;

//////////////////////////////////////////////////////////////////////
// Polyline Class -- A Polyline is a list of vertices
class PolyLine {
public:
    vector<Vertex*> vertices;
    bool isLoop;
    QColor color;
    PolyLine();
    /**
     * @brief drawLine: Draw this polyline in OpenGL
     */
    void drawLine();
    // Return the skewness of points in this polyline.
    /**
     * @brief skewness: Find the skeness of all points.
     * @return the skewness of points in this polyline.
     */
    vector<float> skewness();
    /**
     * @brief clear: clear this Polyline.
     */
    void clear();
    /**
     * @brief isEmpty: Find if this line is empty.
     * @return indicator of this polyline is empty.
     */
    bool isEmpty();
    /* Set the color of this mesh. */
    void setColor(QColor color);
    /* Indicator of whether user sets the color of this mesh.*/
    bool user_set_color;
    /* The transformations to go up one level. */
    vector<mat4> transformations_up;
    /* Set the transformation of this group. */
    void addTransformation(mat4 new_transform);
    /* Add a vertex to the current polyline. */
    void addVertex(Vertex *v);
};

#endif // __POLYLINE_H__
