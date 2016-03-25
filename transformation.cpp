/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "transformation.h"

void transform(Mesh & mesh, mat4 matrix)
{
    vector<Vertex*>::iterator vIt;
    for(vIt = mesh.vertList.begin(); vIt < mesh.vertList.end(); vIt++) {
        (*vIt) -> position = vec3(matrix * vec4((*vIt) -> position, 1));
    }
}

void transform(PolyLine &line, mat4 matrix)
{
    vector<Vertex*>::iterator vIt;
    for(vIt = line.vertices.begin(); vIt < line.vertices.end(); vIt++) {
        (*vIt) -> position = vec3(matrix * vec4((*vIt) -> position, 1));
    }
}

mat4 krotate(vec3 rot_axis, float radian) {
    return glm::rotate(radian, rot_axis);
}

mat4 kscale(vec3 scales) {
    return scale(scales);
}

mat4 ktranslate(vec3 translation) {
    return translate(translation);
}

mat4 kmirror(vec4 mirror_plane) {
    mat4 result;
    float d = mirror_plane[3];
    vec3 plane_normal = vec3(mirror_plane);
    float k = - d / length(plane_normal);
    //cout<<k<<endl;
    plane_normal = normalize(plane_normal);
    float a = plane_normal[0];
    float b = plane_normal[1];
    float c = plane_normal[2];
    result[0][0] = 1 - 2 * a * a;
    result[0][1] = - 2 * a * b;
    result[0][2] = - 2 * a * c;
    result[0][3] = 0;
    result[1][0] = - 2 * a * b;
    result[1][1] = 1 - 2 * b * b;
    result[1][2] = - 2 * b * c;
    result[1][3] = 0;
    result[2][0] = - 2 * a * c;
    result[2][1] = - 2 * b * c;
    result[2][2] = 1 - 2 * c * c;
    result[2][3] = 0;
    result[3][0] = 2 * a * k;
    result[3][1] = 2 * b * k;
    result[3][2] = 2 * c * k;
    result[3][3] = 1;
    return result;
}

PolyLine polylineCopy(PolyLine &line)
{
    PolyLine newPolyline;
    newPolyline.clear();
    vector<Vertex*>::iterator vIt;
    for(vIt = line.vertices.begin();
        vIt < line.vertices.end(); vIt ++) {
        Vertex * vertCopy = new Vertex;
        vertCopy -> ID = (*vIt) -> ID;
        vertCopy -> position = (*vIt) -> position;
        newPolyline.addVertex(vertCopy);
    }
    newPolyline.setColor(line.color);
}
