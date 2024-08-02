// Mehmet Selman Yilmaz 31158 CS300 Homework1

#include <iostream>
#include <string>
#include<fstream>
#include "dStack.h"
#include "randgen.h"
#include <sstream>


using namespace std;

/*
 *The purpose of this program is to build a maze.
 * While doing this, it breaks walls randomly, if there is no wall suitable for breaking,
 * it turns back and continues to break from the nearest wall suitable for breaking.
 *
 *It provides the solution with the same logic.
 * The only difference is, instead of breaking a wall, you go to that cell if there is no wall.
 *
 */




// Structure to store coordinates
//This struct will be created in order to not keep current pointer's information
struct mazeBreakerElem{
    int x;
    int y;

    // Constructors
    mazeBreakerElem() : x(-1), y(-1) {} //Default
    mazeBreakerElem(int xElem,int yElem) : x(xElem), y(yElem) {} //Parametrized
};

// Function to get maze inputs from the user
void getMazeInputs(int & mazeQuantity, int & mazeRow, int & mazeColumn)
{

    cout << "Enter the number of mazes: ";
    cin >> mazeQuantity;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> mazeRow >> mazeColumn;
}
// Function to get path inputs from the user
void getPathInputs(int & mazeID, int & entryX,int & entryY,int & exitX,int & exitY,int mazeQuantity)
{
    cout << "\nEnter a maze ID between 1 " << "to "<< mazeQuantity <<" inclusive to find a path: ";
    cin >> mazeID;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> entryX >> entryY;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin >> exitX >> exitY;
}
// Function to create all walls in the maze (It doesn't make a maze, it just fills all the walls)
void createAllWalls(dStack<cell> & Maze, int mazeRow,int mazeColumn)
{
    for(int i = mazeRow-1; i>=0;i--)
    {
        for(int j = mazeColumn -1; j>=0;j--)
        {

            cell newCell(j, i, true, true, true, true, false, 0);

            // Assign unbreakable walls based on position
            //1=left is unbreakable, 2 right is uB, 3 up is uB, 4 down is uB, 5 left and up, 6 left and down, 7 right and up, 8 right and down
            if(i == 0 && j == 0){newCell.unbreakable =6;}
            else if(j==mazeColumn-1 && i == 0){newCell.unbreakable = 8;}
            else if(j==0 && i == mazeRow-1){newCell.unbreakable = 5;}
            else if(j==mazeColumn-1 && i== mazeRow-1){newCell.unbreakable = 7;}
            else if(j== 0 ){newCell.unbreakable = 1;}
            else if(j==mazeColumn-1){newCell.unbreakable = 2;}
            else if(i== mazeRow-1 ){newCell.unbreakable = 3;}
            else if(i==0 ){newCell.unbreakable = 4;}

            Maze.push(newCell);


        }
    }
}
template<class T>
// Function to check if all cells in the maze have been visited
bool isAllVisited(dStack<T> & Maze)
{

    bool check = true;
    cell x;
    dStack<cell> temp;

    while(!Maze.isEmpty())
    {
        Maze.pop(x);
        temp.push(x);
    }

    while(!temp.isEmpty())
    {
        temp.pop(x);
        Maze.push(x);
        //If one of the cells is unvisited return false
        if(!x.isVisited)
        {
            check = false;
        }
    }
    //If none of the cell is unvisited return true
    return check;

}




// Function to check if a move is possible in order to break to wall
bool isPossibleMove (sNode<cell> * current, dStack<cell> & Maze, int & breaker,int mazeRow, int mazeColumn)
{
    RandGen rnd; // Set seed for Randgen
    cell x;
    bool imRight = false ,imLeft = false ,imUp=false,imDown=false;
    dStack<cell> temp;

    //Choose random wall breaker
    breaker = rnd.RandInt(1,4); // Choose a random direction (1: left, 2: right, 3: up, 4: down)

    //Transfer elements to the temp
    while(!Maze.isEmpty())
    {
        Maze.pop(x);
        temp.push(x);
    }
    // Check neighboring cells in temp stack in order to see which walls are not possible for breaking
    while(!temp.isEmpty())
    {
        temp.pop(x);
        //Check the right
        if(x.xCoordinate == current->element.xCoordinate+1 && x.yCoordinate == current->element.yCoordinate)
        {
            if(x.isVisited)
            {imRight=true;}
        }
        //Check the left
        if(x.xCoordinate == current->element.xCoordinate-1 && x.yCoordinate == current->element.yCoordinate)
        {
            if(x.isVisited)
            {imLeft = true;}
        }
        //Check the up
        if(x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate+1)
        {
            if(x.isVisited)
            {imUp=true;}
        }
        //Check the down
        if(x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate-1)
        {
            if(x.isVisited)
            {imDown = true;}
        }
        // Additional checks for unbreakable walls based on current cell's position
        if(current->element.unbreakable==1){imLeft=true;}
        else if(current->element.unbreakable==2){imRight=true;}
        else if(current->element.unbreakable==3){imUp = true;}
        else if(current->element.unbreakable==4){imDown=true;}
        else if(current->element.unbreakable==5){imLeft = true; imUp=true;}
        else if(current->element.unbreakable==6){imLeft = true; imDown = true;}
        else if(current->element.unbreakable==7){imRight=true; imUp = true;}
        else if(current->element.unbreakable==8){imRight=true; imDown=true;}
        // Adjust moves if the maze is a single row or column
        if(mazeRow == 1)
        {
            imUp = true; imDown = true;
            if(current->element.xCoordinate == 0){imLeft = true;}
            else if(current->element.xCoordinate == mazeColumn-1){imRight = true;}
        }
        if(mazeColumn== 1)
        {
            imLeft = true; imRight = true;
            if(current->element.yCoordinate == 0){imDown = true;}
            else if(current->element.yCoordinate == mazeRow-1){imUp = true;}
        }
        Maze.push(x);
    }
    //If all moves impossible return false
    if(imDown && imRight && imLeft && imUp){return false;}

    // Otherwise, return true.
    // Before that if random wall breaker is not possible, choose a possible random wall which can be broken.
    while( (imDown&& breaker == 4) || (imRight && breaker==2) || (imLeft && breaker == 1) || (imUp && breaker == 3 ) )
    {
        breaker = rnd.RandInt(1,4); //choose wall which will be break again (Ex wall breaker move is not possible move)
    }
    return true;
}

// This function checks if a path is possible for the maze (Path is Dead End or not)
bool isPossiblePath(sNode<cell> * current, dStack<cell> & Maze, int & direction)
{
    RandGen rnd; // Set seed for Randgen
    cell x;
    bool imRight = false ,imLeft = false ,imUp=false,imDown=false;
    dStack<cell> temp;

    // Transfer elements from Maze to temp stack
    while(!Maze.isEmpty())
    {
        Maze.pop(x);
        temp.push(x);
    }

    // Check neighboring cells in temp stack in order to see what is the impossible moves
    while(!temp.isEmpty())
    {
        temp.pop(x);
        //Check right neighbor
        if(x.xCoordinate == current->element.xCoordinate+1 && x.yCoordinate == current->element.yCoordinate)
        {
            if(x.isVisited)
            {imRight=true;}
        }
        //Check left neighbor
        if(x.xCoordinate == current->element.xCoordinate-1 && x.yCoordinate == current->element.yCoordinate)
        {
            if(x.isVisited)
            {imLeft = true;}
        }
        //Check up neighbor
        if(x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate+1)
        {
            if(x.isVisited)
            {imUp=true;}
        }
        //Check down neighbor
        if(x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate-1)
        {
            if(x.isVisited)
            {imDown = true;}
        }

        Maze.push(x);
    }
    // Check current cell's available moves (If there is a wall move is not possible)
    if(current->element.left){ imLeft=true;}
    if(current->element.right){ imRight=true;}
    if(current->element.up){ imUp = true;}
    if(current->element.down){ imDown=true;}
    //Check if there is a dead end
    if(imDown && imRight && imLeft && imUp){return false;}
    //If there is no dead end(Move is possible), change direction if the current direction is not possible; If direction is good skip.
    while(imDown&& direction == 4 || imRight && direction==2 || imLeft && direction == 1 || imUp && direction == 3)
    {
        direction = rnd.RandInt(1,4); //Choose a different direction
    }
    return true;
}

// This function retrieves the current node in the maze
void getCurrent(mazeBreakerElem curr, sNode<cell> * & current,dStack<cell> & Maze,dStack<cell> &copyMaze)
{
    /* Create copyMaze.
     * Aim of copyMaze keeping track of the current cell. Thanks to copy stack, while transfering elements in original Maze
     * Current cell pointer will not lose
    */
    copyMaze = Maze;
    cell x;
    sNode<cell> * tempNode;
    dStack<cell> temp;

    // Transfer elements from Maze to copyMaze stack
    while(!copyMaze.isEmpty())
    {
        copyMaze.pop(x);
        temp.push(x);
    }
    // Find and set the current node
    while(!temp.isEmpty())
    {
        temp.pop(x);
        copyMaze.pushGet(x,tempNode);
        if(curr.x == x.xCoordinate && curr.y == x.yCoordinate)
        {
            current = tempNode; // Set the current node
        }
    }

}

// Function to break walls in a maze in order to create maze which all paths have one solution
void breakWalls(dStack<cell> & Maze,int mazeRow,int mazeColumn)
{

    dStack<cell> copyMaze,temp,wallBreaker; // Stacks to hold maze data
    sNode<cell> * current;
    mazeBreakerElem curr = mazeBreakerElem(0,0); //Store it in order to not lose while transferin elements in original stack
    getCurrent(curr,current,Maze,copyMaze);


    bool newCurrentCheck = false, checkpoint = false; // Flag to track if a new current node is selected

    cell x;
    RandGen rnd; // Set seed for RandGen
    int breaker; // Variable to store the random direction chosen




    // While there are unvisited nodes in the maze, keep breaking the walls
    while(!isAllVisited(Maze))
    {

        // While there is a possible move,no need to backtrack
        while(isPossibleMove(current,Maze,breaker,mazeRow,mazeColumn))
        {

            // Implementation of wall-breaking

            //Transfer maze into temp stack
            while(!Maze.isEmpty())
            {
                Maze.pop(x);
                temp.push(x);
            }
            while(!temp.isEmpty())
            {
                temp.pop(x);
                // Break the wall based on the chosen direction (Breaks wall in our new cell)
                if( (x.xCoordinate == current->element.xCoordinate+1 && x.yCoordinate == current->element.yCoordinate && breaker == 2) ||(x.xCoordinate == current->element.xCoordinate-1 && x.yCoordinate == current->element.yCoordinate && breaker == 1) || (x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate+1 && breaker == 3 ) || (x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate-1 && breaker == 4) )
                {
                    x.isVisited = true;
                    if(breaker == 1) {x.right = false;}
                    else if(breaker == 2) {x.left = false;}
                    else if(breaker == 3) {x.down  = false;}
                    else if(breaker == 4) {x.up = false;}
                    newCurrentCheck = true;
                    curr.x = x.xCoordinate ;
                    curr.y = x.yCoordinate ;
                }

                // Break the wall for our old cell
                if(x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate)
                {
                    if(breaker==1){x.left = false;}
                    else if(breaker==2){x.right = false;}
                    else if(breaker==3){x.up = false;}
                    else if(breaker==4){x.down = false;}
                    if(x.xCoordinate == 0 && x.yCoordinate == 0) {x.isVisited = true;}
                    wallBreaker.push(x);
                }

                Maze.push(x);


            }
            // If a new current node is selected, update the current node
            if(newCurrentCheck)
            {

                getCurrent(curr,current,Maze,copyMaze);

            }
            newCurrentCheck=false;

        }
        wallBreaker.push(current->element); // Push the current node to the wall breaker stack


        // If all cells are not visited, we need to go back. It goes to the nearest cell where it is possible to break the wall
        if(!isAllVisited(Maze))
        {


            while(!wallBreaker.isEmpty())
            {
                wallBreaker.pop(x);
                curr.x = x.xCoordinate ;
                curr.y = x.yCoordinate ;
                getCurrent(curr,current,Maze,copyMaze);
                // If a new possible move is found, push the cell to the wall breaker stack and break the loop
                if(isPossibleMove(current,Maze,breaker,mazeRow,mazeColumn) && !checkpoint)
                {
                    temp.push(x);
                    checkpoint = true;
                }
                else if (checkpoint)
                {
                    temp.push(x);
                }
            }
            while(!temp.isEmpty())
            {
                temp.pop(x);
                wallBreaker.push(x);
            }
        }
        current = wallBreaker.getTop();
        checkpoint = false;
    }
}


// Function to create a maze_mazeID.txt file
void createMazeFile(dStack<cell> & Maze, int mazeQuantity, int mazeRow, int mazeColumn)
{
    ofstream output;
    string fileName;
    cell value;

    // Construct the filename
    fileName = "maze_" + to_string(mazeQuantity) + ".txt";
    output.open(fileName.c_str());

    // Write maze dimensions to the file
    output << mazeRow << " " << mazeColumn << endl;

    // Empty the maze stack and write the data into the text file
    while(!Maze.isEmpty())
    {
        Maze.pop(value);
        output << "x="<< value.xCoordinate <<" y="<< value.yCoordinate <<" l="<< value.left <<" r="<< value.right <<" u="<< value.up <<" d=" <<value.down << endl;

    }
    output.close();



}

// Function to create a path_mazeID_entryX_entryY_exitX_exitY.txt file within the maze
void createPathFile(dStack<cell> & mazePath, int mazeNumber, int entryX, int entryY,int exitX,int exitY)
{
    ofstream output;
    string fileName;
    cell value;

    // Construct the filename for the path file
    fileName = "maze_" + to_string(mazeNumber) + "_path_" + to_string(entryX) + "_" + to_string(entryY) + "_" + to_string(exitX) + "_" + to_string(exitY)+ ".txt";
    output.open(fileName.c_str());

    // Empty the mazePath stack and write the data into the text file
    while(!mazePath.isEmpty())
    {
        mazePath.pop(value);
        output << value.xCoordinate <<" "<< value.yCoordinate  << endl;

    }
    output.close();



}

// Function to read the maze data from a file
void readMazeFile(dStack<cell> & Maze, int mazeID)
{
    cell value;
    int mazeRow,mazeColumn;
    string line,xCord,yCord,left,right,up,down;

    string filename= "maze_" +to_string(mazeID) +".txt";
    ifstream input(filename);

    // Read maze dimensions from the file
    getline(input, line);
    istringstream rcStream(line);
    rcStream >> mazeRow >> mazeColumn;

    // Read cell data from the file and push it to the stack
    while (getline(input, line)) {
        istringstream xyStream(line);
        xyStream >> xCord >> yCord >> left >> right >> up >> down;
        value = cell( stoi(xCord.substr(2)),stoi(yCord.substr(2)), stoi(left.substr(2)), stoi(right.substr(2)), stoi(up.substr(2)) , stoi(down.substr(2)) , false, 0);
        Maze.push(value);
    }
    input.close();

}



// This function creates a path through the maze using a depth-first search algorithm
// If it goes down a dead end, it won't go down that road again.
dStack<cell> createPath(dStack<cell> & Maze, int entryX, int entryY, int exitX,int exitY)
{

    // Initialize necessary stacks and variables
    dStack<cell> copyMaze,temp,pathFinder,mazePath;
    sNode<cell> * current;
    mazeBreakerElem curr = mazeBreakerElem(entryX,entryY);
    getCurrent(curr,current,Maze,copyMaze);
    bool newCurrentCheck = false,backtrack = false;

    cell x;
    RandGen rnd; // Set seed for Randgen
    int direction; // Variable to store the random chosen direction
    current->element.isVisited = true;
    pathFinder.push(current->element);  // Push the initial element into the pathFinder stack

    // Push the initial element into the Maze stack
    // Transfer the entire maze into the temp stack
    while(!Maze.isEmpty())
    {
        Maze.pop(x);
        temp.push(x);
    }
    while(!temp.isEmpty())
    {
        temp.pop(x);
        if(curr.x == x.xCoordinate && curr.y == x.yCoordinate)
        {
            x.isVisited =true;
        }
        Maze.push(x);
    }





    // Navigate through the maze until the exit is reached
    while(current->element.xCoordinate !=exitX || current->element.yCoordinate != exitY)
    {
        direction = rnd.RandInt(1,4); // Choose a random direction (1: left, 2: right, 3: up, 4: down)

        // Move in the selected direction if it's a possible path and not at the exit
        while(isPossiblePath(current,Maze,direction) && !(current->element.xCoordinate ==exitX && current->element.yCoordinate == exitY) )
        {
            // Transfer the entire maze into the temp stack
            while(!Maze.isEmpty())
            {
                Maze.pop(x);
                temp.push(x);
            }

            // Search for the next cell based on the selected direction
            while(!temp.isEmpty())
            {
                temp.pop(x);
                // If the cell in the direction indicated by the direction variable is change isVisited varriables,
                // and get its information in order to make it next current
                if( ( x.xCoordinate == current->element.xCoordinate+1 && x.yCoordinate == current->element.yCoordinate && direction == 2 ) || (x.xCoordinate == current->element.xCoordinate-1 && x.yCoordinate == current->element.yCoordinate && direction == 1) || (x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate+1 && direction == 3) || (x.xCoordinate == current->element.xCoordinate && x.yCoordinate == current->element.yCoordinate-1 && direction == 4))
                {
                    x.isVisited = true; newCurrentCheck = true; curr.x = x.xCoordinate ; curr.y = x.yCoordinate ;
                }
                Maze.push(x);


            }
            // Update the current cell if a new cell has been found
            if(newCurrentCheck)
            {

                getCurrent(curr,current,Maze,copyMaze);

            }
            newCurrentCheck=false;
            pathFinder.push(current->element); // Push the current element into the pathFinder stack

        }

        //If out path is dead end we need to go back
        if(!(current->element.xCoordinate ==exitX && current->element.yCoordinate == exitY))
        {
            bool checkpoint = false;

            while(!pathFinder.isEmpty())
            {
                pathFinder.pop(x);
                curr.x = x.xCoordinate ;
                curr.y = x.yCoordinate ;
                getCurrent(curr,current,Maze,copyMaze);
                // If a new possible path is found checkpoint will be true; means rest of the cells until this points are dead end
                if(isPossiblePath(current,Maze,direction) && !checkpoint)
                {
                    temp.push(x);
                    checkpoint = true;
                }
                //Push other cells until checkpoint cell
                else if (checkpoint)
                {
                    temp.push(x);
                }
            }
            //Fill my pathFinder from temp
            while(!temp.isEmpty())
            {
                temp.pop(x);
                pathFinder.push(x);
            }
            //Update the current cell
            current = pathFinder.getTop();
            checkpoint = false;
        }
    }
    return pathFinder; // Return the path through the maze
}

// Function to construct the one maze. This function will be called mazeQuantity times.
void constructMaze(int mazeQuantity,int mazeRow,int mazeColumn)
{
    dStack<cell> Maze;
    //Call the function which fill all the walls
    createAllWalls(Maze,mazeRow,mazeColumn);

    //Call the function which break walls in order to properly create the maze
    breakWalls(Maze,mazeRow,mazeColumn);

    //Call the function that prints the maze to text file
    createMazeFile(Maze,mazeQuantity,mazeRow,mazeColumn);
}

void constructPath(int mazeID,int entryX,int entryY, int exitX, int exitY)
{
    dStack<cell> mazePath,Maze;

    readMazeFile(Maze,mazeID); // Read the maze from a text file

    mazePath = createPath(Maze,entryX,entryY,exitX,exitY);  // Find and store the path through the maze in the text file

    createPathFile(mazePath,mazeID,entryX,entryY,exitX,exitY); // Create a text file for maze path file
}

int main() {

    int mazeQuantity,mazeRow,mazeColumn,mazeID,entryX,entryY,exitX,exitY;

    // Get inputs for maze generation
    getMazeInputs(mazeQuantity,mazeRow,mazeColumn);

    // Construct multiple mazes based on the inputs
    for(int i= 1; i<=mazeQuantity; i++)
    {
        constructMaze(i,mazeRow,mazeColumn);
    }
    cout << "All mazes are generated.\n";

    getPathInputs(mazeID,entryX,entryY,exitX,exitY,mazeQuantity); // Get inputs for finding a path through the maze

    constructPath(mazeID,entryX,entryY, exitX,exitY); //Construct solution



    return 0;
}
