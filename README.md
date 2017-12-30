# Groggle
Boggle clone with custom boards, custom board sizes (eventually), automatic board solving and more!
Slowly turning into an all-in-one Boggle utility

# TODO
- Find new allowed Boggle words list (Partially fixed, still need to remove roman numerals)
- Add actual game functionality
- Add rules
- Accept command line arguments for custom boards
- Maybe change dice distributions, figure out how to generate dice for larger board sizes
- Switch io stuff to ncurses for better GUI and better portability
- Add double letter cubes, used in Big Boggle. Make Qu cube more modular
- Test against other Boggle solvers using the same dictionary to find bugs (See Issue #1)

# COMPLETED
- Dictionary
- Board generator using default Boggle distribution
- Board solver (Incredibly efficient with new data structure)
- Input and solve custom boards
- Search for words in dictionary
- Add custom words to dictionary

# Changeloggle
- 10/23 Initial commit, with board generator and solver
- 11/19 Add custom board input, dictionary tools
- 12/30 Replace hash table with 26ary tree, which results in orders of magnitude speedup for larger boards
