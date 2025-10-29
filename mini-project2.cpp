#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>   
#include <iomanip>

using namespace std;

struct Point {
    int x, y;

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }
};


struct PointHasher {
    size_t operator()(const Point& p) const {
        return p.x * 31 + p.y;
    }
};

struct Node {
    Point pt;
    int f, g, h;
    Point parent;

    bool operator>(const Node& other) const {
        return f > other.f;
    }
};


bool isValid(int x, int y, int ROW, int COL) {
    return (x >= 0) && (x < ROW) && (y >= 0) && (y < COL);
}


bool isUnBlocked(const vector<vector<int>>& grid, int x, int y) {
    return grid[x][y] == 1;
}


bool isDestination(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}


int calculateH(int x, int y, Point dest) {
    return abs(x - dest.x) + abs(y - dest.y);
}


vector<Point> tracePath(unordered_map<Point, Point, PointHasher>& parentMap, Point dest) {
    vector<Point> path;
    Point current = dest;

    while (parentMap.find(current) != parentMap.end()) {
        path.push_back(current);
        current = parentMap[current];
    }
    path.push_back(current);  

    reverse(path.begin(), path.end());
    return path;
}


void printGridWithPath(const vector<vector<int>>& grid, const vector<Point>& path) {
    vector<vector<char>> display(grid.size(), vector<char>(grid[0].size(), ' '));

    
    for (int i = 0; i < (int)grid.size(); i++) {
        for (int j = 0; j < (int)grid[0].size(); j++) {
            display[i][j] = (grid[i][j] == 1) ? '.' : '#';
        }
    }

  
    for (const auto& p : path) {
        display[p.x][p.y] = '*';
    }

    cout << "\nGrid with path ('.' = free, '#' = blocked, '*' = path):\n";
    for (int i = 0; i < (int)display.size(); i++) {
        for (int j = 0; j < (int)display[0].size(); j++) {
            cout << display[i][j] << " ";
        }
        cout << "\n";
    }
}

void aStarSearch(const vector<vector<int>>& grid, Point start, Point dest) {
    int ROW = grid.size();
    int COL = grid[0].size();

    if (!isValid(start.x, start.y, ROW, COL) || !isValid(dest.x, dest.y, ROW, COL)) {
        cout << "Invalid start or destination coordinates.\n";
        return;
    }

    if (!isUnBlocked(grid, start.x, start.y) || !isUnBlocked(grid, dest.x, dest.y)) {
        cout << "Start or destination cell is blocked.\n";
        return;
    }

    if (isDestination(start, dest)) {
        cout << "Already at the destination.\n";
        return;
    }

    vector<vector<bool>> closedList(ROW, vector<bool>(COL, false));
    unordered_map<Point, Node, PointHasher> allNodes;
    unordered_map<Point, Point, PointHasher> parentMap;
    priority_queue<Node, vector<Node>, greater<Node>> openList;

    Node startNode{start, 0, 0, calculateH(start.x, start.y, dest), start};
    openList.push(startNode);
    allNodes[start] = startNode;

    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    bool foundDest = false;

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        Point pt = current.pt;
        closedList[pt.x][pt.y] = true;

        if (isDestination(pt, dest)) {
            foundDest = true;
            vector<Point> path = tracePath(parentMap, pt);

            cout << "\nPath found! Steps: " << path.size() << "\n";
            cout << "Path (start to destination):\n";
            for (const auto& p : path) {
                cout << "(" << p.x << "," << p.y << ") ";
            }
            cout << "\n";

            printGridWithPath(grid, path);
            return;
        }

        for (int i = 0; i < 4; i++) {
            int nx = pt.x + dx[i];
            int ny = pt.y + dy[i];

            if (isValid(nx, ny, ROW, COL) && isUnBlocked(grid, nx, ny) && !closedList[nx][ny]) {
                int gNew = current.g + 1;
                int hNew = calculateH(nx, ny, dest);
                int fNew = gNew + hNew;

                Point neighbor{nx, ny};

                if (allNodes.find(neighbor) == allNodes.end() || allNodes[neighbor].f > fNew) {
                    Node neighborNode{neighbor, fNew, gNew, hNew, pt};
                    openList.push(neighborNode);
                    allNodes[neighbor] = neighborNode;
                    parentMap[neighbor] = pt;
                }
            }
        }
    }

    if (!foundDest) {
        cout << "Failed to find the destination cell.\n";
    }
}

int main() {
    vector<vector<int>> grid = {
        { 1, 1, 1, 1, 1 },
        { 1, 0, 0, 1, 1 },
        { 1, 1, 1, 0, 1 },
        { 0, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1 }
    };

    Point start{0, 0};
    Point dest{4, 4};

    cout << "Starting A* Search from (" << start.x << "," << start.y << ") "
         << "to (" << dest.x << "," << dest.y << ").\n";

    aStarSearch(grid, start, dest);

    return 0;
}
