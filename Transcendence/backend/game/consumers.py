import json
from channels.generic.websocket import AsyncWebsocketConsumer
#from channels.generic.websocket import WebsocketConsumer
#from channels.db import database_sync_to_async
from asgiref.sync import sync_to_async
from .models import RoomsModel, PlayersModel

@sync_to_async
def room_list(rooms):
    return json.dumps([
        {
            "id": i.id,
            "name": i.name
            } for i in rooms])

class RoomsConsumer(AsyncWebsocketConsumer):

    async def connect(self):
        self.group_name = "rooms"
        self.channel_layer.group_add(
            self.group_name,
            self.channel_name
        )
        await self.accept()
        rooms = RoomsModel.objects.all()
        await self.send(text_data=room_list(rooms))

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        data = json.loads(text_data)
        await self.channel_layer.group_send(
            self.group_name,
            {
                'type': 'update_rooms',
                'action': data,
            }
        )
        #self.send(text_data=json.dumps(update_rooms(json.loads(text_data))))

    async def update_rooms(self, event):
        if 'action' not in event.keys():
            print("Error: No action in event.")
            return
        action = event['action']
        if 'action' not in action.keys():
            print("Error: No action.")
            return
        if 'game' not in action.keys():
            print("Error: No game.")
            return
        if 'login' not in action.keys():
            print("Error: No login.")
            return
        if not PlayersModel.objects.filter(login=action['login']).exists():
            print("Error: Login " + action['login'] + " does not exist.")
            return
        owner = PlayersModel.objects.filter(login=action['login'])
        if (action['action'] == "new"):
            RoomsModel(
                    game=action['game'],
                    name=action['name'],
                    nplayers=1,
                    owner=owner
                    ).save()
        if (action['action'] == "delete"):
            RoomsModel.objects.get(id=action['id']).delete()
        rooms = sync_to_async(RoomsModel.objects.all())
        await self.send(room_list)
