#include "lib.hh"
#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <chrono>

std::string
lSample6(" \
6     \
-+-++- \
+-+-+- \
-+--++ \
+---+- \
++++-+ \
--+-+- \
");

using namespace std;



void test_getEnds()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    stringstream lStream( lSample6 );
    Grid lGrid;
    lGrid.read( lStream );

    cout << boolalpha << lGrid.hasEdge( 0, 0 ) << lGrid.hasEdge( 4, 4 ) << endl;

    cout << "lMesh.getEnds( 0 ).size(): " << lGrid.getEnds( 0 ).size() << endl;
    cout << "lMesh.getEnds( 1 ).size(): " << lGrid.getEnds( 1 ).size() << endl;
    cout << "lMesh.getEnds( 2 ).size(): " << lGrid.getEnds( 2 ).size() << endl;
    cout << "lMesh.getEnds( 3 ).size(): " << lGrid.getEnds( 3 ).size() << endl;
    cout << "lMesh.getEnds( 4 ).size(): " << lGrid.getEnds( 4 ).size() << endl;

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_getNeighborStates()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    stringstream lStream( lSample6 );
    Grid lGrid;
    lGrid.read( lStream );

    list< State > lStates;
    Board lBoard( lGrid );

    lBoard.draw( State("012345"), cout );
    cout << endl << "        |" << endl << "        |" << endl << "        v" << endl << endl;
    lStates = lBoard.getNeighborStates( State("012345") );
    for_each( lStates.begin(), lStates.end(), bind( &Board::draw, lBoard, placeholders::_1, std::ref( cout ) ) );
    cout << string(20, '-') << endl;

    lBoard.draw( State("102345"), cout );
    cout << endl << "        |" << endl << "        |" << endl << "        v" << endl << endl;
    lStates = lBoard.getNeighborStates( State("102345") );
    for_each( lStates.begin(), lStates.end(), bind( &Board::draw, lBoard, placeholders::_1, std::ref( cout ) ) );
    cout << string(20, '-') << endl;

    lBoard.draw( State("120345"), cout );
    cout << endl << "        |" << endl << "        |" << endl << "        v" << endl << endl;
    lStates = lBoard.getNeighborStates( State("120345") );
    for_each( lStates.begin(), lStates.end(), bind( &Board::draw, lBoard, placeholders::_1, std::ref( cout ) ) );
    cout << string(20, '-') << endl;

    lBoard.draw( State("123045"), cout );
    cout << endl << "        |" << endl << "        |" << endl << "        v" << endl << endl;
    lStates = lBoard.getNeighborStates( State("123045") );
    for_each( lStates.begin(), lStates.end(), bind( &Board::draw, lBoard, placeholders::_1, std::ref( cout ) ) );
    cout << string(20, '-') << endl;

    lBoard.draw( State("123405"), cout );
    cout << endl << "        |" << endl << "        |" << endl << "        v" << endl << endl;
    lStates = lBoard.getNeighborStates( State("123405") );
    for_each( lStates.begin(), lStates.end(), bind( &Board::draw, lBoard, placeholders::_1, std::ref( cout ) ) );
    cout << string(20, '-') << endl;

    lBoard.draw( State("123450"), cout );
    cout << endl << "        |" << endl << "        |" << endl << "        v" << endl << endl;
    lStates = lBoard.getNeighborStates( State("123450") );
    for_each( lStates.begin(), lStates.end(), bind( &Board::draw, lBoard, placeholders::_1, std::ref( cout ) ) );

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_drawGrid_Size6()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "6 -+-++- +-+-+- -+--++ +---+- ++++-+ --+-+- " ) );
    lBoard.draw( State("012345"), cout );
    lBoard.draw( State("102345"), cout );
    lBoard.draw( State("120345"), cout );
    lBoard.draw( State("123045"), cout );
    lBoard.draw( State("123405"), cout );
    lBoard.draw( State("123450"), cout );

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_drawGrid_Size1()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "1 -" ) );
    lBoard.draw( State("0"), cout );
    lBoard.draw( State("1"), cout );

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_drawGrid_Size2()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "2 -+ +-" ) );
    lBoard.draw( State("01"), cout );
    lBoard.draw( State("10"), cout );

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_drawGrid_Size3()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "3 -+- +-- -+-" ) );
    lBoard.draw( State("012"), cout );
    lBoard.draw( State("102"), cout );
    lBoard.draw( State("120"), cout );

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_drawGrid()
{
    test_drawGrid_Size1();
    test_drawGrid_Size2();
    test_drawGrid_Size3();
    test_drawGrid_Size6();
}

void test_distance()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "6 -+-++- +-+-+- -+--++ +---+- ++++-+ --+-+- " ) );

    cout << lBoard.distance( State( "104352" ), State( "014352" ) ) << endl;
    cout << lBoard.distance( State( "140352" ), State( "014352" ) ) << endl;
    cout << lBoard.distance( State( "143052" ), State( "014352" ) ) << endl;
    cout << lBoard.distance( State( "143502" ), State( "014352" ) ) << endl;
    cout << lBoard.distance( State( "143520" ), State( "014352" ) ) << endl;
    cout << lBoard.distance( State( "123405" ), State( "014352" ) ) << endl;

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_solve1()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "6 -+-++- +-+-+- -+--++ +---+- ++++-+ --+-+- " ) );
    Solver lSolver;

    State lGoal( "123405" );
    cout << "Goal: " << endl;
    lBoard.draw(lGoal, cout);

    vector< State > lStarts{
          State("123450")
        , State("123045")
        , State("120345")
        , State("102345")
                              };

    for ( const State & lStart: lStarts )
    {
        cout << "Start: " << endl;
        lBoard.draw(lStart, cout);

        lSolver.solve( cout, lBoard, lStart, lGoal );
    }

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_solve2()
{
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "6 -+-++- +-+-+- -+--++ +---+- ++++-+ --+-+- " ) );
    Solver lSolver;
    State lStart( "014352" );
    State lGoal( "123405" );

    cout << "Goal: " << endl;
    lBoard.draw(lGoal, cout);
    cout << "Start: " << endl;
    lBoard.draw(lStart, cout);

    lSolver.solve( cout, lBoard, lStart, lGoal );

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_solve_classic_3x3( ostream & aOutput, const State & aStart/*, int aNumberOfSolutions, int aMaxMoves*/ )
{
    aOutput << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "9 " "-+-+----- "
                              "+-+-+---- "
                              "-+---+--- "
                              "+---+-+-- "
                              "-+-+-+-+- "
                              "--+-+---+ "
                              "---+---+- "
                              "----+-+-+ "
                              "-----+-+- " ) );
    Solver lSolver;

    State lGoal( "123456780" );

    aOutput << "Goal: " << endl;
    lBoard.draw(lGoal, aOutput);
    aOutput << "Start: " << endl;
    lBoard.draw(aStart, aOutput);

    lSolver.solve( aOutput, lBoard, aStart, lGoal );

    aOutput << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

void test_solve_classic_4x4( const State & aStart /*, int aNumberOfSolutions, int aMaxMoves*/ )
{
//    for ( size_t line = 0; line < 16; ++line )
//    {
//        for ( size_t row = 0; row < 16; ++row )
//        {
//            if ( line == row )
//            {
//                cout << "-";
//            }
//            else if ( ( line + row ) % 4 != 0 )
//            {
//                cout << "-";
//            }
//            else
//            {
//                cout << "+";
//            }
//        }
//        cout << endl;
//    }
    cout << string(20, '-') << " beg " << __PRETTY_FUNCTION__ << endl;

    Board lBoard( Grid ( "16 "
                         "-+--+----------- " //1
                         "+-+--+---------- " //2
                         "-+-+--+--------- " //3
                         "--+----+-------- " //4
                         "+----+--+------- " //5
                         "-+--+-+--+------ " //6
                         "--+--+-+--+----- " //7
                         "---+--+----+---- " //8
                         "----+----+--+--- " //9
                         "-----+--+-+--+-- " //A
                         "------+--+-+--+- " //B
                         "-------+--+----+ " //C
                         "--------+----+-- " //D
                         "---------+--+-+- " //E
                         "----------+--+-+ " //F
                         "-----------+--+- " //G
                         ) );
    Solver lSolver;

    State lGoal(  "123456789ABCDEF0" );

//    cout << "Goal: " << endl;
//    lBoard.draw(lGoal);
    cout << "Start: " << endl;
    lBoard.draw(aStart, cout);

    lSolver.solve( cout, lBoard, aStart, lGoal );

    cout << string(20, '-') << " end " << __PRETTY_FUNCTION__ << endl;
}

class TestSolveClassic3x3
{
public:
    void run()
    {
        thread gen( bind( &TestSolveClassic3x3::generatePermuations, this ) );

        this_thread::sleep_for( chrono::seconds(2) );

        thread jobs[] = {
            thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_01.txt" )
          , thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_02.txt" )
          , thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_03.txt" )
          , thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_04.txt" )
          , thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_05.txt" )
          , thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_06.txt" )
          , thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_07.txt" )
          , thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_08.txt" )
          , thread( &TestSolveClassic3x3::solvingJob, this, "results_3x3_09.txt" )
        };

        gen.join();
        for_each( begin(jobs), end(jobs), bind( &thread::join, placeholders::_1 ) );
    }

protected:
    void solvingJob( const string & aOutName )
    {
        ofstream lOutput( aOutName );
        while ( hasPermutaions() )
        {
            string lString( getPermutation() );
            if ( ! lString.empty() )
            {
                test_solve_classic_3x3( lOutput, State( lString ) );
            }
        }
    }

    void generatePermuations()
    {
        string lString( "012345678" );
        while ( next_permutation( lString.begin(), lString.end() ) )
        {
            unique_lock<mutex> lLock( iPermutationsMutex );
            static int a = 0;
            if (!(++a%100000))
                iPermutations.push_back( lString );
        }
        cout << "Finished generating permutations. " << iPermutations.size() << endl;
    }

    bool hasPermutaions()
    {
        unique_lock<mutex> lLock( iPermutationsMutex );

        return ! iPermutations.empty();
    }

    string getPermutation()
    {
        string lResult;
        {
            unique_lock<mutex> lLock( iPermutationsMutex );
            if ( ! iPermutations.empty() )
            {
                lResult = iPermutations.front();
                iPermutations.pop_front();
            }
        }

        return lResult;
    }

private:
    list< string > iPermutations;
    mutex          iPermutationsMutex;
};

int main( void )
{
//    cout << "sizeof(short int): " << sizeof( short int ) << endl;
//    return 0;
//    test_solve_classic_4x4( State( "123456789ABCDEF0") );
//    test_solve_classic_4x4( State( "0123456789ABCDEF") );
//    test_solve_classic_4x4( State( "1023456789ABCDEF") );
//    test_solve_classic_4x4( State( "1203456789ABCDEF") );
//    test_solve_classic_4x4( State( "1230456789ABCDEF") );
//    test_solve_classic_4x4( State( "1234056789ABCDEF") );
//    test_solve_classic_4x4( State( "1234506789ABCDEF") );
//    test_solve_classic_4x4( State( "1234560789ABCDEF") );
//    test_solve_classic_4x4( State( "1234567089ABCDEF") );
//    test_solve_classic_4x4( State( "1234567809ABCDEF") );
//    test_solve_classic_4x4( State( "1234567890ABCDEF") );
//    test_solve_classic_4x4( State( "123456789A0BCDEF") );
//    test_solve_classic_4x4( State( "123456789AB0CDEF") );
//    test_solve_classic_4x4( State( "123456789ABC0DEF") );
//    test_solve_classic_4x4( State( "123456789ABCD0EF") );
//    test_solve_classic_4x4( State( "123456789ABCDE0F") );

//    string lString( "123456789ABCDEF0" );
//    while ( next_permutation( lString.begin(), lString.end() ) )
//    {
//        test_solve_classic_4x4( State( lString ) );
//    }

//    return 0;

//    test_getEnds();
//    test_drawGrid();
//    test_getNeighborStates();
//    test_distance();

//    test_solve_classic_3x3( State( "123405786"), 1, 2 );
//    test_solve_classic_3x3( State( "123745086"), 1, 4 );
//    test_solve_classic_3x3( State( "123480765"), 1, 5 );
//    test_solve_classic_3x3( State( "413726580"), 1, 8 );
//    test_solve_classic_3x3( State( "162530478"), 1, 9 );
//    test_solve_classic_3x3( State( "512630478"), 1, 11 );
//    test_solve_classic_3x3( State( "126350478"), 1, 13 );
//    test_solve_classic_3x3( State( "356148072"), 1, 16 );
//    test_solve_classic_3x3( State( "436871052"), 1, 18 );
//    test_solve_classic_3x3( State( "302651478"), 2, 21 );
//    test_solve_classic_3x3( State( "012345678"), 2, 22 );
//    test_solve_classic_3x3( State( "503284671"), 1, 23 );
//    test_solve_classic_3x3( State( "874320651"), 1, 25 );
//    test_solve_classic_3x3( State( "876543021"), 2, 28 );
//    test_solve_classic_3x3( State( "876543210"), 2, 30 );

    TestSolveClassic3x3 test3x3;
    test3x3.run();


    return 0;

}
