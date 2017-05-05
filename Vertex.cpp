//
// Created by Ishuena on 29/04/2017.
//
#include "Vertex.h"

namespace mwcs {

    Vertex::Vertex(std::string n, int w) {
        name = n;
        weight = w;
    }

    Vertex::Vertex(std::string n, int w, uint32_t c) {
        name = n;
        weight = w;
        color = c;
    }

    const std::string Vertex::get_name() const{
        return name;
    }

    int Vertex::get_weight() {
        return weight;
    }

    uint32_t Vertex::get_color() {
        return color;
    }

    unsigned long Vertex::get_number_of_neighbors() {
        return neighbors.size();
    }

    Vertex Vertex::get_neighbor(int i) {
        return neighbors.at(i);
    }


    void Vertex::set_neighbor(Vertex v) {
        neighbors.push_back(v);
    }


    bool Vertex::operator==(Vertex const& other) const {
        return name.compare(other.name) == 0;
        //return id == other.id;
    }

    //const uint32_t Vertex::get_id() const {
    //    return id;
    //}

    //void Vertex::set_id(uint32_t vertex_id) {
    //    id = vertex_id;
    //}


}
