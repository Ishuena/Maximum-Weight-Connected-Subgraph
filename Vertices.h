//
// Created by Ishuena on 29/04/2017.
//

#ifndef BASIC_ALGO_VERTICES_H
#define BASIC_ALGO_VERTICES_H

#include <vector>
#include <unordered_map>
#include "Vertex.h"

namespace mwcs {
    class Vertices {
    public:
        Vertices();
        void add_vertex(Vertex v);

        const unsigned long size() const;
        const int get_weight() const;
        const std::string string() const;
        const bool has_vertex(Vertex v) const;

        const Vertex get_vertex(int i) const;

    private:
        std::vector<Vertex> vertices;
        int weight;
    };
}
#endif //BASIC_ALGO_VERTICES_H
