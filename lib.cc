#include "lib.hh"

#include <limits>
#include <iostream>
#include <vector>
#include <sstream>
#include <ostream>
#include <string>
#include <list>
#include <algorithm>
#include <string.h>
#include <algorithm>
#include <functional>
#include <memory>
#include <queue>

using namespace std;

Grid::Grid( const std::string & aDescription )
{
    stringstream lStream( aDescription );
    read( lStream );
}

short Grid::getSize() const
{
    return static_cast< short >( iEdges.size() );
}

list< short > Grid::getEnds( short aBeg ) const
{
    list< short > lResult;
    for ( size_t lI = 0; lI < iEdges[aBeg].size(); ++lI )
    {
        if ( iEdges[aBeg][lI] )
        {
            lResult.push_back( lI );
        }
    }

    return lResult;
}

bool Grid::hasEdge( short aBeg, short aEnd ) const
{
    return iEdges[aBeg][aEnd];
}

void Grid::read( istream& aInput )
{
    short lSize;

    aInput >> lSize;
    iEdges.resize( lSize, vector< bool >( lSize, false ) );

    short lLine = 0;
    for ( ; lLine < lSize; ++lLine )
    {
        short lRow = 0;
        for ( ; lRow < lSize; ++lRow )
        {
            char lChar = 0;

            if ( aInput >> lChar )
            {
                iEdges[lLine][lRow]
                = iEdges[lRow][lLine]
                = ( lChar == '+' );
            }

//            cout << lLine << ", " << lRow << " = " << lChar << endl;
        }
    }
}

short Grid::distance(short aBeg, short aEnd) const
{
//    short aBegX = aBeg % 4;
//    short aBegY = aBeg / 4;
//    short aEndX = aEnd % 4;
//    short aEndY = aEnd / 4;

//    short lResult = abs(aBegX-aEndX) + abs(aBegY-aEndY);

//    cout << "aBegX: " << aBegX
//         << ", aBegY: " << aBegY
//         << ", aEndX: " << aEndX
//         << ", aEndY: " << aEndY
//         << ", lResult: " << lResult << endl;

//    return lResult;



    if (aBeg == aEnd )
    {
        return 0;
    }

    if ( iEdges[aBeg][aEnd] )
    {
        return 1;
    }

    return 2;
}

State::State( const string & aAllocation )
    : iAllocation( aAllocation )
{}

short State::getBlank() const
{
    return static_cast< short >( iAllocation.find( '0' ) );
}

char State::getAt( short aIndex ) const
{
    return iAllocation[aIndex];
}

State::HashType State::getHash() const
{
    stringstream lStream( iAllocation );
    uint64_t lResult;
    lStream >> hex >> lResult;
    return lResult;
}


State State::move( short aDestination ) const
{
    string lNew = iAllocation;
    swap( lNew[ lNew.find('0') ], lNew[aDestination] );

    return State( lNew );
}

bool State::operator== ( const State & aLhs ) const
{
    return iAllocation == aLhs.iAllocation;
}

bool State::operator< ( const State & aLhs ) const
{
    return iAllocation < aLhs.iAllocation;
}

ostream & State::print(ostream &aOutput) const
{
    return (aOutput << "[" << iAllocation << "]");
}



Board::Board( const Grid & aGrid )
    : iGrid( aGrid )
{}

list< State > Board::getNeighborStates( const State & aState ) const
{
    list< State > lResult;

    short lCurrentIndex = aState.getBlank();
    list< short > lEnds = iGrid.getEnds( lCurrentIndex );

    for ( const auto & lBeg: lEnds )
    {
        lResult.push_back( aState.move( lBeg) );
    }

    return lResult;
}

int Board::distance( const State & aLhs, const State & aRhs ) const
{
    int lResult = 0;
    for ( size_t lI = 0; lI < iGrid.getSize(); ++lI )
    {
        if ( aLhs.getAt(lI) != '0' && aRhs.getAt(lI) != '0')
        {
            int lLVal = aLhs.getAt(lI)-'1';
            int lRVal = aRhs.getAt(lI)-'1';
            lLVal = (lLVal > 9) ? lLVal + '1' - 'A' : lLVal;
            lRVal = (lRVal > 9) ? lRVal + '1' - 'A' : lRVal;
            lResult += iGrid.distance( lLVal, lRVal );
        }
    }

    return lResult;
}

void Board::draw( const State & aState, std::ostream & aOut ) const
{
    int lNumberOfTiles = iGrid.getSize();
    int lNumberOfTilesOnSide = ceil( std::sqrt( lNumberOfTiles ) );
    int lScreenSizeRows = (3+2)*lNumberOfTilesOnSide;
    int lScreenSizeLines = (3+2)*lNumberOfTiles/lNumberOfTilesOnSide;

    char lScreen[lScreenSizeLines][lScreenSizeRows];
    memset( lScreen, ' ', sizeof(lScreen) );

    for ( size_t lTile = 0; lTile < iGrid.getSize(); ++lTile )
    {
        // draw a tile
        size_t lRow  = lTile % lNumberOfTilesOnSide;
        size_t lLine = lTile / lNumberOfTilesOnSide;

        size_t lYc = lLine * (3+2)+1;
        size_t lXc = lRow * (3+2)+1;

        lScreen[lYc-1][lXc] = '-';
        lScreen[lYc+1][lXc] = '-';
        lScreen[lYc][lXc-1] = '|';
        lScreen[lYc][lXc+1] = '|';

        lScreen[lYc-1][lXc-1] = '+';
        lScreen[lYc-1][lXc+1] = '+';
        lScreen[lYc+1][lXc-1] = '+';
        lScreen[lYc+1][lXc+1] = '+';

        lScreen[lYc][lXc] = aState.getAt(lTile) == '0' ? ' ' : aState.getAt(lTile);
    }

    aOut << string( lScreenSizeRows+4, '*' ) << endl;
    for ( size_t lLine = 0; lLine < lScreenSizeLines; ++lLine )
    {
        aOut << "* " <<  string( lScreen[lLine], 0, lScreenSizeRows ) << " *" << endl;
    }
    aOut << string( lScreenSizeRows+4, '*' ) << endl;
}

int cost( const Board & aBoard, const State & aStartState, const State & aGoalState, const State & aCurrentState )
{
    return aBoard.distance( aStartState, aCurrentState ) + aBoard.distance( aCurrentState, aGoalState );
}

class Node;
typedef shared_ptr< Node > NodePtr;

class Node
{
    State iState;
    signed char iScore; // from start to this State
    signed char iCost;  // heuristic from this to goal

    NodePtr iParent;

public:

    Node( const State & aState, signed char aCost, signed char iScore )
        : iState( aState )
        , iScore( 0 )
        , iCost( aCost )
    {}


    Node( const State & aState, signed char aCost, const NodePtr & aParent )
        : iState( aState )
        , iCost( aCost )
        , iParent( aParent )
    {
        if ( iScore == numeric_limits< signed char >::max() )
            throw 1;
        iScore = iParent->iScore + 1;
//        cout << iScore << endl;
    }

    const State & getState() const { return iState; }
    NodePtr getParent() const { return iParent; }

    bool operator> ( const Node & aRhs ) const
    {
//        cout << "XXXXXXXXXXXXXX: " << (iScore + iCost) << " < " << (aRhs.iScore + aRhs.iCost) << endl;
        if ( int(iScore) + int(iCost) > numeric_limits< signed char >::max() )
            throw 1;

        return (iScore + iCost) > (aRhs.iScore + aRhs.iCost);
    }
};

void Solver::solve( std::ostream & aOut, const Board & aBoard, const State & aStartState, const State & aGoalState, unsigned short iMinNumberOfSolution )
{
    priority_queue< NodePtr, vector< NodePtr >, bool(*)( const NodePtr&, const NodePtr&) > lOpenSet1( 
        [](const NodePtr& aLhs, const NodePtr& aRhs){ return *aLhs > *aRhs;} );
    lOpenSet1.push( NodePtr( new Node(aStartState, aBoard.distance( aStartState, aGoalState), 0) ) );

    while ( ! lOpenSet1.empty() && iMinNumberOfSolution != 0 )
    {
        NodePtr lCurrentNode( lOpenSet1.top() );
//        aOut << "YYYYYYYYYYYYYY" << endl;
        lOpenSet1.pop();

        State lCurrentState( lCurrentNode->getState() );

//        lCurrentState.print(aOut) << endl;

        if ( lCurrentState == aGoalState )
        {
            aOut << "solution: " << endl;
            lCurrentNode->getState().print(aOut) << endl;
            int lNumberOfMoves = 0;
            NodePtr lNode = lCurrentNode;
            while ( lNode = lNode->getParent() )
            {
                ++lNumberOfMoves;
                lNode->getState().print(aOut) << endl;
//                aBoard.draw( lNode->getState() );
            }
            aOut << "lNumberOfMoves: " << lNumberOfMoves << endl;
            aOut << "iVisited: " << iVisited.size() << endl;
            aOut << string(20, '-') << endl;

            --iMinNumberOfSolution;
        }

        list< State > lNeighbors = aBoard.getNeighborStates( lCurrentState );
	for ( const auto & lNeighborState: lNeighbors )
        {
            if ( !visited( lNeighborState ) )
            {
                lOpenSet1.push( NodePtr( new Node(lNeighborState, aBoard.distance(lNeighborState, aGoalState), lCurrentNode) ) );
            }
        }

        iVisited.insert( lCurrentState.getHash() );

//        if ( ! (iVisited.size() % 10000) )
//            aOut << iVisited.size() << endl;

//        if ( iVisited.size() > 10000000L )
//            return;
    }
    aOut << "iVisited: " << iVisited.size() << endl;
}

bool Solver::visited(const State &aState) const
{
    return iVisited.find( aState.getHash() ) != iVisited.end();
}


