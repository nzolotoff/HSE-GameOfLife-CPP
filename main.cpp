#include <iostream>

#define N 10
#define M 10

bool** createGrid(int n, int m)
{
    bool** grid = new bool*[n];
    for (int i = 0; i < n; i++)
        grid[i] = new bool[m];
    return grid;
}


void displayGrid(bool** grid, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 1)
                std::cout << 'X';
            else
                std::cout << '.';
        }
        std::cout << std::endl;
    }
    std::cout << "##########\n";
}


void releaseGrid(bool** grid, int n)
{
    for (int i = 0; i < n; i++)
        delete[] grid[i];
    delete[] grid;
}


int countAliveNeighbours(bool** grid, int k, int l)
{
    int aliveNeighbours = 0;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            aliveNeighbours += grid[k + i][l + j];
    // The cell needs to be subtracted from it's neighbours as it was counted before
    aliveNeighbours -= grid[k][l];
    return aliveNeighbours;
}


bool** nextGeneration(bool** grid, int n, int m)
{
    bool** next = createGrid(n, m);

    // Loop through every cell
    for (int k = 1; k < n - 1; k++) {
        for (int l = 1; l < m - 1; l++) {
            // finding count of neighbours that are alive
            int aliveNeighbours = countAliveNeighbours(grid, k, l);

            // Implementing the Rules of Life

            // Cell is lonely and dies
            if ((grid[k][l] == 1) && (aliveNeighbours < 2))
                next[k][l] = 0;

                // Cell dies due to over population
            else if ((grid[k][l] == 1) && (aliveNeighbours > 3))
                next[k][l] = 0;

                // A new cell is born
            else if ((grid[k][l] == 0) && (aliveNeighbours == 3))
                next[k][l] = 1;

                // Remains the same
            else
                next[k][l] = grid[k][l];
        }
    }
    return next;
}


bool checksTwoGridsForDifferences(bool** prevGrid, bool** nextGrid, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (prevGrid[i][j] != nextGrid[i][j]) {
                return true;
            }
        }
    }
    return false;
}


void fillGrid(bool** grid, int n, int m)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            grid[i][j] = 0;
        }
    }
    grid[1][3] = 1;
    grid[1][4] = 1;
    grid[2][4] = 1;
    grid[5][3] = 1;
    grid[5][4] = 1;
    grid[6][2] = 1;
    grid[6][3] = 1;
    grid[7][5] = 1;
    grid[8][4] = 1;
}


int main()
{
    bool** prevGrid = createGrid(N, M); // create starting grid
    fillGrid(prevGrid, N, M); // fill starting grid
    std::cout << "Starting grid:\n";
    displayGrid(prevGrid, N, M); // display starting grid

    bool** nextGrid = nextGeneration(prevGrid, N, M); //generate next grid
    while (checksTwoGridsForDifferences(prevGrid, nextGrid, N, M)) {
        displayGrid(nextGrid, N, M);
        releaseGrid(prevGrid, N);
        prevGrid = nextGrid;
        nextGrid = nextGeneration(prevGrid, N, M);
    }

    releaseGrid(nextGrid, N);
    releaseGrid(prevGrid, N);
    return 0;
}