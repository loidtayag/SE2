#Global struct
So it turns out most of functions need something from the instance 'struct data Data' and  so made it a global variable so that I don't have to keep passing it back and forth.

Readability worsens if I pass struct every time I need it and if I only pass in the specific variables needed it would not become more memory efficient because it already has memory reserved for the struct and we pass by reference so makes no difference.

#Checking validity of move
Spot: the index in the 2D array where the player wishes to place a dice

1. Check if spot is empty, if not ask user for another move until an empty spot is chosen.
2. Loop through chosen direction until the same color is reached WHILE keeping a 'jumpCounter' that keeps track of how many die we had to check to get the same color.
(If a 'current_color' isn't found skip to step 4)
3. Return to the spot and loop through the same direction for 'jumpCounter' amount of times while turning every dice into the 'current_color'.
4. Repeat steps 2 - 3  for rest of directions.

A boolean value 'invalid' (intialised to TRUE) changes to FALSE if any direction enters step 3. If it is still FALSE after checking all the directions, that'd mean it's an invalid move hence ask user for another move and go back to step 1 otherwise end the turn.