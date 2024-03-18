#include <iostream>
#include <vector>

char patternCheck(char ch, const std::vector<std::vector<char>>& charVector) {
    bool isHorizontal, isVertical, isDiagonalLR, isDiagonalRL;
    isHorizontal = isVertical = isDiagonalLR = isDiagonalRL = true;
    int horizontalCount = 0, verticalCount[4] = {0}, diagLRCount = 0, diagRLCount = 0;
    int totalCount = 0;
    
    for (int i = 0; i < 4; ++i) {
        isHorizontal = true;
        for (int j = 0; j < 4; ++j) {
            // Check horizontal
            if (charVector[i][j] != ch) isHorizontal = false;
            else horizontalCount++;

            // Check vertical
            if (charVector[j][i] == ch) verticalCount[i]++;
            
            // Check diagonal left to right
            if (i == j && charVector[i][j] != ch) isDiagonalLR = false;
            if (i == j && charVector[i][j] == ch) diagLRCount++;
            
            // Check diagonal right to left
            if (i + j == 3 && charVector[i][j] != ch) isDiagonalRL = false;
            if (i + j == 3 && charVector[i][j] == ch) diagRLCount++;
        }
        if (isHorizontal && horizontalCount == 4) return '-';
    }

    for (int i = 0; i < 4; ++i) {
        if (verticalCount[i] == 4) return '|';
    }

    if (isDiagonalLR && diagLRCount == 4) return '\\';
    if (isDiagonalRL && diagRLCount == 4) return '/';

    totalCount = horizontalCount + verticalCount[0] + verticalCount[1] + verticalCount[2] + verticalCount[3] + diagLRCount + diagRLCount;
    if (totalCount != 4) return 'n';
    
    return 'n'; // If none of the patterns match and character count is exactly 4, return 'n'
}

int main() {
    // Example usage:
    std::vector<std::vector<char>> charVector = {
        {'x', 'o', 'x', 'x'},
        {'o', 'x', 'o', 'x'},
        {'x', 'o', 'o', 'x'},
        {'o', 'x', 'o', 'x'}
    };

    char result = patternCheck('x', charVector);
    std::cout << "Pattern is: " << result << std::endl;

    return 0;
}
