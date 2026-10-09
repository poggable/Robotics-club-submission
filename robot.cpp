#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <list>
#include <stack>
#include <algorithm>

using namespace std;

class robot {
public:
    int x;
    int y;
    bool has_cube;

    robot(int initial_x, int initial_y) {
        x = initial_x;
        y = initial_y;
        has_cube = false;
    }

    void moveRight() { x += 1; }
    void moveRightUp() { x += 1, y+=1;}
    void moveRightDown() {x += 1, y -= 1;}
    void moveLeft()  { x -= 1; }
    void moveLeftUp() {x -= 1, y += 1;}
    void moveLeftDown() {x -= 1, y -= 1;}
    void moveUp()    { y += 1; }
    void moveDown()  { y -= 1; }
};
int matrix[5][5] = {};
bool inGrid(int x, int y){
   return x >= 0 && x <= 4 && y >= 0 && y <= 4;
}

bool bfs(robot& bot, vector<int> target){
    queue<pair<int, int>> q;
    bool discovered[5][5] = {}; // to check if i already discovered a cell
    pair<int, int> parent[5][5] = {}; // to keep track of the route, we assign each neighour a parent to find the route later
    if (target.size() != 2){
        return false;}
    if (inGrid(target[0], target[1]) == true){
        if (!inGrid(bot.x, bot.y)){
        return false;
        }
         if (matrix[bot.x][bot.y] != 0){
            return false;
        }
        vector<int> current_cell = {bot.x, bot.y};
         q.push({bot.x, bot.y});
        discovered[bot.x][bot.y] = true; //also have to set it as the start of the queue
        while (!q.empty()) { /* this is where teh search code begins, after initiating it by putting (0, 0), 
            the robots current position, into the queue */
        current_cell = {q.front().first, q.front().second}; // repetition, but important so we can start the search loop
        q.pop();
        if (current_cell == target){ // the following code traces back the routne, and moves the robot along it
    vector<vector<int>> route;
    vector<int> cell = target;

    while (cell != vector<int>{bot.x, bot.y}) {
        // the following is to trace back the route once we find the target
        route.push_back(cell);
        auto previous = parent[cell[0]][cell[1]];
        cell = {previous.first, previous.second}; // because parent is made of pairs we can use .first and .second
    } reverse(route.begin(), route.end());
    for (const vector<int>& next_cell : route) { // iterating over the route to move the robot 
    int dx = next_cell[0] - bot.x;
    int dy = next_cell[1] - bot.y;

    if      (dx == 1  && dy == 0)  bot.moveRight();
    else if (dx == -1 && dy == 0)  bot.moveLeft();
    else if (dx == 0  && dy == 1)  bot.moveUp();
    else if (dx == 0  && dy == -1) bot.moveDown();
    else if (dx == 1  && dy == 1)  bot.moveRightUp();
    else if (dx == 1  && dy == -1) bot.moveRightDown();
    else if (dx == -1 && dy == 1)  bot.moveLeftUp();
    else if (dx == -1 && dy == -1) bot.moveLeftDown();

    cout << "Robot at: " << bot.x << ", " << bot.y << "\n"; // stating where the robot is 
}
    return true;
}       /*searching, the program goes into this if the current cell is not the target,
          and it keeps looking for it until it finds it using bfs, then once it is found
          it runs the code above to find the route and move the robot accordingly*/ 

        // creating the list of neighbours of each current_cell
        vector<vector<int>> neighbours = {
    {current_cell[0] + 1, current_cell[1]},     
    {current_cell[0] - 1, current_cell[1]},     
    {current_cell[0],     current_cell[1] + 1}, 
    {current_cell[0],     current_cell[1] - 1}, 
    {current_cell[0] + 1, current_cell[1] + 1}, 
    {current_cell[0] + 1, current_cell[1] - 1}, 
    {current_cell[0] - 1, current_cell[1] + 1}, 
    {current_cell[0] - 1, current_cell[1] - 1}  
};
    for (const vector<int>& neighbour : neighbours) {
    int nx = neighbour[0];
    int ny = neighbour[1];
    // checking if the neighbour is valid and inside the grid
    if (inGrid(nx, ny) == true){  
    if (discovered[nx][ny] == false){
         if (matrix[nx][ny] == 0){
                            discovered[nx][ny] = true;
        parent[nx][ny] = {current_cell[0], current_cell[1]};    
        q.push({nx, ny});
    }}}}}}
    return false;
    }
    
int main(){
    robot robot1(0, 0); // making the robot object
    /*below im creating the obstacles, to equal 1, so that the check above for
     whether it is occupied can just check if the cell != 0 */
    vector<int> firstobstacle(2);
    vector<int> secondobstacle(2);
    vector<int> thirdobstacle(2);
    cout << "Please enter the first obstacle in the form x y: "; cin >> firstobstacle[0] >> firstobstacle[1];
    cout << "Please enter the second obstacle in the form x y: "; cin >> secondobstacle[0] >> secondobstacle[1];
    cout << "Please enter the third obstacle in the form x y: "; cin >> thirdobstacle[0] >> thirdobstacle[1]; 
    if (!cin ||
    !inGrid(firstobstacle[0], firstobstacle[1]) ||
    !inGrid(secondobstacle[0], secondobstacle[1]) ||
    !inGrid(thirdobstacle[0], thirdobstacle[1])) {

    cout << "Invalid obstacle coordinates.\n";
    return 1;
} 
    matrix[firstobstacle[0]][firstobstacle[1]] = 1; 
    matrix[secondobstacle[0]][secondobstacle[1]] = 1;
    matrix[thirdobstacle[0]][thirdobstacle[1]] = 1;
    /*and here we use the function twice, to reach the cube,then to deliver it, and give some comments, 
    most importantly when it cannot reach the cube at (2,2), or the destination at (4,4)*/
    if (bfs(robot1, {2, 2})) {
    robot1.has_cube = true;
    cout << "Cube collected!\n";

    if (bfs(robot1, {4, 4})) {
        cout << "Destination reached with cube!\n";
    } else {
        cout << "Cannot reach destination.\n";
    }
} else {
    cout << "Cannot reach cube.\n";
}
return 0;
}