import json
from channels.generic.websocket import AsyncWebsocketConsumer
from asgiref.sync import sync_to_async
from .models import RoomsModel

@sync_to_async
def room_list(rooms):
    return json.dumps([
        {
            "id": str(i),
            "name": i.name
            } for i in rooms])

class RoomsConsumer(AsyncWebsocketConsumer):

    async def connect(self):
        self.group_name = "rooms"

        await self.channel_layer.group_add(
            self.group_name,
            self.channel_name
        )
        await self.accept()
        rooms = RoomsModel.objects.all()
        rooms_data = await room_list(rooms)
        print(rooms_data)
        await self.channel_layer.group_send(
            self.group_name,
            {
                'type': 'chat_message',
                'data': rooms_data
            }
        )

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        print(text_data)
        print(self.group_name)
        rooms = RoomsModel.objects.all()
        rooms_data = await room_list(rooms)
        await self.channel_layer.group_send(
            self.group_name,
            {
                'type': 'chat_message',
                'data': rooms_data
            }
        )
    
    async def chat_message(self, event):
        #print(event)
        #await self.send(text_data='rooms_data')
        await self.send(text_data=event['data'])
