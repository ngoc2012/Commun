import json
from channels.generic.websocket import AsyncWebsocketConsumer
#from channels.generic.websocket import WebsocketConsumer
from .models import RoomsModel, PlayersModel

class RoomsConsumer(AsyncWebsocketConsumer):

    async def connect(self):
        self.group_name = "rooms"
        self.channel_layer.group_add(
            self.group_name,
            self.channel_name
        )
        await self.accept()

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
            print("Error: No action in event")
            return
        action = event['action']
        if 'action' not in action.keys():
            print("Error: No action")
            return
        if 'login' not in action.keys():
            print("Error: No login")
            return
        if PlayersModel.objects.filter(login=request.POST['login']).exists():
        if 'login' not in action.keys():
            print("Error: No login")
            return
        if (action['action'] == "new"):
            RoomsModel(
                    game="pong",
                    name=action['name'],
                    nplayers=1,
                    owner=action['owner']
                    ).save()
        if (action['action'] == "delete"):
            RoomsModel.objects.get(id=action['id']).delete()
        await self.send(text_data=json.dumps([
            {
                "id": i.id,
                "name": i.name
            } for i in RoomsModel.objects.all()]))

