% quick sort in Erlang
-module(quick_sort_erlang). 
-export([qsort/1]).

qsort([]) -> [];
qsort([Single]) -> [Single];
qsort([Pivot|T]) ->
       qsort([X || X <- T, X < Pivot])
       ++ [Pivot] ++
       qsort([X || X <- T, X >= Pivot]).