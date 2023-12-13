import json
from channels.generic.websocket import AsyncWebsocketConsumer
from views import rooms

class GameConsumer(AsyncWebsocketConsumer):
    global rooms
    #async def connect(self):
    #    # Get the unique identifier from the query parameters or headers
    #    user_id = self.scope.get('user')  # Adjust this based on your authentication method

    #    # Create a unique room name based on the identifier
    #    room_name = f"user_{user_id}"

    #    self.room_name = room_name
    #    self.room_group_name = f"room_{self.room_name}"

    #    # Add the player to the room group
    #    await self.channel_layer.group_add(
    #        self.room_group_name,
    #        self.channel_name
    #    )

    #    await self.accept()
    async def connect(self):
        self.user = self.scope.get('user')  # Adjust this based on your authentication method
        self.rooms = "rooms"

        # Join room group
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )

        # Update game state
        await self.channel_layer.group_send(
            self.rooms,
            {
                'type': 'update_state',
                'state': updated_state_data,
            }
        )
        
        # Notify player join
        await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'player_join',
                'player_count': updated_player_count,
            }
        )



    async def disconnect(self, close_code):
        # Leave room group
        await self.channel_layer.group_discard(
            self.room_group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        # Handle user input (if needed)
        pass

    async def update_state(self):
        # Send the updated game state back to all clients in the room
