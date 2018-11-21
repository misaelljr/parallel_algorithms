% Envio de mensagem sincronizada
%
% abra interpretador, digitando na linha de comando: erl
% compile, digitando no interpretador: c(example_message_sync_erlang) .

% execute, digitando no interpretador: 
%	  Translator = spawn(fun example_message_sync_erlang:loop/0).	
%     example_message_sync_erlang:loop(Translator, "blanca").
%
%     deve retornar: 
%     "white"
%

-module(example_message_sync_erlang).
-export([loop/0]).
-export([translate/2]).

loop() ->
	receive
		{From, "casa"} ->
			From ! "house",
			loop();
		
		{From, "blanca"} ->
			From ! "white",
			loop();
		
		{From, _} ->
			From ! "I don't understand.",
			loop()
		
	end.

translate(To, Word) ->
	To ! {self(), Word},
	receive
		Translation -> Translation
	end.

