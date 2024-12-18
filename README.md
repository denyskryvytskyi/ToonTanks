# ToonTanks
This is a 3D game created in Unreal Engine 5 as part of the Unreal Engine 5 C++ Developer: Learn C++ & Make Video Games course. The game features a level with enemy towers shooting a player tank.

Here are some specific things I learned while making this game:

- Custom Pawn class for the Tank and Towers
- New Enhanced Input system usage for the player controller with custom input actions and input mapping context
- Gamepad support
- Tank movement using player input
- Projectiles spawning on Tank/Tower shooting
- Health, damage and destruction logic
- Simple HUD with start/end game messages
- Special effects: smoke, explosions
- Sounds on fire and destroy
- Camera shake effect

# Demo
Video on YouTube (click on image):
[<img src=".github/demo/ToonTanksThumbnail.png">](https://youtu.be/OqnVpx-66cU?si=7spcowMuWaRDy6k7)

# Getting started
*Updated to the Unreal Engine 5.4.3.*
1. `git clone https://github.com/denyskryvytskyi/ToonTanks`
2. Right-click the `ToonTanks.uproject` file and select `Generate Visual Studio project files`
3. Build project in Visual Studio (`Development Editor` configuration to run in Editor)
4. Run `ToonTanks.uproject`
