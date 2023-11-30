from django.shortcuts import render
from django.http import JsonResponse
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import redirect
import time

#def pong_game(request):
## Handle game logic and return the current game state
#game_state = {"paddle1_y": 50, "paddle2_y": 50, "ball_x": 100, "ball_y": 100}
#return JsonResponse(game_state)

players = {}
games = {}
game_id = 0

def index(request):
	return (render(request, 'index.html'));

def home(request):
    return (redirect("index"));

def login(request):
	return (render(request, 'login.html'));

def pong(request):
	return (render(request, 'pong.html'));

def invite(request):
    game_id += 1
    games[game_id] = {
        "game": request.POST['game'],
        "start": False,
        "players": request.POST['players'],
        "admission": [request.POST['user']]
        }
    return (JsonResponse({"game_id": game_id}));

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
    print(games)
    users = list(players.keys())
    for user in users:
        if time.time() - players[user]["heart_beat"] > 3:
            players.pop(user)
    user = request.POST['user'];
    users = list(players.keys())
    if user in users:
        players[user]["heart_beat"] = time.time();
    return (JsonResponse({"players": list(players.keys())}));
