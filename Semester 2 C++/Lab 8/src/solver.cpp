#include "solver.h"

std::vector<uchar> solve(std::array<std::array<uchar, 9>, 6> &colors) 
{
    Rubik rubik;
    std::vector<uchar> solution;

    rubik.readRubik(colors);
    rubik.solve(solution);

    return solution;
}