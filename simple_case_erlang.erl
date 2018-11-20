% simple case clause in Erlange
-module(simple_case_erlang). 
-export([case_clause/1]).

case_clause(String) ->
	case String of 
		"dog" -> cachorro;
		"cat" -> gato;
		_ -> something_else
	end.

