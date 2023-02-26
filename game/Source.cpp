#include <iostream>
#include <conio.h>
#include <vector>
#include <algorithm>

using namespace std;

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;

const int MAX_TREES = 10; // Maximum number of trees on the map
int numTrees = 0; // Current number of trees on the map

char map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "################",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "#              #",
    "################"
};

struct Tree {
    int x;
    int y;
};

vector<string> inventory;
vector<pair<int, int>> trees = { {3, 3}, {5, 7}, {8, 4}, {12, 10} };

void drawMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            cout << map[y][x];
        }
        cout << endl;
    }

    cout << endl << "Inventory: ";
    for (string item : inventory) {
        cout << item << " ";
    }
    cout << endl;
}

void clearPlayer(int x, int y) {
    map[y][x] = ' ';
}

void addTree() {
    int x, y;
    do {
        // Generate random coordinates for the tree
        x = rand() % (MAP_WIDTH - 2) + 1;
        y = rand() % (MAP_HEIGHT - 2) + 1;
    } while (map[y][x] != ' '); // Keep generating coordinates until an empty space is found

    map[y][x] = 'T'; // Add the tree to the map
    numTrees++; // Increment the number of trees
}


bool isTree(int x, int y) {
    for (auto tree : trees) {
        if (tree.first == x && tree.second == y) {
            return true;
        }
    }
    return false;
}

void clearTree(int x, int y) {
    for (int i = 0; i < trees.size(); i++) {
        if (trees[i].first == x && trees[i].second == y) {
            trees.erase(trees.begin() + i);
            break;
        }
    }
}

void breakTree(int x, int y) {
    map[y][x] = ' ';
    inventory.push_back("Wood");
}

bool hasTree = false;

int main() {
    char input;
    int playerX = 1;
    int playerY = 1;

    // Add some initial trees to the map
    while (numTrees < MAX_TREES) {
        addTree();
    }

    while (true) {
        // Отображение карты
        system("cls"); // Очистка консоли
        drawMap();

        // Управление игроком
        input = _getch();

        switch (input) {
        case 'w':
            if (map[playerY - 1][playerX] == ' ') {
                clearPlayer(playerX, playerY);
                playerY--;
            }
            else if (map[playerY - 1][playerX] == 'T') {
                breakTree(playerX, playerY - 1);
            }
            break;
        case 's':
            if (map[playerY + 1][playerX] == ' ') {
                clearPlayer(playerX, playerY);
                playerY++;
            }
            else if (map[playerY + 1][playerX] == 'T') {
                breakTree(playerX, playerY + 1);
            }
            break;
        case 'a':
            if (map[playerY][playerX - 1] == ' ') {
                clearPlayer(playerX, playerY);
                playerX--;
            }
            else if (map[playerY][playerX - 1] == 'T') {
                breakTree(playerX - 1, playerY);
            }
            break;
        case 'd':
            if (map[playerY][playerX + 1] == ' ') {
                clearPlayer(playerX, playerY);
                playerX++;
            }
            else if (map[playerY][playerX + 1] == 'T') {
                breakTree(playerX + 1, playerY);
            }
            break;
        case 'q':
            return 0; // Выход из программы
        case 'f':
            void placeTree(int playerX, int playerY, bool& hasTree, int& inventory); {
                if (hasTree) {
                    int targetX = playerX, targetY = playerY;
                    char key = _getch();
                    if (key == 'w' && map[playerY - 1][playerX] == ' ') {
                        targetY--;
                    }
                    else if (key == 's' && map[playerY + 1][playerX] == ' ') {
                        targetY++;
                    }
                    else if (key == 'a' && map[playerY][playerX - 1] == ' ') {
                        targetX--;
                    }
                    else if (key == 'd' && map[playerY][playerX + 1] == ' ') {
                        targetX++;
                    }
                    else {
                        return; // Exit if invalid input or target location
                    }

                    // Place tree in front of player
                    if (inventory > 0) {
                        hasTree = false;
                        inventory--;
                        map[targetY][targetX] = 'T';
                    }
                }
            }
        default:
            break;
        }

        // Перемещение игрока на карту
        map[playerY][playerX] = 'O';
    }

    return 0;
}




