% Imprime um elemento traduzido baseado na String fornecida
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(simple_case_erlang) .

% execute, digitando no interpretador: 
%     simple_case_erlang:case_clause("dog").
%
%     deve retornar "cachorro"
%

-module(simple_case_erlang). 
-export([case_clause/1]).

case_clause(String) ->
	case String of 
		"dog" -> cachorro;
		"cat" -> gato;
		_ -> something_else
	end.

