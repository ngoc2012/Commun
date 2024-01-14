from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from .models import RoomsModel, PlayersModel, PlayerRoomModel

from pong.data import pong_data

@csrf_exempt
def new_game(request):
    if 'game' not in request.POST:
        return (HttpResponse("Error: No game!"))
    if 'login' not in request.POST:
        return (HttpResponse("Error: No login!"))
    if 'name' not in request.POST:
        return (HttpResponse("Error: No name!"))
    if not PlayersModel.objects.filter(login=request.POST['login']).exists():
        return (HttpResponse("Error: Login '" + request.POST['login'] + "' does not exist!"))
    owner = PlayersModel.objects.get(login=request.POST['login'])
    new_room = RoomsModel(
        game=request.POST['game'],
        name=request.POST['name'],
        nplayers=1,
        owner=owner,
        server=owner
    )
    if new_room.game == 'pong':
        data = pong_data
        new_room.x = data['PADDLE_WIDTH'] / 2
        new_room.y = data['HEIGHT'] / 2
    else:
        data = {}
    new_room.save()
    player_room = PlayerRoomModel(
        player=owner,
        room=new_room,
        side=0,
        position=0
    )
    player_room.save()
    return (JsonResponse({
        'id': str(new_room),
        'game': new_room.game,
        'name': new_room.name,
        'data': pong_data
        }))

@csrf_exempt
def join(request):
    if 'game_id' not in request.POST:
        return (HttpResponse("Error: No game id!"))
    if 'login' not in request.POST:
        return (HttpResponse("Error: No login!"))
    if not PlayersModel.objects.filter(login=request.POST['login']).exists():
        return (HttpResponse("Error: Login '" + request.POST['login'] + "' does not exist!"))
    #uuid_obj = UUID(uuid_str)
    if not RoomsModel.objects.filter(id=request.POST['game_id']).exists():
        return (HttpResponse("Error: Room with id '" + request.POST['game_id'] + "' does not exist!"))
    room = RoomsModel.objects.get(id=request.POST['game_id'])
    return (JsonResponse({
        'id': str(room),
        'game': room.game,
        'name': room.name
        }))

@csrf_exempt
def delete(request):
    if 'game_id' not in request.POST:
        return (HttpResponse("Error: No game id!"))
    if 'login' not in request.POST:
        return (HttpResponse("Error: No login!"))
    if not PlayersModel.objects.filter(login=request.POST['login']).exists():
        return (HttpResponse("Error: Login '" + request.POST['login'] + "' does not exist!"))
    owner = PlayersModel.objects.get(login=request.POST['login'])
    #uuid_obj = UUID(uuid_str)
    if not RoomsModel.objects.filter(id=request.POST['game_id']).exists():
        return (HttpResponse("Error: Room with id '" + request.POST['game_id'] + "' does not exist!"))
    room = RoomsModel.objects.get(id=request.POST['game_id'])
    s = "Room " + room.name + ' - ' + str(room) + " deleted"
    room.delete()
    if room.owner == owner:
        return (HttpResponse(s))
    return (HttpResponse("Error: Login '" + request.POST['login'] + "' is not the owner of '" + request.POST['game_id'] + "'!"))
