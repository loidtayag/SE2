# Global struct vs Passing struct
Making it a global variable in lib.c or passing by reference from main.c forces me to type 'Data.whatever' everytime, this worsens the readability of lib.c.

Instead I've decided to make it a global varaible in lib.c but typedef every struct member. Since most of the functions need something from the struct, passing by reference is too much extra work and I want the main.c to be simple and clean. The lib files will store all the complex declarations and functions. 

# Checking validity of move
Spot: the index in the 2D array where the player wishes to place a dice

1. Check if spot is empty, if not ask user for another move until an empty spot is chosen.
2. Loop through chosen direction until the same color is reached WHILE keeping a 'jumpCounter' that keeps track of how many die we had to check to get the same color.
(If a 'current_color' isn't found skip to step 4)
3. Return to the spot and loop through the same direction for 'jumpCounter' amount of times while turning every dice into the 'current_color'.
4. Repeat steps 2 - 3  for rest of directions.

A boolean value 'invalid' (intialised to TRUE) changes to FALSE if any direction enters step 3. If it is still FALSE after checking all the directions, that'd mean it's an invalid move hence ask user for another move and go back to step 1 otherwise end the turn.
