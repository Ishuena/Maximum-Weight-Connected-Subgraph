//
// Created by Ishuena on 02/05/2017.
//

#ifndef BASIC_ALGO_COLORSET_H
#define BASIC_ALGO_COLORSET_H


#include <cstdint>
namespace mwcs {
    class ColorSet {

    public:
        ColorSet();
        ColorSet(int number_of_colors);

        mwcs::ColorSet copy();
        void add(int color);
        void remove(int color);
        void remove(ColorSet set);
        int size();
        std::vector<mwcs::ColorSet> create_subsets(int size);
        std::vector<mwcs::ColorSet> create_powerset();
        const bool has_color(int color) const;
        bool operator==(ColorSet const& other) const;
        const uint32_t get_colors() const;
        const std::string string() const;

    private:
        uint32_t colors;
        int number_of_colors;
        int get_next(int start);
        void get_subsets(int size, int start, ColorSet current, std::vector<mwcs::ColorSet> *result);
    };
}

#endif //BASIC_ALGO_COLORSET_H
