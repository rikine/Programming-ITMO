#pragma once
#include <array>
#include <vector>
#include <string>

typedef unsigned char uchar;
typedef unsigned int uint;

/**
 * @struct Center
 * @brief Central sticker of a face.
 *
 */
struct Center
{
  char center;
};

/**
 * @struct Edge
 * @brief Piece with two stickers.
 *
 */
struct Edge
{
  char up, down;
};

/**
 * @struct Corner
 * @brief Piece with three stickers, the orientation doesn't change.
 *
 */
struct Corner
{
  char up, left, right;
};

/**
 * @class Class to interact with an instance of Rubik's Cube
 *
 */
class Rubik
{
private:
  /**
       * @brief Centers of rubik's cube
       * \note Order of centers: top(0), frontal(1), right(2), back(3), left(4), bottom(5)
       *
       */
  Center center[6];

  /**
       * @brief Edges of rubik's cube
       * \note Order of edges:
       *  top(0, 1, 2, 3) and bottom(4, 5, 6, 7), central ring(8, 9, 10, 11)
       *
       */
  Edge edge[12];

  /**
       * @brief Corners of rubik's cube
       * \note Order of corners:
       *  top(0, 1, 2, 3) and bottom(4, 5, 6, 7)
       *
       */
  Corner corner[8];

  // Auxiliary functions
  /**
        * @brief Develop each movement in natural language
        * @param std::vector<char>& solution Movements to explain, part of the real solution
        * @param const unsigned int& movement First movement to explain
        * @return void
        * @pre char of solution are limited in class
        * @pre movement < solution.size()
        * @see Movements
        *
        */
  int equivalentNumber(const char &c) const;

  /**
        * @brief Look for specific edge
        * @param const char& ar
        * @param const char& ab
        * @return int
        * @retval [0, 11]
        * @pre ar && ab valid colours with centers not opposite
        * @see Edge
        *
        */
  int searchEdge(const char &ar, const char &ab) const;

  /**
        * @brief Look for specific specific corner
        * @param const char& a
        * @param const char& iz
        * @param const char& de
        * @return int
        * @retval [0, 7]
        * @pre a, iz, de valid colours with center not opposite
        * @see Corner
        *
        */
  int searchCorner(const char &a, const char &iz, const char &de) const;

  /**
        * @brief Execution of sec.size() movements in std::string sec
        * @param std::string sec std::string with movements
        * @param std::vector<char>& solution where we will append movements from sec
        * @return void
        * @pre Valid chars in std::string
        * @see explainMovements()
        *
        */
  void sequence(const std::string &sec, std::vector<uchar> &solution);

  // Parts of the solution
  /**
        * @brief It complete top face (white)
        * @param std::vector<char>& solution will store the solution
        * @param std::vector<char>& solution
        * @return void
        * @pre solution.size() == 0, it will be deleted
        *
        */
  void firstStep(std::vector<uchar> &solution);

  /**
        * @brief First part of top face
        * @param std::vector<char>& solution
        * @return void
        * @see firstStep()
        *
        */
  void whiteCross(std::vector<uchar> &solution);

  /**
        * @brief First three corners of top face
        * @param std::vector<char>& solution
        * @return void
        * @pre firstStep()
        * @see firstStep()
        *
        */
  void cornersFirstStep(std::vector<uchar> &solution);

  /**
        * @brief Central ring of rubik's cube
        * @param std::vector<char>& solution
        * @return void
        * @pre firstStep()
        * @see thirdStep()
        *
        */
  void secondStep(std::vector<uchar> &solution);

  /**
        * @brief Last part of solution
        * @param std::vector<char>& solution
        * @return void
        * @pre firstStep()
        * @pre secondStep()
        *
        */
  void thirdStep(std::vector<uchar> &solution);

  /**
        * @brief First part of bottom face
        * @param std::vector<char>& solution
        * @return void
        * @see thirdStep()
        *
        */
  void yellowCross(std::vector<uchar> &solution);

  /**
        * @brief Last four corners
        * @param std::vector<char>& solution
        * @return void
        * @pre yellowCross()
        *
        */
  void finalCorners(std::vector<uchar> &solution);

  /**
        * @brief It moves corner to their position
        * @param std::vector<char>& solution
        * @return void
        * @see finalCorners()
        *
        */
  void permutationFinalCorners(std::vector<uchar> &solution);

  /**
        * @brief Last step
        * @param std::vector<char>& solution
        * @return void
        * @pre permutationFinalCorners()
        * @see
        *
        */
  void positionFinalCorners(std::vector<uchar> &solution);

public:
  /**
        * @brief Constructor without arguments
        * @see validRubik()
        *
        */
  Rubik();

  /**
        * @brief Constructor with an instance of Rubik class
        * @param const Rubik& rubik
        * @pre *this != &rubik
        *
        */
  Rubik(const Rubik &rubik);

  /**
        * @brief Check if our rubik's cube is solved
        * @return bool
        * @see validRubik()
        *
        */
  bool isSolved() const;

  /**
        * @brief Check if there are logic errors in colour distribution
        * @return int
        * @retval -1 wrong centers
        * @retval -2 wrong edges
        * @retval -3 wrong corners
        *
        */
  int logicErrors() const;

  // Movements
  /**
        * @brief Move right side backward.
        * @param std::vector<char>& solution
        * @return void
        * @see r()
        *
        */
  void R(std::vector<uchar> &solution);

  /**
        * @brief Move right side backward two times
        * @param std::vector<char>& solution
        * @return void
        *
        */
  void R2(std::vector<uchar> &solution);

  /**
        * @brief Move right side to you
        * @param std::vector<char>& solution
        * @return
        * @see R()
        *
        */
  void r(std::vector<uchar> &solution);

  /**
        * @brief Move left side to you
        * @param std::vector<char>& solution
        * @return void
        * @see l()
        *
        */
  void L(std::vector<uchar> &solution);

  /**
        * @brief  Move left side to you two times
        * @param std::vector<char>& solution
        * @return void
        *
        */
  void L2(std::vector<uchar> &solution);

  /**
        * @brief Move left side backward
        * @param std::vector<char>& solution
        * @return void
        * @see L()
        *
        */
  void l(std::vector<uchar> &solution);

  /**
        * @brief Move down side right
        * @param std::vector<char>& solution
        * @return void
        * @see d()
        *
        */
  void D(std::vector<uchar> &solution);

  /**
        * @brief Move down side right two times
        * @param std::vector<char>& solution
        * @return void
        *
        */
  void D2(std::vector<uchar> &solution);

  /**
        * @brief Move down side left
        * @param std::vector<char>& solution
        * @return void
        * @see D()
        *
        */
  void d(std::vector<uchar> &solution);

  /**
        * @brief Move top side left
        * @param std::vector<char>& solution
        * @return void
        * @see u()
        *
        */
  void U(std::vector<uchar> &solution);

  /**
        * @brief Move top side left two times
        * @param std::vector<char>& solution
        * @return void
        *
        */
  void U2(std::vector<uchar> &solution);

  /**
        * @brief Move top side right
        * @param std::vector<char>& solution
        * @return void
        * @see U()
        *
        */
  void u(std::vector<uchar> &solution);

  /**
        * @brief Move frontal side in clockwise
        * @param std::vector<char>& solution
        * @return void
        * @see f()
        *
        */
  void F(std::vector<uchar> &solution);

  /**
        * @brief Move frontal side in clockwise two times
        * @param std::vector<char>& solution
        * @return void
        *
        */
  void F2(std::vector<uchar> &solution);

  /**
        * @brief Move frontal side, not in clockwise
        * @param std::vector<char>& solution
        * @return void
        * @see F()
        *
        */
  void f(std::vector<uchar> &solution);

  /**
        * @brief Move back side left
        * @param std::vector<char>& solution
        * @return void
        * @see b()
        *
        */
  void B(std::vector<uchar> &solution);

  /**
        * @brief Move back side left two times
        * @param std::vector<char>& solution
        * @return void
        *
        */
  void B2(std::vector<uchar> &solution);

  /**
        * @brief Move back side right
        * @param std::vector<char>& solution
        * @return void
        * @see B()
        *
        */
  void b(std::vector<uchar> &solution);

  /**
        * @brief It solves rubik cube with private auxiliary functions
        * @param std::vector<char>& solution
        * @return void
        * @pre solution empty, it's modified
        * @see solveStepByStep()
        *
        */
  void solve(std::vector<uchar> &solution, const char &method = 'B');

  // Input && output
  /**
        * @brief Read specific sticker from rubik's cube
        * \note Rubik is modified
        * @param char& c, is modified
        * @param std::istream& is=cin
        * @return void
        * @pre char& c is a sticker of the instance
        * @see readRubik()
        *
        */
  void readSticker(char &c, const uchar is);

  /**
        * @brief Read rubik's cube
        * \note It's modified
        * @param std::istream& is=cin
        * @return void
        * @pre Readable istream with correct rubik's format
        * @see readSticker()
        *
        */
  void readRubik(std::array<std::array<uchar, 9>, 6> &is);

  // Getter
  /**
        * @brief Getter of center piece
        * @param const int& position
        * @return Center
        * @pre Valid position
        * @see Center
        *
        */
  Center getCenter(const int &position) const;

  /**
        * @brief Getter of specific edge
        * @param const int& position
        * @return Edge
        * @pre Valid position
        * @see Edge
        *
        */
  Edge getEdge(const int &position) const;

  /**
        * @brief Getter of specific corner
        * @param const int& position
        * @return Corner
        * @pre Valid position
        * @see Corner
        *
        */
  Corner getCorner(const int &position) const;

  // Operators
  /**
        * @brief Assigment operator
        * \note It's modified
        * @param const Rubik& r
        * @return Rubik&
        * @retval *this
        * @pre r different rubik's cube
        * @see operator ==
        *
        */
  Rubik &operator=(const Rubik &r);

  /**
        * @brief Operator ==
        * @param const Rubik& r
        * @return bool
        * @pre r different rubik's cube
        *
        */
  bool operator==(const Rubik &rubik);

  /**
        * @brief Operator !=
        * @param const Rubik& r
        * @return bool
        * @pre r different rubik's cube
        *
        */
  bool operator!=(const Rubik &rubik);
};

/**
 * @brief Ostream in readable format
 * @param std::ostream& os
 * @param const Rubik& rubik
 * @return std::ostream&
 *
 */
std::ostream &operator<<(std::ostream &os, const Rubik &rubik);

/**
 * @brief Istream of a rubik's cube in readable format
 * @param std::istraem& is
 * @param Rubik& rubik, it's modified
 * @return std::istream&
 *
 */
std::istream &operator>>(std::istream &is, Rubik &rubik);