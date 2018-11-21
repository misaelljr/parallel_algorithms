% Ordenação com o algoritmo Merge Sort
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(mergesort) .

% execute, digitando no interpretador: 
%     mergesort:mergesort([1,0,3,-2]).
%
%     deve retornar [-2,0,1,3]
%

-module(mergesort).
-export([mergesort/1]).

merge(A, []) -> A;
merge([], B) -> B;
merge([Ha|Ta], [Hb|Tb]) ->
  if
    Ha < Hb -> [Ha | merge(Ta, [Hb|Tb])];
    true -> [Hb | merge([Ha|Ta], Tb)]
  end.

mergesort([]) -> [];
mergesort([E]) -> [E];
mergesort(L) ->
  {A, B} = lists:split(trunc(length(L)/2), L),
  merge(mergesort(A), mergesort(B)).