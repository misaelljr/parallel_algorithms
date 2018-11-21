% Imprime sucess ou error baseado no valor fornecido
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(simples_if_erlang) .

% execute, digitando no interpretador: 
%     simples_if_erlang:if_clause(2).
%
%     deve retornar "sucess"
% 

-module(simples_if_erlang). 
-export([if_clause/1]).

if_clause(N) -> 
	if
		N > 0 -> sucess;
		N < 0 -> error;
		true -> zero
	end.