from django.shortcuts import render

# Create your views here.

def new_game(request):
    return render(request, "chat/room.html", {"room_name": room_name})
