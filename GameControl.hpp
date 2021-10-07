#ifndef GameControl_HPP
#define GameControl_HPP

#include "BoardDisplay.hpp"
#include "Engagement.hpp"
#include "ShipPlacement.hpp"

class GameControl
{
    private:
        BoardDisplay board;
        Engagement engagement;
        ShipPlacement placement;

    public:
        void MakeMove();
};

#endif