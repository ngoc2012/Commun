from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from .models import RoomsModel, PlayersModel

@csrf_exempt
def new_player(request):
    if 'game' not in action.keys():
        print("Error: No game.")
        return None
    if 'login' not in action.keys():
        print("Error: No login.")
        return None
    if 'login' not in request.POST or 'password' not in request.POST or 'name' not in request.POST:
          return (HttpResponse({'Error: Form not correct!'}))
    if request.POST['login'] == "" or request.POST['password'] == "" or request.POST['name'] == "":
        return (HttpResponse({'Error : Form not correct!'}))
    if PlayersModel.objects.filter(login=request.POST['login']).exists():
        return (HttpResponse({"Error: Login '" + request.POST['login'] + "' exist."}))
    new_player = PlayersModel(
            login=request.POST['login'],
            password=request.POST['password'],
            name=request.POST['name'],
            x=0,
            y=0
            )
    new_player.save()
    return (JsonResponse({
        'login': new_player.login,
        'name': new_player.name
        }))
