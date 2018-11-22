% Calcula fibonacci
%
%Alunos: 
%-- Misael Costa Júnior (NUSP 9254469)
%-- João Choma Neto (NUSP 10633606)
%-- Felipe Torres (NUSP 9253670)
%-- Guilherme Milan Santos (NUSP 9012966)
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(fib) .

% execute, digitando no interpretador: 
%
%     fib:comp_fib(5).
%
%     deve retornar [1,1,2,3,5]

-module(fib).
-export([comp_fib/1]).
-export([gera_lista/1]).

%%computa elementos de fibonacci
comp_fib(0) -> 1; %%caso base 1
comp_fib(1) -> 1; %%caso base 2
comp_fib(N) -> comp_fib(N-1) + comp_fib(N-2). %%computa para N

%%gera lista com elementos de fibonacci
gera_lista(N) -> 
	[comp_fib(List) || List <- %%atribuição
	lists:seq(0,N-1)]. %%monta uma sequência de 0 até N-1