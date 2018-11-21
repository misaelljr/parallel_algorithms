% Envio de mensagem distribuída
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(example_message_distrib_erlang) .

% execute, digitando no interpretador: 
%	  Pid = spawn(fun example_message_distrib_erlang:loop/0).	
%     Pid ! "casa".
%
%     deve retornar: 
%     "house"
% 	  "casa"
%

-module(example_message_distrib_erlang).
-export([loop/0]).

loop() ->

	receive
		"casa" ->
		io:format("house~n"),
		loop();
		
		"blanca" ->
		io:format("white~n"),
		loop();
		
		_ ->
		io:format("I don't understand.~n"),
		loop()
	end.