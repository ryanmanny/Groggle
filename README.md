# Groggle
Boggle clone with custom boards, custom board sizes (eventually), automatic board solving and more!
Slowly turning into an all-in-one Boggle utility

# TODO
- Find new allowed Boggle words list (or remove crummy words like roman numerals and words with apostrophes)
- Add actual game functionality
- Add rules
- Accept command line arguments for custom boards (too fancy)
- Maybe change dice distributions, figure out how to generate dice for larger board sizes
- Switch io stuff to ncurses for better GUI and better portability

# COMPLETED
- Dictionary
- Board generator using default Boggle distribution
- Board solver (fairly efficient, takes about 3 seconds, ONLY .2 seconds on Linux (thanks tail recursion I guess))
- Input and solve custom boards
- Search for words in dictionary
- Add custom words to dictionary

# Changeloggle
- 10/23 Initial commit, with board generator and solver
- 11/19 Add custom board input, dictionary tools
