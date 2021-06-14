# Pritzza-Engine
An uncreative name for another one of my attempts at a 2d game engine. Uses SFML and C++ 17.

## Current Features

Entity System
  - Game objects and entites can have animated sprites and collide
  - Entities can move around smoothly
  
 Camera
  - Can follow any game object or entity
  - Able to pan to points at linear and exponential speeds
  - Flexible zooming in and out
  - Optimized to not render sprites outside of view
  
Sprites
  - Scaleable and transformable
  - Can be animated with AnimatedSprite class
  
Resource Manager
  - Flexibly manages sf::Textures, sf::Fonts, and sf::Sounds using enum classes
  
Game State Machine
  - Able to store multiple states at once
  - Can switch between any states at any time
  - Easy to create new state by inheriting from State class

Other
  - Isometric tilemaps
  - Perlin noise (by Reputeless)
  - AABB collision detection
  - Mouse & Keyboard input wrapper
  - sf::Text wrapper
  
## Controls
  - Movement: WASD
  - Zoom In/Out: E
  - Regenerate Terrain: Q
  - Change Gamestate: MMouse

## Todo
  - Clean up code
  - Finish implementind Text class
  - Make isometric tile collision
   
## Demo Screenshots
![Screenshot](https://cdn.discordapp.com/attachments/746538931192987696/845346354494570556/unknown.png)
![Screenshot](https://cdn.discordapp.com/attachments/746538931192987696/845346381900152892/unknown.png)
![Screenshot](https://cdn.discordapp.com/attachments/746538931192987696/845348513134018590/unknown.png)
