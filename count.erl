% Imprime número difitado até o valor máximo fornecido
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(count) .

% execute, digitando no interpretador: 
%     count:count_until(1,10).
%
%     deve retornar 7
%

-module(count). 
-export([count_until/2]).

count_until(Val, Max) when Val < Max ->
  io:fwrite("~p~n", [Val]),
  count_until(Val + 1, Max).