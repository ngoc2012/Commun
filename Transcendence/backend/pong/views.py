from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from game.models import RoomsModel, PlayersModel, PlayerRoomModel

# Create your views here.
def index(request):
    return render(request, "pong.html")

@csrf_exempt
def state(request):
    if 'action' not in request.POST:
        return (HttpResponse("Error: No action!"))
    if 'game_id' not in request.POST:
        return (HttpResponse("Error: No game id!"))
    if 'login' not in request.POST or request.POST['login'] == "":
        return (HttpResponse("Error: No login!"))
    player = PlayersModel.objects.get(login=request.POST['login'])
    if not RoomsModel.objects.filter(id=request.POST['game_id']).exists():
        return (HttpResponse("Error: Room with id '" + request.POST['game_id'] + "' does not exist!"))
    room = RoomsModel.objects.get(id=request.POST['game_id'])
    if not PlayerRoomModel.objects.filter(player=player,room=room).exists():
        return (HttpResponse("Error: Player is not playing this game!"))
    player_room = PlayerRoomModel.objects.get(player=player,room=room)
    if request.POST['action'] == 'up':
        player_room.y += 
