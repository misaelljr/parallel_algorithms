% Determina o tamanho de uma lista.
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(list_length) .

% execute, digitando no interpretador: 
%     list_length:list_length([1,2,3,4,5,6,7]).
%
%     deve retornar 7
%

-module(list_length).
-export([list_length/1]).

list_length([]) -> 0;
list_length([First | Rest]) -> 1 + list_length(Rest).
