from django.shortcuts import render
from django.http import JsonResponse

games_list = {{1, 2}, {3, 4}}
players_list = {"haha", "hehe"}
width = 800
height = 400
game_state = {"paddle1_y": 50, "paddle2_y": 50, "ball_x": 100, "ball_y": 100}

def pong_game(request):
	# Handle game logic and return the current game state
	return JsonResponse(game_state)

def state(request):
	global players_list
	return JsonResponse(players_list);

def action(request):
	global players_list
	return JsonResponse(players_list);

def get_games_list(request):
	global games_list
	return JsonResponse(games_list);

def get_players_list(request):
	global players_list
	return JsonResponse(players_list);
