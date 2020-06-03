#include "cube.h"
#include <ctime>
#include <string>

void Cube::clear()
{
    // верх
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            parts[i][j][2].set_color(0, default_colors[0]);

    // низ
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            parts[i][j][0].set_color(1, default_colors[1]);

    // спереди
    for (size_t k = 0; k < 3; k++)
        for (size_t j = 0; j < 3; j++)
            parts[j][0][k].set_color(2, default_colors[2]);

    // сзади
    for (size_t k = 0; k < 3; k++)
        for (size_t j = 0; j < 3; j++)
            parts[j][2][k].set_color(3, default_colors[3]);

    // слева
    for (size_t i = 0; i < 3; i++)
        for (size_t k = 0; k < 3; k++)
            parts[0][k][i].set_color(4, default_colors[4]);

    // справа
    for (size_t i = 0; i < 3; i++)
        for (size_t k = 0; k < 3; k++)
            parts[2][k][i].set_color(5, default_colors[5]);

    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            for (size_t k = 0; k < 3; k++)
                parts[i][j][k].set_size((size / 3.0) * 0.95);
}

void Cube::input()
{
    std::ifstream fin;
    std::cout << "INPUT\n"
                 "Green side must be in front and a white side must be on top\n"
                 "input in the same order: \n"
                 "w - white, o - orange, g - green, r - red, b - blue, y - yellow\n"
                 "Input will use a file. Input file name to open or create a file\n"
                 "called 'cube' and then just enter n or press d to make default cube\n"
                 "and shuffle cube 15 times\n";
    std::string s;
    std::cin >> s;
    if (s == "n")
        fin.open("cube", std::ios_base::binary);
    else if (s == "d")
    {
        shuff = true;
        make_shuffeled();
        shuff = false;
        return;
    }
    else
        fin.open(s, std::ios_base::binary);

    if (!fin.is_open())
        throw MyException("File aren't open");

    // верх
    for (int j = 2; j >= 0; j--)
        for (int i = 0; i < 3; i++)
        {
            fin >> colors_by_s[0][(2 - j) * 3 + i];
            parts[i][j][2].set_color(0, colors_by_s[0][(2 - j) * 3 + i]);
        }

    // слева
    for (int i = 2; i >= 0; i--)
        for (int k = 2; k >= 0; k--)
        {
            fin >> colors_by_s[1][(2 - i) * 3 + (2 - k)];
            parts[0][k][i].set_color(4, colors_by_s[1][(2 - i) * 3 + (2 - k)]);
        }

    // спереди
    for (int k = 2; k >= 0; k--)
        for (int j = 0; j < 3; j++)
        {
            fin >> colors_by_s[2][(2 - k) * 3 + j];
            parts[j][0][k].set_color(2, colors_by_s[2][(2 - k) * 3 + j]);
        }

    // справа
    for (int i = 2; i >= 0; i--)
        for (int k = 0; k < 3; k++)
        {
            fin >> colors_by_s[3][(2 - i) * 3 + k];
            parts[2][k][i].set_color(5, colors_by_s[3][(2 - i) * 3 + k]);
        }

    // сзади
    for (int k = 2; k >= 0; k--)
        for (int j = 2; j >= 0; j--)
        {
            fin >> colors_by_s[4][(2 - k) * 3 + (2 - j)];
            parts[j][2][k].set_color(3, colors_by_s[4][(2 - k) * 3 + (2 - j)]);
        }

    // низ
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
        {
            fin >> colors_by_s[5][j * 3 + i];
            parts[i][j][0].set_color(1, colors_by_s[5][j * 3 + i]);
        }
}

void Cube::solver()
{
    update_colors();
    path = solve(colors_by_s);
    for (auto it = path.begin(); it < path.end(); it++)
    {
        if (*it == 'f')
        {
            it = path.insert(path.erase(it), 3, 'F') + 2;
            continue;
        }
        if (*it == 'W')
        {
            it = path.insert(path.erase(it), 3, 'w') + 2;
            continue;
        }
        if (*it == 'R')
        {
            it = path.insert(path.erase(it), 3, 'r') + 2;
            continue;
        }
        if (*it == 'l')
        {
            it = path.insert(path.erase(it), 3, 'L') + 2;
            continue;
        }
        if (*it == 'U')
        {
            it = path.insert(path.erase(it), 3, 'u') + 2;
            continue;
        }
        if (*it == 'd')
        {
            it = path.insert(path.erase(it), 3, 'D') + 2;
            continue;
        }
    }

    for (auto it = path.begin(); it < path.end(); it++)
    {
        if (it + 3 < path.end() && *it == *(it + 1) && *it == *(it + 2) && *it == *(it + 3) && *it == *(it + 4))
        {
            it = path.erase(it, it + 4) - 1;
        }
    }

    std::cout << "Way to solve:" << std::endl;
    for (auto i : path)
        std::cout << i << std::endl;

    std::reverse(path.begin(), path.end());
}

void Cube::check_invariants()
{
    update_colors();
    solve(colors_by_s);
}

void Cube::set_def_col(const std::array<uint, 6> &def_col) noexcept
{
    std::copy(def_col.begin(), def_col.end(), default_colors.begin());
}

void Cube::set_size(const double size_)
{
    if (size_ <= 0)
        throw MyException("Size can't be negative");
    size = size_;
}

void Cube::make_shuffeled()
{
    if (shuff == true)
    {
        srand(std::time(NULL));
        for (auto i = 0; i < 15; i++)
            rot90(rand() % 6, 1);
    }
}

void Cube::update_colors() noexcept
{
    //верх
    for (int j = 2; j >= 0; j--)
        for (int i = 0; i < 3; i++)
        {
            colors_by_s[0][(2 - j) * 3 + i] = parts[i][j][2].get_color(0);
        }

    // слева
    for (int i = 2; i >= 0; i--)
        for (int k = 2; k >= 0; k--)
        {
            colors_by_s[1][(2 - i) * 3 + (2 - k)] = parts[0][k][i].get_color(4);
        }

    // спереди
    for (int k = 2; k >= 0; k--)
        for (int j = 0; j < 3; j++)
        {
            colors_by_s[2][(2 - k) * 3 + j] = parts[j][0][k].get_color(2);
        }

    // справа
    for (int i = 2; i >= 0; i--)
        for (int k = 0; k < 3; k++)
        {
            colors_by_s[3][(2 - i) * 3 + k] = parts[2][k][i].get_color(5);
        }

    // сзади
    for (int k = 2; k >= 0; k--)
        for (int j = 2; j >= 0; j--)
        {
            colors_by_s[4][(2 - k) * 3 + (2 - j)] = parts[j][2][k].get_color(3);
        }

    // низ
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < 3; i++)
        {
            colors_by_s[5][j * 3 + i] = parts[i][j][0].get_color(1);
        }
}