from django.shortcuts import render
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import redirect
import time

#def pong_game(request):
## Handle game logic and return the current game state
#game_state = {"paddle1_y": 50, "paddle2_y": 50, "ball_x": 100, "ball_y": 100}
#return JsonResponse(game_state)

players = {}

def index(request):
	return (render(request, 'index.html'));

def home(request):
    return (redirect("index"));

def login(request):
	return (render(request, 'login.html'));

def pong(request):
	return (render(request, 'pong.html'));

#@csrf_exempt
def new_player(request):
    i = 0
    user_name = "user" + str(i)
    while (user_name in players.keys()):
        i += 1
        user_name = "user" + str(i)
    players[user_name] = {"heart_beat": time.time()};
    return (JsonResponse({"user": user_name}));

@csrf_exempt
def players_list(request): 
    users = list(players.keys())
    for user in users:
        if time.time() - players[user]["heart_beat"] > 2:
            players.pop(user)
    user = request.POST['user'];
    if user in users:
        players[user]["heart_beat"] = time.time();
    return (JsonResponse({"players": list(players.keys())}));
