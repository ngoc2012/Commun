from django.shortcuts import render

# Create your views here.
def index(request):
    return render(request, "pong.html")

#def room(request, room_name):
#    return render(request, "chat/room.html", {"room_name": room_name})
