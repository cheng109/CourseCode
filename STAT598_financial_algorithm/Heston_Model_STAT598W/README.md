# Heston_Model_STAT598W
Final project Spring2015

Instructor: Sveinn Olafsson


The goal of this project is to implement a C++ library to price a number of nancial derivatives using Monte Carlo
simulation, under the Heston stochastic volatility model. The library should also be able to calibrate the model
parameters to observed option prices.

This shall result in a report at the end of the semester, as well as an in-class presentation. The report should include
an introduction (Heston model overview, pros/cons, etc.), numerical methods overview (a description of your Monte
Carlo methodology), numerical results, and discussion on your ndings (implementation issues, accuracy, eciency,
improvements). The report should also contain the interface for your library, i.e. a \user manual" with a description
of each function and how to use it. The private section (implementation) should be included in an appendix.

For data structures and algorithms, you should use STL as much as possible and take advantage of the STL algorithms.
For data visualization you are allowed to use Matlab (or any other software). It is your responsibility to design the
library and class hierarchy (you may get ideas from [6] and similar references), but at a minimum it should be able to
perform the following tasks:

**(1) Use Monte Carlo simulation to price European options (puts, calls, as well as user dened payo function).**

**(2) To simulate the Heston process you should use a Milstein scheme, as well as the more advanced QE-scheme found
in [1].**

**(3) Use Monte Carlo simulation to price path-dependent options, in particular barrier options (knock-in, knock-out).**

**(4) Calibrate the model parameters using vanilla option quotes from e.g. Bloomberg. Note that there exists a semi-
closed form formula for call option prices under the Heston model ([2],[5]) (start by making sure your algorithm
works using \articial" option prices generated by your model for some preselected parameter values).**

**(5) Compute implied volatilities and the most important Greeks.**

**(6) Price American/Bermudan options using Monte Carlo simulation. You can use either stochastic meshes or
least-squares Monte Carlo (see [4] and references therein).**

**(7) For all of the above, you should consider improvements to the traditional Monte Carlo schemes, e.g. variance
reduction techniques, and improvements that are based on the fact that your model is Heston.**

##Project milestones:

1. April 9th. In-class discussion on how you intend to approach each part of the project. This is also the time to
raise any questions or concerns you may have.
2. TBD In-class project presentation.
3. TBD Final report due.

##References

1. L. Andersen. Ecient simulation of the Heston stochastic volatility model, Bank of America Securities, 2006.
2. P. Carr and D.B. Madan, Option valuation using the fast Fourier transform, Journal of Computational Finance
2(4), 1999.
3. D. Duy, Introduction to C++ for nancial engineers: An Object-Oriented Approach, Wiley, December 2006.
4. P. Glasserman, Monte Carlo methods in nancial engineering, Springer, 2004.
5. S. Heston, A closed-form solution for options with stochastic volatility with applications to bond and currency
options, The Review of Financial Studies, 6(2), 1993.
6. M. Joshi, C++ design patterns and derivatives pricing, Second edition, Cambridge University Press, 2008.