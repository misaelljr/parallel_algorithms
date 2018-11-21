% Soma de itens acumulativa dada uma lista
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(sum_listitem_erlang) .

% execute, digitando no interpretador: 
%     sum_listitem_erlang:sum_items([1,2,3]).
%
%     deve retornar 6
%

-module(sum_listitem_erlang). 
-export([sum_items/2]).

sum_items([H|T], Acc) -> 
   sum_items(T, H + Acc); 

sum_items([], Acc) ->
   Acc.
	

