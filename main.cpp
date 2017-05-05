#include <iostream>
#include <vector>
#include <unordered_map>
#include "Vertex.h"
#include "Vertices.h"

void add_vertices(mwcs::Vertices *v) {
    // vertex (name, weight, color)
    mwcs::Vertex a("a", 2, 1);
    mwcs::Vertex b("b", 4, 2);
    mwcs::Vertex c("c", 3, 2);
    mwcs::Vertex d("d", -2, 1);
    mwcs::Vertex e("e", 6, 3);
    mwcs::Vertex f("f", 10, 3);
    a.set_neighbor(b);
    a.set_neighbor(e);
    b.set_neighbor(a);
    b.set_neighbor(c);
    b.set_neighbor(e);
    c.set_neighbor(b);
    c.set_neighbor(d);
    d.set_neighbor(c);
    d.set_neighbor(e);
    d.set_neighbor(f);
    e.set_neighbor(a);
    e.set_neighbor(b);
    e.set_neighbor(d);
    f.set_neighbor(d);
    v->add_vertex(a);
    v->add_vertex(b);
    v->add_vertex(c);
    v->add_vertex(d);
    v->add_vertex(e);
    v->add_vertex(f);
}

void add_vertices_2(mwcs::Vertices *v) {
    // vertex (name, weight, color)
    mwcs::Vertex a("a", 2, 3);
    mwcs::Vertex b("b", 4, 2);
    mwcs::Vertex c("c", 3, 1);
    mwcs::Vertex d("d", -2, 3);
    mwcs::Vertex e("e", 6, 1);
    mwcs::Vertex f("f", 10, 2);
    a.set_neighbor(b);
    a.set_neighbor(e);
    b.set_neighbor(a);
    b.set_neighbor(c);
    b.set_neighbor(e);
    c.set_neighbor(b);
    c.set_neighbor(d);
    d.set_neighbor(c);
    d.set_neighbor(e);
    d.set_neighbor(f);
    e.set_neighbor(a);
    e.set_neighbor(b);
    e.set_neighbor(d);
    f.set_neighbor(d);
    v->add_vertex(a);
    v->add_vertex(b);
    v->add_vertex(c);
    v->add_vertex(d);
    v->add_vertex(e);
    v->add_vertex(f);
}

void print_table(std::unordered_map<std::VertexColorPair, mwcs::Vertices> table) {
    std::cout << "----------------- START TABLE ---------------------" << std::endl;
    for (auto it : table) {
        std::VertexColorPair current = it.first;
        mwcs::Vertex v = it.first.first;
        mwcs::ColorSet c = it.first.second;
        std::cout << "Vertex: " << v.get_name() << " colors: " << c.string() << " weight: " << it.second.get_weight() << " graph: " << it.second.string()<< std::endl;
    }
    std::cout << "----------------- END TABLE ---------------------" << std::endl;
}

void init_table(std::unordered_map<std::VertexColorPair, mwcs::Vertices> *table, mwcs::Vertices vertices) {
    for (int i = 0; i < vertices.size(); i++) {
        mwcs::Vertex current = vertices.get_vertex(i);
        mwcs::ColorSet c;
        c.add(current.get_color());
        std::VertexColorPair tkey = {current, c};
        mwcs::Vertices v;
        v.add_vertex(current);
        /* Check which method is better */
        //table->emplace(tkey, current.get_weight());
        std::pair<std::VertexColorPair, mwcs::Vertices> entry (tkey, v);
        table->insert(entry);
    }
}

void get_subsets(unsigned long number_of_colors, int size, int start, mwcs::ColorSet current, std::vector<mwcs::ColorSet> *result) {
    if (current.size() == size) {
        result->push_back(current);
        return;
    }
    if (start > number_of_colors) return;

    current.add(start);
    get_subsets(number_of_colors, size, start + 1, current, result);
    current.remove(start);
    get_subsets(number_of_colors, size, start + 1, current, result);
}

std::vector<mwcs::ColorSet> create_powerset(mwcs::ColorSet set) {
    std::vector<mwcs::ColorSet> result;
    for (int i = 1; i <= set.size(); i++) {

        std::vector<mwcs::ColorSet> temp = set.create_subsets(i);
        result.insert(result.end(), temp.begin(), temp.end() );
    }
    return result;
}

std::unordered_map<std::VertexColorPair, mwcs::Vertices> find_max(std::unordered_map<std::VertexColorPair, mwcs::Vertices> table, mwcs::Vertex vertex, mwcs::Vertex neighbor, mwcs::ColorSet set) {
    mwcs::Vertices result;
    std::vector<mwcs::ColorSet> powerset = create_powerset(set);
    std::VertexColorPair best_pair = {vertex, vertex.get_color()};

    for (auto it : powerset) {

        std::unordered_map<std::VertexColorPair, mwcs::Vertices>::const_iterator vertex_pair = table.find({vertex, it});
        // als subset van powerset staat in table met vertex
        if (vertex_pair != table.end()) {
            // als complement subset van powerset staat in table met neighbor
            mwcs::ColorSet temp = set.copy();
            temp.remove(it);
            std::unordered_map<std::VertexColorPair, mwcs::Vertices>::const_iterator neighbor_pair = table.find({neighbor, temp});
            if (neighbor_pair != table.end()) {
                if (!neighbor_pair->second.has_vertex(vertex)) {
                    int candidate = vertex_pair->second.get_weight() + neighbor_pair->second.get_weight();
                    if (candidate > result.get_weight()) {
                        result.add_vertex(vertex);
                        result.add_vertex(neighbor);
                        for (int i = 0; i < neighbor_pair->second.size(); i ++) {
                            result.add_vertex(neighbor_pair->second.get_vertex(i));
                        }
                        best_pair = {vertex, set};
                    }
                }
            }
        }
    }
    std::pair<std::VertexColorPair, mwcs::Vertices> entry (best_pair, result);
    std::unordered_map<std::VertexColorPair, mwcs::Vertices>::const_iterator current_pair = table.find({best_pair.first, best_pair.second});
    if (current_pair != table.end()) {
        if (current_pair->second.get_weight() < result.get_weight()) table[best_pair] = result;
    } else {
        table.insert(entry);
    }
    return table;
}


int main() {
    unsigned long number_of_colors = 3;
    mwcs::Vertices vertices;
    add_vertices_2(&vertices);

    mwcs::ColorSet colors;
    colors.add(1);
    colors.add(2);
    colors.add(3);
    std::unordered_map<std::VertexColorPair, mwcs::Vertices> table;

    init_table(&table, vertices);

    for (int i = 2; i <= number_of_colors; i++) {
        // create all possible sub color sets of size i
        std::vector<mwcs::ColorSet> subsets = colors.create_subsets(i);
        for (int j = 0; j < vertices.size(); j++) {
            mwcs::Vertex current = vertices.get_vertex(j);

            for (int k = 0; k < current.get_number_of_neighbors(); k++) {
                mwcs::Vertex neighbor = current.get_neighbor(k);

                // for all subsets_q in t
                for (auto it : subsets) {

                    // is kleur van v element van subset?
                    if (it.has_color(current.get_color())) {
                        mwcs::ColorSet complement = it.copy();
                        complement.remove(current.get_color());

                        // ja -> is kleur van neighbor element van t-q?
                        if (complement.has_color(neighbor.get_color())) {
                            table = find_max(table, current, neighbor, it);
                        }
                    }
                }
            }
        }
    }
    print_table(table);
    return 0;
}

