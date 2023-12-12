from django.shortcuts import render
from django.http import JsonResponse
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import redirect
import time
from random import randrange

online_players = {}
playings_players = {}
games = {}
game_id = 0
HEIGHT = 400
WIDTH = 800
PADDLE_WIDTH = 10
PADDLE_HEIGHT = 60
RADIUS = 10
PADDLE_VITESSE = 5
PADDLE_DISTANCE = 20

def lobby(request):
	return (render(request, 'lobby.html'))

def pong(request):
	return (render(request, 'pong.html'))

def new_player(request):
    i = 0
    user_name = "user" + str(i)
    while (user_name in online_players.keys()):
        i += 1
        user_name = "user" + str(i)
    online_players[user_name] = {
            "online": time.time(),
            "invitations": {},
            "accepted": -1
            }
    #print(online_players)
    return (HttpResponse(user_name))
