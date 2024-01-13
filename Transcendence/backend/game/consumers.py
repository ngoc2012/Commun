import json
from channels.generic.websocket import AsyncWebsocketConsumer
from .models import RoomsModel

def update_rooms(event):
    action = event['action']
    if (action['action'] == "new"):
        RoomsModel(
            game="pong",
            name=action['name'],
            nplayers=1,
            owner=action['owner']
        ).save()
    if (action['action'] == "delete"):
        RoomsModel.objects.get(id=action['id']).delete()
    return ([
        {
            "id": i.id,
            "name": i.name
        } for i in RoomsModel.objects.all()
        ])
        
class RoomsConsumer(AsyncWebsocketConsumer):

    async def connect(self):
        self.accept()

    async def disconnect(self, close_code):
        pass

    async def receive(self, text_data):
        self.send(text_data=json.dumps(update_rooms(json.loads(text_data))))