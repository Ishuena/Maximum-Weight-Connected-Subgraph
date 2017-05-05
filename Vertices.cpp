//
// Created by Ishuena on 29/04/2017.
//

#include "Vertex.h"
#include "Vertices.h"

namespace mwcs {

    mwcs::Vertices::Vertices() {
        //ids = 0;
        weight = INT_MIN;
    }

    void Vertices::add_vertex(Vertex v) {
        // Hack : oplossen in programma!
        if (!has_vertex(v)) {
            vertices.push_back(v);
            if (weight == INT_MIN) weight = 0;
            weight += v.get_weight();
        }
    }

    const unsigned long Vertices::size() const {
        return vertices.size();
    }

    const Vertex Vertices::get_vertex(int i) const {
        return vertices.at(i);
    }

    const bool Vertices::has_vertex(Vertex v) const {
        for (auto it : vertices) {
            if (v.get_name().compare(it.get_name()) == 0) return true;
        }
        return false;
    }

    const int Vertices::get_weight() const {
        return weight;
    }

    const std::string Vertices::string() const {
        std::string result = "";
        for (auto it : vertices) {
            result += it.get_name() + " ";
        }
        return result;
    }
}
