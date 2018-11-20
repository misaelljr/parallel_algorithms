% example of sum of item on list with erlang
-module(sum_listitem_erlang). 
-export([sum_items/2]).

sum_items([H|T], Acc) -> 
   sum_items(T, H + Acc); 

sum_items([], Acc) ->
   Acc.
	

