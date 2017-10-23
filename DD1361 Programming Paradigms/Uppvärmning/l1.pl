% Uppgift 1.
% Use cut on base cases to let prolog know that the unifications made cannot be changed, 
% which means that the values are locked so prolog does not have to evaluate these statements every time they
% are called upon.
fib(0,0) :- !.
fib(1,1) :- !.
fib(F, N) :-
	F > 1,
	F1 is F - 2,
	fib(F1, N1),
	F2 is F - 1,
	fib(F2, N2),
	N is N2 + N1.

% Uppgift 2.
% Use cut for the same reason as in fib, lock the values for each vowel.
vowel(97):- !.
vowel(101):- !.
vowel(105):- !.
vowel(111):- !.
vowel(117):- !.
vowel(229):- !.
vowel(228):- !.
vowel(246):- !.
vowel(121):- !.
vowel(117):- !.

% From text to rovarsprak: [H1|T1] becomes [H1,O,H1|T2].
% From rovarsprak to text: [H1,O,H1|T2] cuts off 3 characters from string if H1 is a consonant since we call the method recursively with the tail.
rovarsprak([], []).
rovarsprak([H1|T1], [H1,111,H1|T2]) :- %
	\+vowel(H1),
	rovarsprak(T1,T2).
rovarsprak([H1|T1], [H1|T2]) :-
	vowel(H1),
	rovarsprak(T1,T2).

% Uppgift 3.
medellangd(Text, AvgLen) :-
    wordsAndLetters(Text, Words, Letters),
    Words > 0, % Cannot divide by 0.
    AvgLen is Letters / Words,!.

% Empty list returns 0.
medellangd(_, 0).

% If there's only one element left in the list and it is a letter, add 1 to words and letters.
% This is because we cannot check whether the element after is a letter or not as we usually do.
wordsAndLetters([H], 1, 1) :-
	is_alpha(H).

% If the last element is not a letter, don't change words or letters.
wordsAndLetters([_], 0, 0).

% If H1 is a letter and H2 is not, add 1 to words and letters.
wordsAndLetters([H1, H2|T], Words, Letters) :-
is_alpha(H1),
\+is_alpha(H2),
wordsAndLetters([H2|T], W, L),
Letters is L + 1,
Words is W + 1,!.

% If H is a letter, add 1 to letters.
wordsAndLetters([H|T], Words, Letters) :-
	is_alpha(H),
	wordsAndLetters(T, Words, L),
	Letters is L + 1,!.

% If we call wordsAndLetters with a non-character as first element, remove it.
wordsAndLetters([_|T],Words,Letters) :-
wordsAndLetters(T,Words,Letters).

% Uppgift 4.
% Begin with dividing the input list into an uneven and an even list with listByIndex.
% Then call skyffla recursively with the even list and append the uneven lists from listByIndex.
skyffla([],[]) :- !.
skyffla(Lista, Skyfflad) :-
	listByIndex(Lista, Uneven, Even),
	skyffla(Even, EvenRes), % Keep shuffling the even list.
	append(Uneven,EvenRes,Skyfflad), !.

% Base cases.
listByIndex([],[],[]). % We're done if all lists are empty.
listByIndex([H1],[H1],[]). % If the input is a list with uneven length, one element will remain at the end so we set that last element to the last element of our uneven list.

% Create two lists: One with all the uneven indexes from input list and one with all even indexes.
listByIndex([H1,H2|T1], [H1|T2], [H2|T3]) :-
	listByIndex(T1,T2,T3).