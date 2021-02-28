#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.

bool hasDupes(const vector<vector<int>>& grid, size_t rowStart, size_t rowEnd, size_t colStart, size_t colEnd)
{
    std::vector<int> validDigits(10);
    for (size_t i = rowStart; i <= rowEnd; ++i)
    {
        for (size_t j = colStart; j <= colEnd; ++j)
        {
            int num = grid[i][j];
            if (num == 0)
                continue;
 
            if (++validDigits[num] > 1)
                return false;
        }
    }

    return true;
}

bool IsValidSudoku(const vector<vector<int>>& grid) {
  
    size_t gridSize = grid.size();
    // Check rows
    for (size_t i = 0; i < gridSize; ++i)
    {
        if (!hasDupes(grid, i, i, 0, gridSize - 1))
            return false;
    }

    // Check cols
    for (size_t i = 0; i < gridSize; ++i)
    {
        if (!hasDupes(grid, 0, gridSize - 1, i, i))
            return false;
    }

    // Check local 3x3
    for (size_t i = 0; i < gridSize; i += 3)
    {
        for (size_t j = 0; j < gridSize; j += 3)
        {
            if (!hasDupes(grid, i, i + 2, j, j + 2))
                return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
