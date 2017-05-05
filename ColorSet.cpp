//
// Created by Ishuena on 02/05/2017.
//

#include <string>
#include <vector>
#include <iostream>
#include "ColorSet.h"

mwcs::ColorSet::ColorSet() {
    colors = 0;
    number_of_colors = 0;
}

mwcs::ColorSet::ColorSet(int number_of_colors) {
    for (int i = 1; i <= number_of_colors; i++) {
        add(i);
    }
}

void mwcs::ColorSet::add(int color) {
    colors = (colors | (1 << (color - 1)));
    number_of_colors += 1;
}

void mwcs::ColorSet::remove(int color) {
    colors = (colors & ~(1 << (color - 1)));
    number_of_colors -= 1;
}

void mwcs::ColorSet::remove(ColorSet set) {
    colors = colors & (~set.colors);

    int count = 0;

    for (int i = 1; i <= 32; i++) {
        if (has_color(i) && !set.has_color(i)) {
            count += 1;
        }
    }

    number_of_colors = count;
}

int mwcs::ColorSet::size() {
    return number_of_colors;
}

const bool mwcs::ColorSet::has_color(int color) const {
    return 1 << (color - 1) == (colors & (1 << (color - 1)));
}

bool mwcs::ColorSet::operator==(ColorSet const& other) const {
    return colors == other.colors;
}

int mwcs::ColorSet::get_next(int start) {
    while (!has_color(start)) {
        start++;
    }
    return start;
}

mwcs::ColorSet mwcs::ColorSet::copy() {
    ColorSet result;
    result.colors = colors;
    result.number_of_colors = number_of_colors;
    return result;
}

void mwcs::ColorSet::get_subsets(int size, int start, ColorSet current, std::vector<mwcs::ColorSet> *result) {
    if (current.number_of_colors == size) {
        result->push_back(current.copy());
        return;
    }
    if (start >= 32) return;

    current.add(start);
    get_subsets(size, get_next(start + 1), current, result);
    current.remove(start);
    get_subsets(size, get_next(start + 1), current, result);
}

std::vector<mwcs::ColorSet> mwcs::ColorSet::create_subsets(int size) {
    std::vector<mwcs::ColorSet> result;
    mwcs::ColorSet current;
    get_subsets(size, get_next(0), current, &result);
    return result;
}

std::vector<mwcs::ColorSet> mwcs::ColorSet::create_powerset() {
    std::vector<mwcs::ColorSet> result;
    mwcs::ColorSet current;

    for (int i = 1; i <= number_of_colors; i++) {
        get_subsets(i, get_next(0), current, &result);
    }
    return result;
}


// friendly?
const uint32_t mwcs::ColorSet::get_colors() const {
    return colors;
}

const std::string mwcs::ColorSet::string() const {
    std::string result = "";
    for (int i = 1; i <= 32; i++) {
        if (has_color(i)) {
            result += std::to_string(i) + " ";
        }
    }
    return result;
}
