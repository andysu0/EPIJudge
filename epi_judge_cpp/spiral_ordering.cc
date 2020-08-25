#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
enum class Direction
{
  kLeft,
  kDown,
  kRight,
  kUp
};
struct Point
{
  int row;
  int col;
};
void spiralTraverse(Direction dir, const Point& topLeft, const Point& bottomRight, vector<int>& result, const vector<vector<int>>& mat)
{
  if (topLeft.row < 0 || topLeft.col < 0
      || bottomRight.row >= mat.size() || bottomRight.col >= mat[0].size())
  {
    return;
  }

  if (bottomRight.row < topLeft.row || bottomRight.col < topLeft.col)
  {
    return;
  }

  switch(dir)
  {
    case Direction::kLeft:
    {
      for (int i = topLeft.col; i <= bottomRight.col; ++i)
      {
        result.push_back(mat[topLeft.row][i]);
      }
      Point newTopLeft = topLeft;
      newTopLeft.row++;
      spiralTraverse(Direction::kDown, newTopLeft, bottomRight, result, mat);
      break;
    }
    case Direction::kDown:
    {
      for (int i = topLeft.row; i <= bottomRight.row; ++i)
      {
        result.push_back(mat[i][bottomRight.col]);
      }
      Point newBottomRight = bottomRight;
      newBottomRight.col--;
      spiralTraverse(Direction::kRight, topLeft, newBottomRight, result, mat);
      break;
    }
    case Direction::kRight:
    {
      for (int i = bottomRight.col; i >= topLeft.col; --i)
      {
        result.push_back(mat[bottomRight.row][i]);
      }
      Point newBottomRight = bottomRight;
      newBottomRight.row--;
      spiralTraverse(Direction::kUp, topLeft, newBottomRight, result, mat);
      break;
    }
    case Direction::kUp:
    {
      for (int i = bottomRight.row; i >= topLeft.row; --i)
      {
        result.push_back(mat[i][topLeft.col]);
      }
      Point newTopLeft = topLeft;
      newTopLeft.col++;
      spiralTraverse(Direction::kLeft, newTopLeft, bottomRight, result, mat);
      break;
    }
    default:
      break;
  }
}

vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix)
{
  if (square_matrix.empty())
  {
    return {};
  }

  vector<int> result;
  spiralTraverse(Direction::kLeft, Point{0, 0}, Point{static_cast<int>(square_matrix.size() - 1), static_cast<int>(square_matrix[0].size()-1)}, result, square_matrix);
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
