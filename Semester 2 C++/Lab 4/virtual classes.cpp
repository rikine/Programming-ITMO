#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "Figures.h"

inline void help() {
	std::cout << "Write 'Add' to add figure then write %Figure_name%(rectangle or circle)" << std::endl;
	std::cout << "Write 'ShowAll' to draw all figures" << std::endl;
	std::cout << "Write 'SortByMass' to sort objects by mass" << std::endl;
	std::cout << "Write 'SumSquare' to get sum of squares" << std::endl;
	std::cout << "Write 'sumPerimeter' to get sum of perimeters" << std::endl;
	std::cout << "Write 'SumSize' to get sum of size of all objects" << std::endl;
	std::cout << "Write 'massCenter' to get mass center, vector(x, y)" << std::endl;
	std::cout << "Write help to get help" << std::endl;
}

int main() {
	std::vector<IFigure*> figures;
	std::string s;

	help();
	while (std::cin >> s) {
		std::transform(s.begin(), s.end(), s.begin(), std::tolower);
		
		if (s == "add") {
			std::cin >> s;
			if (s == "rectangle")
				figures.push_back(new Rectangle());
			else if (s == "circle")
				figures.push_back(new Circle());
			else {
				std::cerr << "Figure is wrong. Try again" << std::endl;
				continue;
			}
			figures.back()->initFromDialog();
		}
		else if (s == "showall") {
			for (auto a : figures)
				a->draw();
		}
		else if (s == "sortbymass") {
			sort(figures.begin(), figures.end());
			std::cout << "Sorted" << std::endl;
		}
		else if (s == "sumsquare") {
			double sum = 0;
			for (auto a : figures)
				sum += a->square();
			std::cout << "Summery square = " << sum << std::endl;
		}
		else if (s == "sumperimeter") {
			double sum = 0;
			for (auto a : figures)
				sum += a->perimeter();
			std::cout << "Summery perimeter = " << sum << std::endl;
		}
		else if (s == "sumsize") {
			double sum = 0;
			for (auto a : figures)
				sum += a->size();
			std::cout << "Summery size = " << sum << std::endl;
		}
		else if (s == "masscenter") {
			Vector2D center{ 0, 0 };
			double sum = 0;
			for (auto& x : figures) {
				center.x += x->position().x * x->mass();
				center.y += x->position().y * x->mass();
				sum += x->mass();
			}
			center.x /= sum;
			center.y /= sum;
			std::cout << "Center mass = (" << center.x << ", " << center.y << ")" << std::endl;
		}
		else if (s == "help")
			help();
		else if (s == "clear")
			for (int i = 0; i < 30; i++)
				std::cout << std::endl;
		else {
			std::cerr << "Wrong command. Try again";
		}
	}
	return 0;
}
