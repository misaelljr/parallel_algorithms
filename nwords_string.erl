% measure number of words in a string
-module(count). 
-export([count_n/1]).

count_n([]) -> 0;
count_n(String) -> [_ | Tail] = String, 1 + count_n(Tail).