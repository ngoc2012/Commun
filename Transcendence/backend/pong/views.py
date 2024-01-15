from django.shortcuts import render
from django.http import HttpResponse
from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from game.models import PlayersModel, PlayerRoomModel

# Create your views here.
def index(request):
    return render(request, "pong.html")

@csrf_exempt
def state(request):
    if 'login' not in request.POST or request.POST['login'] == "":
        return (HttpResponse("Error: No login!"))
    player = PlayersModel.objects.get(login=request.POST['login'])
