from django.shortcuts import render
from django.http import JsonResponse
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import redirect
import time

players = {}
games = {}
game_id = 0

def index(request):
	return (render(request, 'index.html'))

def home(request):
    return (redirect("index"))

def login(request):
	return (render(request, 'login.html'))

def pong(request):
	return (render(request, 'pong.html'))

def new_player(request):
    i = 0
    user_name = "user" + str(i)
    while (user_name in players.keys()):
        i += 1
        user_name = "user" + str(i)
    players[user_name] = {
            "heart_beat": time.time(),
            "invitations": [];
            "acceped": -1;
            }
    return (JsonResponse({"user": user_name}))

def check_all_users_heart_beat():
    users = list(players.keys())
    for user in users:
        if time.time() - players[user]["heart_beat"] > 3:
            players.pop(user)

@csrf_exempt
def players_list(request): 
    #print(games)
    check_all_users_heart_beat()
    user = request.POST['user']
    users = list(players.keys())
    invitations = []
    if user in users:
        players[user]["heart_beat"] = time.time()
        g_ids = list(games.keys())
    return (JsonResponse({"user_status": players[user], "players_list": list(players.keys())}))

def invite(request):
    game_id += 1
    games[game_id] = {
        "id": game_id,
        "game": request.POST['game'],
        "status": "waiting",
        "players": request.POST['players'],
        "host": request.POST['host'],
        "accepted": [request.POST['host']]
        }
    return (JsonResponse({"game_id": game_id}))

def accept_invitation(request):
    g_id = request.POST['game_id']
    if (g_id not in games.keys())
        return (JsonResponse({"status": "Error: game id " + str(g_id) + " is not found"}))
    user = request.POST['user']
    if (user not in games[g_id]["players"])
        return (JsonResponse({"status": "Error: player " + user +  " is not found"}))
    if (user not in games[g_id]["accepted"])
        games[g_id]["accepted"].append(user)
    return (JsonResponse({"status": "accepted"}))


def cancel_invitation(request):
    g_id = request.POST['game_id']
    if (g_id not in games.keys())
        return (JsonResponse({"status": "Error: game id " + str(g_id) + " is not found"}))
    user = request.POST['user']
    if (user not in games[g_id]["players"])
        return (JsonResponse({"status": "Error: player " + user +  " is not found"}))
    games.pop(g_id)
    return (JsonResponse({"status": "canceled"}))

def check_game_status(request):
    g_id = request.POST['game_id']
    if (g_id not in games.keys())
        return (JsonResponse({"status": "canceled"}))
    if (len(game_id[g_id]['players']) == len(game_id[g_id]['accepted']))
        return (JsonResponse({"status": "ready"}))
    return (JsonResponse({"status": "waiting"}))
