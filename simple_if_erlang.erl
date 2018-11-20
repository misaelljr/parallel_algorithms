% simple if clause in Erlange
-module(simples_if_erlang). 
-export([if_clause/1]).

if_clause(N) -> 
	if
		N > 0 -> sucess;
		N < 0 -> error;
		true -> zero
	end.