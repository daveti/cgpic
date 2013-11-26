% gqicwt_d prolog file

% Dynamic function definition
:- dynamic(parent/2).

parent(bob,mary).
parent(jane,mary).
parent(mary,peter).
parent(paul,peter).
parent(peter,john).

anc(X, Y) :-
	parent(X, Y).

anc(X, Z) :-
	parent(X, Y),
	anc(Y, Z).
