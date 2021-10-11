#include "GameControl.hpp"

GameControl::GameControl(){
    // map<char, BattleShip> ship;

    // ship['D'] = enemyDestroyer;
};

GameControl::~GameControl(){};

void GameControl::MakeMove()
{
    // placement.FriendlyGridIntake("RA1A2", board.gameBoard);
    // placement.FriendlyGridIntake("MB1B3", board.gameBoard);
    // placement.FriendlyGridIntake("DC1C4", board.gameBoard);
    placement.FriendlyGridIntake("FD1D5", board.gameBoard);
    // board.PrintBoard();

    int x, y;
    while (x != 20)
    {
        cout << "----------Enemy Ships------------" << endl;
        for (int i = 0; i < 10; i++)
            cout << placement.enemyGrid[i] << endl;

        string input = "";
        cout << "Input: ";
        cin >> input;

        int rowStart = input[0] - 65;
        int colStart = input[1] - 49;

        engagement.Strike(rowStart, colStart, placement.enemyGrid, board.gameBoard);
        // board.PrintBoard();
        input = "";

        EnemyMakeMove();

        cout << "----------Friendly Ships------------" << endl;
        for (int i = 0; i < 10; i++)
            cout << placement.friendlyGrid[i] << endl;
    }
};

bool GameControl::isNewGuess(int row, int col)
{
    for (int i = 0; i < guessList.size(); i++)
    {
        if (guessList[i] == row && guessList[i + 1] == col)
            return false;
        i++;
    }
    return true;
}

int GameControl::GetShipBlock(char shipType)
{
    switch (shipType)
    {
    case 'R':
        return friendlyRadar.GetBlockNumber();
    case 'M':
        return friendlyMinor.GetBlockNumber();
    case 'D':
        return friendlyDestroyer.GetBlockNumber();
    case 'F':
        return friendlyFlag.GetBlockNumber();
    default:
        return 0;
    }
}

void GameControl::DestroyShipBlock(char shipType)
{
    switch (shipType)
    {
    case 'R':
        friendlyRadar.DestroyBlock();
        break;
    case 'M':
        friendlyMinor.DestroyBlock();
        break;
    case 'D':
        friendlyDestroyer.DestroyBlock();
        break;
    case 'F':
        friendlyFlag.DestroyBlock();
        break;
    }
}

void GameControl::EnemyMakeRandomGuess()
{
    bool newGuess = false;

    int guessRow;
    int guessCol;

    // Avoid Redundant Guesses
    while (!newGuess)
    {
        guessRow = placement.RandomNumberGenerator(0, 9);
        guessCol = placement.RandomNumberGenerator(0, 8);

        if (isNewGuess(guessRow, guessCol))
            newGuess = true;
    }
    guessList.push_back(guessRow);
    guessList.push_back(guessCol);

    // Computer Misses!
    if (placement.friendlyGrid[guessRow][guessCol] == '.')
    {
        placement.friendlyGrid[guessRow][guessCol] = 'x';
        cout << "MISS!" << endl;
    }

    // Computer Hits!
    else if (placement.friendlyGrid[guessRow][guessCol] == 'o')
    {
        cout << "HIT!" << endl;
        placement.friendlyGrid[guessRow][guessCol] = 'x';
        shipDetected = true;
        cout << "ROW:" << guessList[guessList.size() - 2] << endl;
        cout << "COL:" << guessList[guessList.size() - 1] << endl;

        detectedRow = guessList[guessList.size() - 2];
        detectedCol = guessList[guessList.size() - 1];

        char shipType = placement.GetCoordinateType(detectedRow, detectedCol);
        DestroyShipBlock(shipType);
    }
}

void GameControl::FindShipOrientation()
{
    int ranNum = placement.RandomNumberGenerator(1, 4);
    // Check Top
    switch (ranNum)
    {
    case 1:
        if (((detectedRow - 1) > -1) && (isNewGuess(detectedRow - 1, detectedCol)))
        {
            if (placement.friendlyGrid[detectedRow - 1][detectedCol] == 'o')
            {
                orientationDetected = true;
                direction = 'T';

                char shipType = placement.GetCoordinateType(detectedRow - 1, detectedCol);
                DestroyShipBlock(shipType);
            }
            cout << 'T' << endl;
            guessList.push_back(detectedRow - 1);
            guessList.push_back(detectedCol);
            placement.friendlyGrid[detectedRow - 1][detectedCol] = 'x';
        }
        break;
    // Check Right
    case 2:
        if (((detectedCol + 1) < 11) && (isNewGuess(detectedRow, detectedCol + 1)))
        {
            if (placement.friendlyGrid[detectedRow][detectedCol + 1] == 'o')
            {
                orientationDetected = true;
                direction = 'R';

                char shipType = placement.GetCoordinateType(detectedRow, detectedCol + 1);
                DestroyShipBlock(shipType);
            }
            cout << 'R' << endl;
            guessList.push_back(detectedRow);
            guessList.push_back(detectedCol + 1);
            placement.friendlyGrid[detectedRow][detectedCol + 1] = 'x';
        }
        break;
    // Check Down
    case 3:
        if (((detectedRow + 1) < 10) && (isNewGuess(detectedRow + 1, detectedCol)))
        {
            if (placement.friendlyGrid[detectedRow + 1][detectedCol] == 'o')
            {
                orientationDetected = true;
                direction = 'D';

                char shipType = placement.GetCoordinateType(detectedRow + 1, detectedCol);
                DestroyShipBlock(shipType);
            }
            cout << 'D' << endl;
            guessList.push_back(detectedRow + 1);
            guessList.push_back(detectedCol);
            placement.friendlyGrid[detectedRow + 1][detectedCol] = 'x';
        }
        break;
    // Check Left
    case 4:
        if (((detectedCol - 1) > -1) && (isNewGuess(detectedRow, detectedCol - 1)))
        {
            if (placement.friendlyGrid[detectedRow][detectedCol - 1] == 'o')
            {
                orientationDetected = true;
                direction = 'L';

                char shipType = placement.GetCoordinateType(detectedRow, detectedCol - 1);
                DestroyShipBlock(shipType);
            }
            cout << 'L' << endl;
            guessList.push_back(detectedRow);
            guessList.push_back(detectedCol - 1);
            placement.friendlyGrid[detectedRow][detectedCol - 1] = 'x';
        }
        break;
    }
};


void GameControl::HorizontalGuessing(char switchDirection)
{
    if (((detectedCol + 2) < 11) && ((detectedCol + 2) > -1) && (isNewGuess(detectedRow, detectedCol + 2)))
    {
        char shipType = placement.GetCoordinateType(detectedRow, detectedCol + 2);
        placement.friendlyGrid[detectedRow][detectedCol + 2] = 'x';
        if (placement.friendlyGrid[detectedRow][detectedCol + 2] == 'o')
        {
        // horizontalCounter++;
            DestroyShipBlock(shipType);

            // if the current coordinate we are at does not equal the original ship type,
            // we are dealing with more than one ship and should keep track of that
            if (shipType != placement.GetCoordinateType(detectedRow, detectedCol))
            {
                foundShipsList.push_back(detectedRow);
                foundShipsList.push_back(detectedCol + 2);
            }
        }
        else
            direction = switchDirection;
        guessList.push_back(detectedRow);
        guessList.push_back(detectedCol + 2);
    }
};


void GameControl::DestroyShip()
{
    switch (direction)
    {
    case 'T':
    case 'D':

    case 'R':
        AttackRight();
    case 'L':
    }
};

void GameControl::EnemyMakeMove()
{
    if (!shipDetected)
        EnemyMakeRandomGuess();
    else if (shipDetected == true && !orientationDetected)
    {
        cout << "yoo" << endl;
        FindShipOrientation();
    }
    else if (shipDetected == true && orientationDetected)
    {
        DestroyShip();
    }
};