Genetic Template

To build the project you *need* to have GNUmake which is a shame but sadly
I did not think to hard when making this project.

This is a sample project where I used a genetic algorithm that barely works.
The main project is a "decoder" where it breaks the "Mastermind" on any
difficulty and on any possible password length. Because it implements a O(n^3)
algorithm it was simply more efficient to use C++ to write it. I simply created
a decoder but did not provide a main method to run. There are still many steps
before one can actually run it. The decoder actually has two methods, the *algorithm*
and the *tester*. The tester actually implements the algorithm to till it finds the password
for every single possible password. The algorithm simply takes a game state that you create
by playing rounds using one of its member functions. The genetic algorithm was used to attempt
to minimize the number of moves needed to solve passwords on average.

