#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Structure to represent a position in the grid with umbrella state
struct State {
    int row, col, hasUmbrella, dist;
    
    State(int r, int c, int umbrella, int d) : row(r), col(c), hasUmbrella(umbrella), dist(d) {}
};

int main() {
    int n, m;
    cin >> n >> m;
    
    // Read the grid
    // Note: The input has m rows and n columns
    vector<vector<int>> grid(m, vector<int>(n));
    int startRow = -1, startCol = -1;
    int homeRow = -1, homeCol = -1;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                startRow = i;
                startCol = j;
            } else if (grid[i][j] == 3) {
                homeRow = i;
                homeCol = j;
            }
        }
    }
    
    // Directions for moving: up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    // BFS to find shortest path from start to umbrella store to home
    // State: (row, col, has_umbrella)
    // has_umbrella: 0 = haven't visited umbrella store, 1 = have visited umbrella store
    vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(2, INT_MAX)));
    queue<State> q;
    
    // Start from the initial position without an umbrella
    dist[startRow][startCol][0] = 0;
    q.push(State(startRow, startCol, 0, 0));
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        int row = curr.row;
        int col = curr.col;
        int hasUmbrella = curr.hasUmbrella;
        int d = curr.dist;
        
        // If we've found a longer path, skip
        if (d > dist[row][col][hasUmbrella]) {
            continue;
        }
        
        // Explore all four directions
        for (auto& dir : directions) {
            int newRow = row + dir.first;
            int newCol = col + dir.second;
            
            // Check bounds
            if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n) {
                continue;
            }
            
            // Check if the building is under construction (cannot pass)
            if (grid[newRow][newCol] == 1) {
                continue;
            }
            
            // Determine if we have an umbrella at the new position
            int newHasUmbrella = hasUmbrella;
            
            // If the new position is an umbrella store, we get an umbrella
            if (grid[newRow][newCol] == 4) {
                newHasUmbrella = 1;
            }
            
            // Calculate new distance
            int newDist = d + 1;
            
            // Update distance if we found a shorter path
            if (newDist < dist[newRow][newCol][newHasUmbrella]) {
                dist[newRow][newCol][newHasUmbrella] = newDist;
                q.push(State(newRow, newCol, newHasUmbrella, newDist));
            }
        }
    }
    
    // Output the shortest distance to reach home with an umbrella
    // If no path exists, output -1 (though the problem guarantees a solution exists)
    if (dist[homeRow][homeCol][1] == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << dist[homeRow][homeCol][1] << endl;
    }
    
    return 0;
}