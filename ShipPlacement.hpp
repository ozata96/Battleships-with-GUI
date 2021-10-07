#ifndef ShipPlacement_HPP
#define ShipPlacement_HPP

#include <iostream>
#include <vector>

using namespace std;

class ShipPlacement
{
private:
    // Friendly Ship Placement


    // Enemy Ship Placement
    bool enemyFlagShipPlaced = false;
    bool enemyDestroyerShipPlaced = false;
    bool enemyMinorShipPlaced = false;
    bool enemyRadarShipPlaced = false;

    void ClearGrid(vector<string> &grid, vector<int> targetCoordinates);

    // Friendly Ship Functions
    bool CheckString(string input);
    int GetNumberDeployable(char shipType);
    bool areValidCoordinates(int numShipBlocks, int rowStart, int colStart, int rowEnd, int colEnd);
    int convertRowForMainGrid(int row);
    int convertColForMainGrid(int col);
    void CreateShip(int numDeployed);

    // Enemy Ship Functions
    void RandomEnemyShipPlacement(int shipBlocks, bool enemyShipType);
    int RandomNumberGenerator(int min, int max);

public:
    bool friendlyFlagShipPlaced = false;
    bool friendlyDestroyerShipPlaced = false;
    bool friendlyMinorShipPlaced = false;
    bool friendlyRadarShipPlaced = false;

    ShipPlacement();
    ~ShipPlacement();

    // Logic Grids
    vector<string> friendlyGrid;
    vector<string> enemyGrid;

    // functions
    void FriendlyGridIntake(string input, vector<string> &grid);
};

#endif

/*
R A1 J8


[0][0] = [4][6]
[0][1] = [4][10]
[0][2] = [4][14]
[0][3] = [4][18]


[1][0] = [6][6]
[1][1] = [6][10]
[1][2] = [6][14]
[1][3] = [6][18]

[9][8] = [22][38]



x -> y

y = (x * 4) + 2

1 -> 6
2 -> 10
3 -> 14
4 -> 18
5 -> 22
6 -> 26

*/
