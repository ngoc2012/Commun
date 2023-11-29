from django.shortcuts import render
from django.http import JsonResponse

#def pong_game(request):
## Handle game logic and return the current game state
#game_state = {"paddle1_y": 50, "paddle2_y": 50, "ball_x": 100, "ball_y": 100}
#return JsonResponse(game_state)

players = ["user0"]

def home(request):
	return (render(request, 'index.html'));

def new_player(request):
    i = 1
    user_name = "user" + i;
    while (user_name in players):
        i += 1
        user_name = "user" + i
    return (JsonResponse({"name": user_name}));
