#include <iostream>
#include <vector>
#include <unordered_map>
#include "Vertex.h"
#include "Vertices.h"
#include "ColorSet.h"

void add_vertices(mwcs::Vertices *v);
void print_vertices(mwcs::Vertices v);
void print_neighbours(mwcs::Vertex v);
int main();


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
    for (auto it : table) {
        std::VertexColorPair current = it.first;
        mwcs::Vertex v = it.first.first;
        mwcs::ColorSet c = it.first.second;
        std::cout << "Vertex: " << v.get_name() << " colors: " << c.string() << " weight: " << it.second.get_weight() << " graph: " << it.second.string()<< std::endl;
        std::cout << "              ";
        print_vertices(it.second);
        std::cout<< std::endl;
    }
}

void print_vertices(mwcs::Vertices v) {
    //std::cout << "Nr of vertices is " << v.size() << std::endl;
    for (int i = 0; i < v.size(); i++) {
        mwcs::Vertex vertex = v.get_vertex(i);
        //std::cout << "Vertex " << vertex.get_name() << ", weight " << vertex.get_weight() << ", color "<< vertex.get_color() << ", neighbours: ";
        //print_neighbours(vertex);
        //std::cout << vertex.get_name() << " ";
    }
    std::cout << std::endl;
}

void print_neighbours(mwcs::Vertex v) {
    for (int i = 0; i < v.get_number_of_neighbors(); i++) {
        std::cout << v.get_neighbor(i).get_name() << ", ";
    }
}

void print_subsets(std::vector<mwcs::ColorSet> subset) {
    for (auto it : subset) {
        std::cout << it.string() << std::endl;
    }
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
        //std::cout << current.size() << size << std::endl;
        result->push_back(current);
        //std::cout << current.string() << std::endl;
        //std::cout << std::endl;
        return;
    }
    if (start > number_of_colors) return;

    current.add(start);
    get_subsets(number_of_colors, size, start + 1, current, result);
    current.remove(start);
    get_subsets(number_of_colors, size, start + 1, current, result);

}

void create_subsets(std::vector<mwcs::ColorSet> *result, int size, unsigned long number_of_colors) {

    mwcs::ColorSet current;
    get_subsets(number_of_colors, size, 1, current, result);
}

std::vector<mwcs::ColorSet> create_powerset(mwcs::ColorSet set) {
    //std::cout << "setsize: " << set.string() << set.size() << std::endl;
    std::vector<mwcs::ColorSet> result;
    for (int i = 1; i <= set.size(); i++) {
        //std::cout << "loopie " << i << " " << set.size() << std::endl;

        std::vector<mwcs::ColorSet> temp = set.create_subsets(i);
        result.insert(result.end(), temp.begin(), temp.end() );
    }
    return result;
}

std::unordered_map<std::VertexColorPair, mwcs::Vertices> find_max(std::unordered_map<std::VertexColorPair, mwcs::Vertices> table, mwcs::Vertex vertex, mwcs::Vertex neighbor, mwcs::ColorSet set) {
    mwcs::Vertices result;
    std::vector<mwcs::ColorSet> powerset = create_powerset(set);
    std::VertexColorPair best_pair = {vertex, vertex.get_color()};
    //print_subsets(powerset);
    //std::cout << "----------------------------------" << std::endl;

    for (auto it : powerset) {
        //std::cout << it.string() << std::endl;

        std::unordered_map<std::VertexColorPair, mwcs::Vertices>::const_iterator vertex_pair = table.find({vertex, it});
        //std::VertexColorPair best = vertex_pair->first;
        // als subset van powerset staat in table met vertex
        if (vertex_pair != table.end()) {
            //for (int i = 0; i < vertex.get_number_of_neighbors(); i ++) {
            //    std::cout << vertex.get_neighbor(i).get_name() << " ";
            //    result.add_vertex(vertex.get_neighbor(i));
            //}
            // als complement subset van powerset staat in table met neighbor
            mwcs::ColorSet temp = set.copy();
            temp.remove(it);
            //std::cout << "it: " << it.string() << std::endl;
            //std::cout << "temp: " << temp.string() << std::endl;
            std::unordered_map<std::VertexColorPair, mwcs::Vertices>::const_iterator neighbor_pair = table.find({neighbor, temp});
            if (neighbor_pair != table.end()) {
                if (!neighbor_pair->second.has_vertex(vertex)) {
                    std::cout << neighbor_pair->second.string() << std::endl;
                    int candidate = vertex_pair->second.get_weight() + neighbor_pair->second.get_weight();
                    //std::cout << candidate << std::endl;
                    if (candidate > result.get_weight()) {
                        result.add_vertex(vertex);
                        std::cout << "cand: " << candidate << " result: " << result.get_weight() << std::endl;
                        result.add_vertex(neighbor);
                        for (int i = 0; i < neighbor_pair->second.size(); i ++) {
                            result.add_vertex(neighbor_pair->second.get_vertex(i));
                        }
                        //best_pair = vertex_pair->first;
                        best_pair = {vertex, set};
                        std::cout << "set: " << set.string() << " with curr weight: " << result.get_weight() << " path: " << result.string()
                                  << std::endl;
                    }
                }
            }
        }
            //mwcs::ColorSet complement = current_pair->first.second.difference(it);

    }
    std::cout << best_pair.first.get_name() << " | " << best_pair.second.string() << std::endl;

    std::pair<std::VertexColorPair, mwcs::Vertices> entry (best_pair, result);
    //table->emplace(best_pair, result);

    std::unordered_map<std::VertexColorPair, mwcs::Vertices>::const_iterator current_pair = table.find({best_pair.first, best_pair.second});
    if (current_pair != table.end()) {
        table[best_pair] = result;
    } else {
        table.insert(entry);
    }
    std::cout << "result for vertex: " << vertex.get_name() << " neighbor: " << neighbor.get_name() << " is: " << result.get_weight() << std::endl;
    std::cout << "----------------- START TABLE ---------------------" << std::endl;
    print_table(table);
    std::cout << "----------------- END TABLE ---------------------" << std::endl;
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
    //colors.add(4);
    std::unordered_map<std::VertexColorPair, mwcs::Vertices> table;

    init_table(&table, vertices);

    for (int i = 2; i <= number_of_colors; i++) {
        //std::cout << "NEXT LOOP ---------------------------------------------" << std::endl;
        // create all possible sub color sets of size i
        std::vector<mwcs::ColorSet> subsets = colors.create_subsets(i);
        //std::vector<mwcs::ColorSet> subset_q = create_powerset(subsets);
        for (int j = 0; j < vertices.size(); j++) {
            mwcs::Vertex current = vertices.get_vertex(j);
            //std::cout << "cur vertex: " << current.get_name() << " " << current.get_color() << " ";

            for (int k = 0; k < current.get_number_of_neighbors(); k++) {
                mwcs::Vertex neighbor = current.get_neighbor(k);
                //std::cout << "cur neighbor: " << neighbor.get_name() << " " << neighbor.get_color() << std::endl;

                // for all subsets_q in t
                for (auto it : subsets) {
                    //std::cout << "NEXT SUBSET --------------------------------------------- " << it.string() << std::endl;

                    // is kleur van v element van subset?
                    if (it.has_color(current.get_color())) {
                        mwcs::ColorSet complement = it.copy();
                        complement.remove(current.get_color());
                        //std::cout << "comp: " << complement.string() << std::endl;
                        // ja -> is kleur van neighbor element van t-q?
                        if (complement.has_color(neighbor.get_color())) {
                            //std::cout << "cur: " << current.get_name() << " - " << current.get_color() << " neigh: " << neighbor.get_name() << " - " << neighbor.get_color() << std::endl;
                            //int max_weight = find_max(table, current, neighbor, it);
                            table = find_max(table, current, neighbor, it);
                        }
                    }
                    //std::cout << "----------------- START TABLE ---------------------" << std::endl;
                    //print_table(table);
                    //std::cout << "----------------- END TABLE ---------------------" << std::endl;

                    //print_subsets(subset_q);

                    //}


                }


                //std::unordered_map<std::VertexColorPair, int>::const_iterator neighbor_pair = table.find({neighbor, it});

                //   }

            }


        }
        //}
    }

    //print_table(table);



// Test dingen
    //print_vertices(vertices);

    //mwcs::cc_table main_table = init_table(vertices, number_of_colors);
    //main_table.print();

    //mwcs::ColorSet c;
    //c.add(2);
    //c.add(4);
    //bool test = c.has_color(4);

    //mwcs::ColorSet b;
    //b.add(3);
    //std::cout << test << std::endl;
    //mwcs::ColorSet a = c.difference(b);
    //std::cout << a.string() << std::endl;
    //std::unordered_map<std::VertexPair, int> m6;// = new std::unordered_map<mwcs::Vertex, std::string, std::size_t >;
    //m6 = { {{vertices.get_vertex(1), c}, 1}, {{vertices.get_vertex(2), b}, 5} };
    //std::VertexPair vp = {vertices.get_vertex(2), b};
    //std::cout << m6[vp];


    return 0;

}

