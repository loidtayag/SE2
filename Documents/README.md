#Game logic
I wanted an easy way to access all the variables needed and so just made a struct to store everything. I used a 2D char
array as the board because when displaying the board I can just loop through while displaying each char and changing and
comparing the char values is simple.

##Turn Simulation
Keep looping until board is filled or both players have passed i.e. had no available moves.
In the loop, it simulates a turn just before it switches to the other person at the end.

##Move Input
Spot: the index in the 2D array i.e. 'board' where the player wishes to place a disc.

This is a general overview of it but the code has code that are necessary and would take too long to explain,

0. First of all, we need to check if the player even has any valid moves left. If s/he does we can move onto the following 
but if s/he doesn't that would mean we'd have to skip the following and end their turn early.
1. Ask for spot.
2. Check if spot is empty, if not ask user for another move until an empty spot is chosen.
3. Loop through any direction until the same color is reached WHILE keeping a 'jumpCounter' that keeps track of how many 
   discs we had to check to get to the furthest dice that was the same color. (If a 'current_color' i.e. same color
   isn't found skip to step 5)
4. Return to the spot and loop through the same direction for 'jumpCounter' amount of times while turning every dice 
   into the 'current_color'.
5. Repeat steps 2 - 3  for rest of directions.
6. A boolean value 'validMove' (initialised to FALSE) changes to TRUE if any direction entered step 5. 
   If it is still FALSE after checking all the directions, that'd mean it never found the same color in any direction 
   making it an invalid move. Hence go back to step 1, otherwise player's turn is finished.
   
I could of used 'PossibleMoves()' to make a 2D array of the valid moves and just check if the user picks a move from 
there because 'PossibleMove()' checks the above conditions but I wanted to inform the user as to why their move isn't
valid. It creates repeated processes but it's worth it for the user experience.

##Niche 
###'modify' parameter for directions
If passed as true that means we should update the score and the board i.e. change the colors. If it's false, don't do either.

We need this because when we call 'PossibleMoves()', we don't want it to do the above for every single spot. This would
make it update the score and the board after checking every single spot, hence in it's code we pass into the directions 
false. The only time we pass in true is for the user's move.

###'SpotCapture()' vs 'NonSpotCapture()'
When capturing the spot i.e. an empty index, we only increment the current player's score.

where as

When capturing an index other than spot i.e. an index with the opposite color, we increment current player's score AND 
decrement other player's score.

###'struct data' as a global variable in lib.c
I initialised the 'struct data' as a global variable in lib.c because all the functions need something from the the
struct and so I didn't want to keep passing the struct or certain members of it for every single function.

###main .c
I wanted main.c to give a good idea to anyone who reads it as to what is going on from just the function calls. That's
why a lot of the work is done by lib.c and why main.c is short. Wanted it to be pseudocode.

