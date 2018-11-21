% Imprime um Hello World
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(helloworld).

% execute, digitando no interpretador: 
%     helloworld:start().
%
%     deve retornar "Hello World"
%

-module(helloworld). 
-export([start/0]). 

start() -> io:fwrite("Hello World!\n").