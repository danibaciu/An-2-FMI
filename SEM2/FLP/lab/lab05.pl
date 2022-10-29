% lab 5 - 243 flp
% recapitulare prolog




% num_aparitii/3

num_aparitii([], _, 0).
num_aparitii([X | Tail], X, Result) :- 
    num_aparitii(Tail, X, ResultTail),
    Result is ResultTail + 1.
num_aparitii([_ | Tail], X, Result) :- 
    num_aparitii(Tail, X, Result).





% lista_cifre_aux\2

lista_cifre_aux(X, [X]) :- X < 10.

lista_cifre_aux(N, [C | L]) :- 
    C is N mod 10, Nr is N div 10,
    lista_cifre_aux(Nr, L).

lista_cifre(X, L) :-
    lista_cifre_aux(X, Ltmp),
    reverse(Ltmp, L).





% ex3
% lista permutarilor circulare

permcirc([],[]).
permcirc([H | T], L) :-
    append(T, [H], L).

lpermcirc(L,L,[L]).
lpermcirc(L, M, [M | LP]) :- 
    permcirc(M, N),
    lpermcirc(L, N, LP).

% listpermcirc/2
listpermcirc(L, LP) :-
    permcirc(L, M),
    lpermcirc(L, M, LP).






% ex4


% a. elimina/3

elimina([], _, []).

elimina([X | Tail], X, Aux) :- 
    elimina(Tail, X, Aux).

elimina([H | T], X, [H | R]) :- 
    elimina(T, X, R).


% b. multime/2

multime([], []).

multime([H | T], R) :- 
    member(H, T), 
    multime(T, R).

multime([H | T], [H | R]) :-
    not(member(H, T)),
    multime(T, R).


% c. emult/1

emult(L) :- 
    length(L, N1),
    multime(L, LFD),
    length(LFD, N2),
    N1 =:= N2.








% ex 5

% intersectie/3

intersectie([], _, []).

intersectie([H | T], L, R) :-
    not(member(H, L)),
    intersectie(T, L, R).

intersectie([H | T], L, [H | R]) :-
    member(H, L),
    intersectie(T, L, R).





% diff/3
diff([], _, []).

diff([H | T], L, R) :-
    member(H, L),
    diff(T, L, R).

diff([H | T], L, [H | R]) :-
    not(member(H, L)),
    diff(T, L, R).




% prod_cart/3

elem_ori_mult(_, [], []).

elem_ori_mult(X, [H | T], [(X, H) | R]) :-
    elem_ori_mult(X, T, R).


prod_cart([], _, []).

prod_cart([H | T], L, R) :-
    elem_ori_mult(H, L, Res1),
    prod_cart(T, L, Res2),
    append(Res1, Res2, R).






% ex6

% nil = arbore vid
% arb/3
% arb(+RAD, +SUBARBST, +SUBARBDR)


% srd/2 

srd(nil, []).
srd(arb(R, S, D), L) :-
    srd(S, Ls), srd(D, Ld),
    append(Ls, [R | Ld], L).



rsd(nil, []).
rsd(arb(R, S, D), L) :-
    rsd(S, Ls), rsd(D, Ld),
    append([R | Ls], Ld, L).


sdr(nil, []).
sdr(arb(R, S, D), L) :-
    sdr(S, Ls), sdr(D, Ld),
    append(Ls, Ld, LTemp),
    append(LTemp, [R], L).


% frunze/2

frunze(nil, []).

frunze(arb(F, nil, nil), [F]).

frunze(arb(R, S, D), L) :-
    frunze(S, Ls),
    frunze(D, Ld),
    append(Ls, Ld, L).










