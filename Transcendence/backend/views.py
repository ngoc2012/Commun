from django.shortcuts import render
from django.http import JsonResponse

global games_list = {1, 2, 3, 4}
global players_list = {"haha", "hehe"}

def pong_game(request):
	# Handle game logic and return the current game state
	game_state = {"paddle1_y": 50, "paddle2_y": 50, "ball_x": 100, "ball_y": 100}
	return JsonResponse(game_state)

def get_games_list(request):
	return JsonResponse(games_list);

def get_players_list(request):
	return JsonResponse(players_list);
