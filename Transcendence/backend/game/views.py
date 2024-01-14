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
    owner = PlayersModel.objects.get(login=action['login'])
    if (action['action'] == "new"):
        RoomsModel(
                game=action['game'],
                name=action['name'],
                nplayers=1,
                owner=owner
                ).save()
    if (action['action'] == "delete"):
        RoomsModel.objects.get(id=action['id']).delete()
    return (JsonResponse({
        'id': new_game.id,
        'name': new_game.name
        }))
