import json
from channels.generic.websocket import AsyncWebsocketConsumer
#from channels.generic.websocket import WebsocketConsumer
from .models import RoomsModel

#def update_rooms(event):
#    action = event['action']
#    if (action['action'] == "new"):
#        RoomsModel(
#            game="pong",
#            name=action['name'],
#            nplayers=1,
#            owner=action['owner']
#        ).save()
#    if (action['action'] == "delete"):
#        RoomsModel.objects.get(id=action['id']).delete()
#    return ([
#        {
#            "id": i.id,
#            "name": i.name
#        } for i in RoomsModel.objects.all()
#        ])
        
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
        await self.send(text_data=json.dumps([
            {
                "id": i.id,
                "name": i.name
            } for i in RoomsModel.objects.all()]))
        #return ([
        #    {
        #        "id": i.id,
        #        "name": i.name
        #        } for i in RoomsModel.objects.all()
        #    ])
        #action = event['action']
        #if action['action'] == "new":
        #    # Your implementation for handling a new action
        #elif action['action'] == "delete":
        #    # Your implementation for handling a delete action

        ## Send the updated room data to the group
        #await self.send(text_data=json.dumps([
        #    {
        #        "id": i.id,
        #        "name": i.name
        #    } for i in RoomsModel.objects.all()]))

