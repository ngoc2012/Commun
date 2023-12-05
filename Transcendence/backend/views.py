from django.shortcuts import render
from django.http import JsonResponse
from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from django.shortcuts import redirect
import time

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
    #print(request.POST)
    user = request.POST['user']
    users = list(online_players.keys())
    #print(user)
    #print(users)
    if user in users:
        online_players[user]["online"] = time.time()
        return (JsonResponse({
            "invitations": [v for k, v in online_players[user]["invitations"].items()],
            "online_players_list": users}))
    #print(online_players)
    return (JsonResponse({"invitations": [], "online_players_list": users}))

@csrf_exempt
def pong_state(request):
    #print(online_players)
    global online_players
    global games
    global WIDTH, HEIGHT, PADDLE_WIDTH, PADDLE_HEIGHT
    g_id = int(request.POST['game_id'])
    if (g_id not in games.keys()):
        return HttpResponse("Error: Game " + str(g_id) + " was not found.")
    user = request.POST['user']
    if user not in games[g_id]["players"]:
        return HttpResponse("Error: Player " + user + " was not found in the game.")
    g = games[g_id]
    i = g["update"]["order"][user]
    if g["update"][i] == 1:
        return HttpResponse("wait")
    to_do = request.POST['do']
    if (to_do == "up" && d["data"]["position"][i] < HEIGHT - PADDLE_HEIGHT)
		d["data"]["position"][i] += PADDLE_VITESSE;
    else if (to_do == "down" && d["data"]["position"][i] > 0)
		d["data"]["position"][i] -= PADDLE_VITESSE;
    g["update"][i] = 1
    if sum(g["update"]) == g["n"]:
        g["update"] = [0 for i in range(len(players))]
        g["ball_x"] += g["dx"];
        g["ball_y"] += g["dy"];
        # Bounce off the top and bottom walls
        if (g["ball_y"] - RADIUS < 0 || g["ball_y"] + RADIUS > HEIGHT)
	    	g["dy"] = -g["dy"];
	    # Bounce off paddle
	    if (g["ball_x"] - RADIUS < this.leftPaddle.x + this.leftPaddle.width &&
	        g["ball_x"] + RADIUS > this.leftPaddle.x + this.leftPaddle.width &&
	    	g["ball_y"] > this.leftPaddle.y - HEIGHT / 2 &&
	    	g["ball_y"] < this.leftPaddle.y + HEIGHT / 2)
	    	g["dx"] = -g["dx"];
	    # Check for game over
	    if (g["ball_x"] - RADIUS < 0 || g["ball_x"] + RADIUS > WIDTH)
	    	this.resetGame();
    return (JsonResponse({"ball": [g["ball_x"], g["ball_y"]], "postion": d["data"]["position"]}))

@csrf_exempt
def invite(request):
    #print(online_players)
    #print(request.POST)
    global game_id
    global online_players
    global games
    global WIDTH, HEIGHT, PADDLE_WIDTH, PADDLE_HEIGHT
    players = request.POST.getlist('players[]')
    print(players)
    for user in players:
        if (user not in online_players.keys()):
            #print(user)
            #print(online_players.keys())
            return HttpResponse("Player " + user + " is not online.")
    game_id += 1
    games[game_id] = {
        "id": game_id,
        "game": request.POST['game'],
        "status": "waiting",
        "players": players,
        "n": len(players),
        "order": {},
        "host": request.POST['host'],
        "accepted": [request.POST['host']],
        "update": [0 for i in range(len(players))],
        "x": [0 for i in range(len(players))],
        "data": 
        {
            "ball_x": -WIDTH / 2 + PADDLE_WIDTH,
            "ball_y": -HEIGHT / 2,
            "dx": 5,
            "dy": 5,
            "position": [-PADDLE_HEIGHT / 2 for i in range(len(players))],
            "side": [i % 2 for i in range(len(players))]
            "update": [0 for i in range(len(players))],
        }
    }
    g = games[g_id]
    print(games)
    for i, user in enumerate(players):
        if (i % 2 == 0)
            g["x"][i] = i / 2 * PADDLE_DISTANCE
        else
            g["x"][i] = WIDTH - (int(i / 2) * PADDLE_DISTANCE - PADDLE_WIDTH)
        g["order"][user] = i
        online_players[user]['invitations'][game_id] = g
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
        return HttpResponse("Game " + str(g_id) + " was not found.")
    user = request.POST['user']
    if (user not in games[g_id]["players"]):
        print("Player " + user + " was not found in the game.")
        return HttpResponse("Player " + user + " was not found in the game.")
    if (online_players[user]['accepted'] != -1):
        print("Player " + user + " was in another game.")
        return HttpResponse("Player " + user + " was in another game.")
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
        return HttpResponse("Game " + str(g_id) + " was not found.")
    user = request.POST['user']
    if (user not in games[g_id]["players"]):
        return HttpResponse("Player " + user + " was not found in the game.")
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
