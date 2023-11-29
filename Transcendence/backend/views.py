from django.shortcuts import render
from django.http import JsonResponse
#from django.views.decorators.csrf import csrf_exempt

#def pong_game(request):
## Handle game logic and return the current game state
#game_state = {"paddle1_y": 50, "paddle2_y": 50, "ball_x": 100, "ball_y": 100}
#return JsonResponse(game_state)

players = ["default"]

def home(request):
	return (render(request, 'index.html'));

#@csrf_exempt
def new_player(request):
    i = 0
    user_name = "user" + str(i)
    while (user_name in players):
        i += 1
        user_name = "user" + str(i)
    players.append(user_name);
    return (JsonResponse({"name": user_name}));
