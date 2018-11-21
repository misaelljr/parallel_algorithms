% Imprime número de elementos de uma String
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(nwords_string) .

% execute, digitando no interpretador: 
%     nwords_string:count_words("Hei").
%
%     deve retornar 3
%

-module(nwords_string). 
-export([count_words/1]).

count_words([]) -> 0;
count_words(String) -> [_ | Tail] = String, 1 + count_words(Tail).