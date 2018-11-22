-module(quick_sort).
-export([quick/1]).

quick(X) ->
        List = [2,3,1,4,5,9,8,7,0],
        if
                X == 1 ->
                        io:format("~w~n", [sortA(List)]);
                X == 2 ->
                        io:format("~w~n", [sortD(List)]);
                true ->
                        io:format("ERROR, enter 1 - ASC or 2 - DESC~n")
        end.


sortA([Pivot|T]) ->
        sortA([X || X <- T, X < Pivot]) ++
        [Pivot] ++
        sortA([X || X <- T, X >= Pivot]);

sortA([]) -> [].

sortD([Pivot|T]) ->
        sortD([X || X <- T, X > Pivot]) ++
        [Pivot] ++
        sortD([X || X <- T, X =< Pivot]);

sortD([]) -> [].
