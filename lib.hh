#pragma once

#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>

/// Represents the possible moves on the board.
class Grid
{
public:
    Grid() {};
    explicit Grid( const std::string & aDescription );

    short getSize() const;

    std::list< short > getEnds( short aBeg ) const;

    bool hasEdge( short aBeg, short aEnd ) const;

    void read( std::istream& aInput );

    short distance( short aBeg, short aEnd ) const;

private:
    std::vector< std::vector< bool > > iEdges;
};


/// Represents the allocation of tiles on the board
class State
{
public:
    typedef std::list< State > Path;
    typedef uint64_t HashType;

public:
    explicit State( const std::string & aAllocation );

    short getBlank() const; /// returns index of blank tile
    char getAt( short aIndex ) const;
    HashType getHash() const;

    State move( short aDestination ) const;

    bool operator== ( const State & aLhs ) const;
    bool operator< ( const State & aLhs ) const;

    std::ostream & print( std::ostream & aOutput ) const;

private:
    std::string iAllocation;
};


/// represents Mesh and State
class Board
{
public:
    explicit Board( const Grid & aGrid );

    std::list< State > getNeighborStates( const State & aState ) const;
    int distance( const State & aLhs, const State & aRhs ) const;

    void draw( const State & aState, std::ostream & aOut ) const;

private:
    Grid iGrid;
};


class Solver
{
public:
    void solve( std::ostream & aOut, const Board & aBoard, const State & aStartState, const State & aGoalState, unsigned short iMinNumberOfSolution = 1 );

protected:
    bool visited( const State & aState ) const;

private:
    std::set< State::HashType > iVisited;
};
