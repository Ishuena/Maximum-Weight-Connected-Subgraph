//
// Created by Ishuena on 29/04/2017.
//

#include "Vertex.h"
#include "Vertices.h"

namespace mwcs {

    mwcs::Vertices::Vertices() {
        //ids = 0;
    }

    void Vertices::add_vertex(Vertex v) {
        //ids += 1;
        //v.set_id(ids);
        vertices.push_back(v);
    }

    unsigned long Vertices::size() {
        return vertices.size();
    }

    Vertex Vertices::get_vertex(int i) {
        return vertices.at(i);
    }
}
