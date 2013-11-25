# giic.pl
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
