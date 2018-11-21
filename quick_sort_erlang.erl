% Ordenação com o algoritmo Quick Sort
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(quick_sort_erlang) .

% execute, digitando no interpretador: 
%     quick_sort_erlang:qsort([1,0,3,-2]).
%
%     deve retornar [-2,0,1,3]
%

-module(quick_sort_erlang). 
-export([qsort/1]).

qsort([]) -> [];
qsort([Single]) -> [Single];
qsort([Pivot|T]) ->
       qsort([X || X <- T, X < Pivot])++ %elementos menores que o pivot
       [Pivot] ++
       qsort([X || X <- T, X >= Pivot]). %%elementos maiores ou igual ao pivot