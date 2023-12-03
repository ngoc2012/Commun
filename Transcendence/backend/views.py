from django.shortcuts import render
from django.http import JsonResponse
from django.http import HttpResponse
from django.http import HttpResponseNotFound
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import redirect
import time

online_players = {}
games = {}
game_id = 0

def index(request):
	return (render(request, 'index.html'))

def home(request):
	return (render(request, 'home.html'))

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
            "invitations": {},
            "accepted": -1
            }
    print(online_players)
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
    print(request.POST)
    user = request.POST['user']
    users = list(online_players.keys())
    #print(user)
    print(users)
    if user in users:
        online_players[user]["online"] = time.time()
        user_info = online_players[user]
        user_info["invitations"] = [v for k, v in online_players[user]["invitations"].items()]
        print(user_info)
        return (JsonResponse({"user_info": user_info, "online_players_list": users}))
    #print(online_players)
    return (JsonResponse({"user_info": {}, "online_players_list": users}))

@csrf_exempt
def invite(request):
    #print(online_players)
    #print(request.POST)
    global game_id
    global online_players
    global games
    players = request.POST.getlist('players[]')
    print(players)
    for user in players:
        if (user not in online_players.keys()):
            #print(user)
            #print(online_players.keys())
            return HttpResponseNotFound("Player " + user + " is not online.")
    game_id += 1
    games[game_id] = {
        "id": game_id,
        "game": request.POST['game'],
        "status": "waiting",
        "players": players,
        "host": request.POST['host'],
        "accepted": [request.POST['host']]
        }
    print(games)
    for user in players:
        online_players[user]['invitations'][game_id] = games[game_id]
    return (JsonResponse({"game_id": game_id}))

@csrf_exempt
def accept_invitation(request):
    global games
    global online_players
    print(request.POST)
    g_id = int(request.POST['game_id'])
    print(games)
    print(games[g_id])
    if (g_id not in games.keys()):
        print("Game " + str(g_id) + " was not found.")
        return HttpResponseNotFound("Game " + str(g_id) + " was not found.")
    user = request.POST['user']
    if (user not in games[g_id]["players"]):
        print("Player " + user + " was not found in the game.")
        return HttpResponseNotFound("Player " + user + " was not found in the game.")
    if (online_players[user]['accepted'] != -1):
        print("Player " + user + " was in another game.")
        return HttpResponseNotFound("Player " + user + " was in another game.")
    online_players[user]["accepted"] = g_id
    if (user not in games[g_id]["accepted"]):
        games[g_id]["accepted"].append(user)
        if (len(games[g_id]["accepted"]) == len(games[g_id]["players"])):
            games[g_id]["status"] = "playing"
    return (JsonResponse({"game": games[g_id]['game']}))

@csrf_exempt
def cancel_invitation(request):
    global games
    print(request.POST)
    g_id = int(request.POST['game_id'])
    if (g_id not in games.keys()):
        return HttpResponseNotFound("Game " + str(g_id) + " was not found.")
    user = request.POST['user']
    if (user not in games[g_id]["players"]):
        return HttpResponseNotFound("Player " + user + " was not found in the game.")
    if (online_players[user]["accepted"] == g_id):
        online_players[user]["accepted"] = -1
    for user in games[g_id]["players"]:
        if g_id in online_players[user]["invitations"].keys():
            online_players[user]["invitations"].pop(g_id)
    games.pop(g_id)
    return (HttpResponse("canceled"))

@csrf_exempt
def check_game_status(request):
    global games
    #print(request.POST)
    g_id = int(request.POST['game_id'])
    user = request.POST['user']
    users = list(online_players.keys())
    if user in users:
        online_players[user]["online"] = time.time()
    if (g_id not in games.keys()):
        return (HttpResponse("canceled"))
    return (JsonResponse(games[g_id]))
