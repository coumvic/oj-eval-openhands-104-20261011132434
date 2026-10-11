#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// Structure to represent a position in the grid
struct Position {
    int row, col, dist;
    
    Position(int r, int c, int d) : row(r), col(c), dist(d) {}
};

// BFS to find shortest distances from a starting point to all other points
vector<vector<int>> bfs(const vector<vector<int>>& grid, int startRow, int startCol, int m, int n) {
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    queue<Position> q;
    
    // Start from the initial position
    dist[startRow][startCol] = 0;
    q.push(Position(startRow, startCol, 0));
    
    // Directions for moving: up, down, left, right
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    
    while (!q.empty()) {
        Position curr = q.front();
        q.pop();
        
        int row = curr.row;
        int col = curr.col;
        int d = curr.dist;
        
        // If we've found a longer path, skip
        if (d > dist[row][col]) {
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
            
            // Calculate new distance
            int newDist = d + 1;
            
            // Update distance if we found a shorter path
            if (newDist < dist[newRow][newCol]) {
                dist[newRow][newCol] = newDist;
                q.push(Position(newRow, newCol, newDist));
            }
        }
    }
    
    return dist;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    // Read the grid
    // Note: The input has m rows and n columns
    vector<vector<int>> grid(m, vector<int>(n));
    int startRow = -1, startCol = -1;
    int homeRow = -1, homeCol = -1;
    vector<pair<int, int>> umbrellaStores;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 2) {
                startRow = i;
                startCol = j;
            } else if (grid[i][j] == 3) {
                homeRow = i;
                homeCol = j;
            } else if (grid[i][j] == 4) {
                umbrellaStores.push_back({i, j});
            }
        }
    }
    
    // Find shortest distances from start to all points
    vector<vector<int>> distFromStart = bfs(grid, startRow, startCol, m, n);
    
    // Find shortest distances from home to all points
    vector<vector<int>> distFromHome = bfs(grid, homeRow, homeCol, m, n);
    
    // Find the minimum distance that goes through an umbrella store
    int minDist = INT_MAX;
    
    for (auto& store : umbrellaStores) {
        int storeRow = store.first;
        int storeCol = store.second;
        
        // Check if we can reach the umbrella store from start and home from umbrella store
        if (distFromStart[storeRow][storeCol] != INT_MAX && distFromHome[storeRow][storeCol] != INT_MAX) {
            int totalDist = distFromStart[storeRow][storeCol] + distFromHome[storeRow][storeCol];
            minDist = min(minDist, totalDist);
        }
    }
    
    // Output the result
    if (minDist == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << minDist << endl;
    }
    
    return 0;
}