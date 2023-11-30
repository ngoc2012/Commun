from django.shortcuts import render
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import redirect
import datetime

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
    while (user_name in players):
        i += 1
        user_name = "user" + str(i)
    players[user_name] = {"user": user_name, "heart_beat": datetime.datetime.now()};
    return (JsonResponse({"user": user_name}));

@csrf_exempt
def players_list(request):
    print(request.POST['user'])
    players
    return (JsonResponse({"players": [i['user'] for i in players]}));
