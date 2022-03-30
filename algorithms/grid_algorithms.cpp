#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <utility>

// movement vectors
const int dRow[4] = {0, 1, 0, -1};
const int dCol[4] = {-1, 0, 1, 0};

typedef std::pair<int, int> Pair;

static void printGrid(std::vector<std::vector<int>> grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << "\n";
    }
}
bool isValid(std::vector<std::vector<bool>> &visited, int row, int col)
{
    if (row < 0 || col < 0 || col >= visited[0].size() || row >= visited.size() || visited[row][col])
    {
        return 0;
    }
    return 1;
}

/*Note: no error handling has been done for starting points*/
void DFSGrid(std::vector<std::vector<int>> &grid, int startR = 0, int startC = 0)
{
    // check for valid grid size
    int height = grid.size();
    if (!height)
    {
        return;
    }

    int length = grid[0].size();

    // initialize grid with all zeros
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(length, 0));

    // initialize a stack to store future moves
    std::stack<Pair> stack;

    stack.push({startR, startC});

    while (!stack.empty())
    {
        Pair current = stack.top();
        stack.pop();

        int row = current.first;
        int col = current.second;

        // check if current cell is valid
        if (!isValid(visited, row, col))
        {
            continue;
        }

        // mark current cell as visited
        visited[row][col] = 1;

        // uncomment to see the order of traversal
        // std::cout << grid[row][col] << " ";

        // push all adjacent cells
        for (int i = 0; i < 4; i++)
        {
            stack.push({row + dRow[i], col + dCol[i]});
        }
    }
}

/*Note: no error handling has been done for starting points*/
std::vector<std::vector<int>> BFSGrid(std::vector<std::vector<int>> &grid, int startR = 0, int startC = 0)
{
    std::vector<std::vector<int>> dist;

    int height = grid.size();
    if (!height)
    {
        return dist;
    }
    int length = grid[0].size();

    // Initialize grid to check if a cell is visited
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(length, 0));
    // Initialize grid to store distances to different cells
    dist = std::vector<std::vector<int>>(height, std::vector<int>(length, 0));

    dist[startR][startC] = 0;
    visited[startR][startC] = 1;

    // pairs hold coordinates of each cell
    std::queue<Pair> fringe;
    fringe.push({startR, startC});

    while (!fringe.empty())
    {
        Pair current = fringe.front();
        fringe.pop();

        int row = current.first;
        int col = current.second;

        // uncomment to see the order of traversal
        // std::cout << grid[row][col] << " ";

        // since we can move up, down, left and right
        for (int i = 0; i < 4; i++)
        {
            int adjR = row + dRow[i];
            int adjC = col + dCol[i];
            // check if next cell is valid and visited
            if (isValid(visited, adjR, adjC))
            {
                visited[adjR][adjC] = 1;
                dist[adjR][adjC] = dist[row][col] + 1;

                fringe.push({adjR, adjC});
            }
        }
    }

    return dist;
}

/*Note: I'll assume the data received is always correct, just to keep things simple*/
std::vector<std::vector<int>> getMazePath(std::vector<std::vector<Pair>> &parentGrid, int startR, int startC)
{
    std::vector<std::vector<int>> pathGrid(parentGrid.size(), std::vector<int>(parentGrid[0].size(), 0));
    int i = startR;
    int j = startC;

    // backtrack until we reach the beggining
    while (i != 0 || j != 0)
    {
        Pair current = parentGrid[i][j];

        pathGrid[i][j] = 1;
        i = current.first;
        j = current.second;
    }

    // add starting point to path
    pathGrid[i][j] = 1;

    return pathGrid;
}
bool solveMaze(std::vector<std::vector<char>> &grid)
{
    // parent Grid to backTrack path
    std::vector<std::vector<Pair>> parentGrid(grid.size(), std::vector<Pair>(grid[0].size(), {0, 0}));
    // path grid to display shortest path
    std::vector<std::vector<int>> path(grid.size(), std::vector<int>(grid[0].size(), 0));
    // grid to keep track of visited cells
    std::vector<std::vector<bool>> visited(grid.size(), std::vector<bool>(grid[0].size(), 0));

    // add starting point to path
    path[0][0] = 1;
    parentGrid[0][0] = {0, 0};
    std::queue<Pair> fringe;
    fringe.push({0, 0});

    while (!fringe.empty())
    {
        Pair current = fringe.front();
        fringe.pop();
        int row = current.first;
        int col = current.second;

        visited[row][col] = 1;

        if (grid[row][col] == 'E')
        {
            // call getMazePath to build the shortest path
            // using the data stored in parentGrid
            path = getMazePath(parentGrid, row, col);
            printGrid(path);
            return true;
        }

        for (int i = 0; i < 4; i++)
        {
            int adjR = row + dRow[i];
            int adjC = col + dCol[i];
            if (isValid(visited, adjR, adjC) && grid[adjR][adjC] != '#')
            {
                // mark the cell we came from
                // so we can backtrack to it later
                parentGrid[adjR][adjC] = {row, col};

                // push next cell to explore
                fringe.push({adjR, adjC});
            }
        }
    }
    return false;
}

int main()
{
    std::vector<std::vector<int>> grid = {{-1, -2, -3, -4, -5, -6},
                                          {0, 9, 8, 7, 6, 5},
                                          {1, 2, 3, 4, 15, 16},
                                          {-11, -22, -33, -44, -55, -66},
                                          {10, 99, 88, 77, 66, 55},
                                          {11, 22, 33, 44, 155, 166}};

    std::vector<std::vector<int>> grid1 = {{0, 1, 2},
                                           {3, 4, 5},
                                           {6, 7, 8}};

    std::vector<std::vector<int>> dist = BFSGrid(grid, 4, 3);

    // Maze problem
    // S - start position, E - end position
    // find minimal steps required to reach 'E' starting from 'S'
    // '#' are forbidded areas '.' are areas you can walk on
    std::vector<std::vector<char>> maze = {{'S', '.', '.', '#', '.', '#'},
                                           {'#', '#', '.', '#', '.', '.'},
                                           {'.', '.', '.', '.', '.', '#'},
                                           {'#', '.', '#', '#', '.', '.'},
                                           {'#', '.', '.', '#', '#', '.'},
                                           {'.', '#', 'E', '.', '.', '.'}};

    std::cout << solveMaze(maze);
}