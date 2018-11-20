% count to number input
-module(count). 
-export([count_until/2]).
-export([count_until1/1]).
-export([count_until2/2]).

count_until(Val, Max) when Val < Max ->
  io:fwrite("~p~n", [Val]),
  count_until(Val + 1, Max).
count_until2(_, Max) ->
  io:fwrite("~p~n", [Max]).
count_until1(Max) ->
  count_until(0, Max).