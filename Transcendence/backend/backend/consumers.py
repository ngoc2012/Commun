import json
from channels.generic.websocket import AsyncWebsocketConsumer
from views import rooms

class GameConsumer(AsyncWebsocketConsumer):
    global games
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
        self.room_name = self.scope['url_route']['kwargs']['room_name']
        rooms.add(self.room_name)
        self.user = self.scope.get('user')  # Adjust this based on your authentication method
        self.room_group_name = f"pong_{self.room_name}"

        # Update game state
        await self.channel_layer.group_send(
            self.room_group_name,
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

        # Join room group
        await self.channel_layer.group_add(
            self.room_group_name,
            self.channel_name
        )

        await self.accept()

        # Start a loop to continuously update the game state
        await self.game_loop()

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
        await self.channel_layer.group_send(
            self.room_group_name,
            {
                'type': 'game_update_state',
                'state': self.state,
            }
        )
