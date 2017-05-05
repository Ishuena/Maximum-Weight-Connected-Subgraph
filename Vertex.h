//
// Created by Ishuena on 29/04/2017.
//

#ifndef BASIC_ALGO_VERTEX_H
#define BASIC_ALGO_VERTEX_H

#include <string>
#include <vector>
#include <boost/functional/hash.hpp>
#include "ColorSet.h"

namespace mwcs {
    class Vertex {

    public:
        Vertex(std::string n, int w, uint32_t c);
        Vertex(std::string n, int w);

        const std::string get_name() const;
        int get_weight();
        uint32_t get_color();
        unsigned long get_number_of_neighbors();
        Vertex get_neighbor(int i);
        void set_neighbor(Vertex v);
        bool operator==(Vertex const& other) const;

    private:
        std::string name;
        int weight;
        uint32_t color;
        std::vector<Vertex> neighbors;
    };
}

namespace std
{
    using VertexColorPair = pair<mwcs::Vertex, mwcs::ColorSet>;
    template<>
    struct hash<VertexColorPair>
    {
        size_t operator()(VertexColorPair const& p) const
        {
            std::size_t seed = 0;
            boost::hash_combine(seed, p.first.get_name());
            boost::hash_combine(seed, p.second.get_colors());

            return seed;
        }
    };
}

#endif //BASIC_ALGO_VERTEX_H
