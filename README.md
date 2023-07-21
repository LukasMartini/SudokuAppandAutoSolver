# WaveCollapseSudokuSolver

Command List Reference:
- Ctrl+S: Saves the file.
- Ctrl+Shift+S: Saves the contents of the current table into a new file.
- Ctrl+O: Opens the file browser.
- Ctrl+R: Reloads the file list in the application itself.
- Ctrl+Shift+R: Resets all setValue flags, i.e. making all tiles editable again.
- Ctrl+E: Sets a value, making it un-editable.
- Ctrl+N: Creates a new file.

Hello,

This project was mostly as a fun way for me to improve with Qt6 and C++ in general, so it is a bit rough around the edges.
Notable changes I intend to work on when I have time are making the UI look nicer, commenting my code more, and improving the creator tools.
I would also like to note that calling the algorithm I created to auto-solve the sudoku puzzle is a wave function collapse algorithm is a bit of a stretch.
It's only run whenever there is a situation where the main solving algorithm doesn't work, specifically when there is a situation where none of the tiles that
do not currently have a single, correct value can be deduced to have one themselves based on the rest of the board. I.e., there are multiple solutions to the puzzle.
The name of the repository will have changed, as it really isn't a wave function collapse at all, but the name will not be refactored for the rest of the codebase.
It could be considered one because it quite literally takes one of the tiles, determined not by random seed but by the lowest number of possible values and proximity to
the first tile, decides it's value, then iteratively repeats that process in concert with the main solving algorithm until the table is complete. However, that feels like
an insult to procedural generation as a concept.

If you have any questions regarding the repository, please reach out to me at luke.herbert.martin@gmail.com and I'll try to get back to you.

Thanks,
Luke Martin.
