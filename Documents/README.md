# Checking validity of move
Spot: the index in the 2D array i.e. 'board' where the player wishes to place a dice

0. Ask for spot.
1. Check if spot is empty, if not ask user for another move until an empty spot is chosen.
2. Loop through any direction until the same color is reached WHILE keeping a 'jumpCounter' that keeps track of how many die we had to check to get to the furthest dice that was the same color. (If a 'current_color' isn't found skip to step 4)
3. Return to the spot and loop through the same direction for 'jumpCounter' amount of times while turning every dice into the 'current_color'.
4. Repeat steps 2 - 3  for rest of directions.
5. A boolean value 'validMove' (intialised to FALSE) changes to TRUE if any direction entered step 3. If it is still FALSE after checking all the directions, that'd mean it never found the same color in any direction making it an invalid move. Hence go back to step 0, otherwise player's turn is finished.
