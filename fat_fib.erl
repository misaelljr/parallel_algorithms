% Calcula fatorial e fibonacci
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(fat_fib) .

% execute, digitando no interpretador: 
%     fat_fib:another_factorial(5).
%
%     deve retornar 120
%
%     fat_fib:another_fib(13).
%
%     deve retornar 233

-module(fat_fib).
-export([another_factorial/1]).
-export([another_fib/1]).

another_factorial(0) -> 1;
another_factorial(N) -> N * another_factorial(N-1).

another_fib(0) -> 1;
another_fib(1) -> 1;
another_fib(N) -> another_fib(N-1) + another_fib(N-2).