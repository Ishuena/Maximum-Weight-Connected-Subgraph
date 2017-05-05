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

        //const uint32_t get_id() const;

        Vertex get_neighbor(int i);

        void set_name(std::string n);

        void set_weight(int w);

        void set_color(uint32_t c);

        void set_neighbor(Vertex v);

        // friend?
        //void set_id(uint32_t vertex_id);

        bool operator==(Vertex const& other) const;

        //friend std::size_t hash_value(Vertex const& p);

       // friend std::size_t hash_value(Vertex const &p) {
       //     std::size_t seed = 0;
       //     boost::hash_combine(seed, p.name);

       //     return seed;
       // }



    private:
        std::string name;
        int weight;
        uint32_t color;
        std::vector<Vertex> neighbors;
        //uint32_t id; //friend?
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
