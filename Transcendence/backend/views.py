from django.shortcuts import render
from django.http import JsonResponse
from django.http import HttpResponse
from django.http import HttpResponseNotFound
#from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import redirect
import time

online_players = {}
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
    while (user_name in online_players.keys()):
        i += 1
        user_name = "user" + str(i)
    online_players[user_name] = {
            "online": time.time(),
            "invitations": [],
            "accepted": -1
            }
    return (JsonResponse({"user": user_name}))

def check_all_users_online():
    users = list(online_players.keys())
    for user in users:
        if time.time() - online_players[user]["online"] > 3:
            online_players.pop(user)

@csrf_exempt
def online_players_list(request): 
    #print(games)
    check_all_users_online()
    user = request.POST['user']
    users = list(online_players.keys())
    invitations = []
    if user in users:
        online_players[user]["online"] = time.time()
    return (JsonResponse({"user_status": online_players[user], "online_players_list": users}))

def invite(request):
    for user in request.POST['players']
        if (user not in online_players.keys()):
            return HttpResponseNotFound("Player " + user + " is not online.")

    game_id += 1
    for user in request.POST['players']
        online_players[user]['invitations'].append(game_id)

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
        return HttpResponseNotFound("Game " + str(g_id) + " was not found.")
    user = request.POST['user']
    if (user not in games[g_id]["online_players"])
        return HttpResponseNotFound("Player " + user + " was not found in the game.")
    if (online_players[user]['accepted'] != 1)
        return HttpResponseNotFound("Player " + user + " was in another game.")
    if (user not in games[g_id]["accepted"])
        games[g_id]["accepted"].append(user)
    return (JsonResponse({"game": games[g_id]['game']}))

def cancel_invitation(request):
    g_id = request.POST['game_id']
    if (g_id not in games.keys())
        return HttpResponseNotFound("Game " + str(g_id) + " was not found.")
    user = request.POST['user']
    if (user not in games[g_id]["players"])
        return HttpResponseNotFound("Player " + user + " was not found in the game.")
    games.pop(g_id)
    return (HttpResponse("canceled"))

def check_game_status(request):
    g_id = request.POST['game_id']
    if (g_id not in games.keys())
        return HttpResponseNotFound("Game " + str(g_id) + " was not found or canceled.")
    return (JsonResponse(games[g_id]))
