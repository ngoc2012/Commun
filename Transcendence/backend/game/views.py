from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from .models import RoomsModel, PlayersModel

@csrf_exempt
def new_player(request):
    if 'game' not in request.POST:
        return (HttpResponse("Error: No game!"))
    if 'login' not in request.POST:
        return (HttpResponse("Error: No login!"))
    if 'name' not in request.POST:
        return (HttpResponse("Error: No name!"))
    if not PlayersModel.objects.filter(login=request.POST['login']).exists():
        return (HttpResponse("Error: Login '" + request.POST['login'] + "' does not exist!"))
    owner = PlayersModel.objects.get(login=request.POST['login'])
    new_game = RoomsModel(
        game=request.POST['game'],
        name=request.POST['name'],
        nplayers=1,
        owner=owner
    ).save()
    #if (action['action'] == "delete"):
    #    RoomsModel.objects.get(id=action['id']).delete()
    return (JsonResponse({
        'id': new_game.id,
        'name': new_game.name
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
    if 
    #    RoomsModel.objects.get(id=action['id']).delete()
    #    RoomsModel.objects.get(id=action['id']).delete()
    return (HttpResponse("Done"))
