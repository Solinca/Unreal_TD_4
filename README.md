# Unreal_TD_4

### Controls:

Z Q S D     -> Player Movement

Left Shift  -> Hold to run

Left Ctrl   -> Hold to crouch

E           -> Grab an item if close enough to it (only bottles for now)

Right Click -> If holding an item, trigger the aim

Left Click  -> If aiming, throw the held item

Escape      -> Trigger in game pause menu

Inputs are disabled on death and during pause


### IA Behavior:

3 different behavior trees associated with a state:

- CALM       => Simple patrolling system between points. If no patrol points are registered, it will simply stay on the spot.
- SUSPICIOUS => If a sound has been triggered near the IA, it will go to the sound position to investigate. After 5s without triggering a new sound, it will go back to the CALM state.
- ALERTED    => Once an AI has made visual contact with the player, all is doomed. The AI will proceed to sprint towards the player, and trigger the death screen on contact with him.


### Checkpoint System:

Checkpoints are invisible and in betwen game segments. On player death, everything will reload to its initial position and the player will be teleported to the latest checkpoint registered.


### Hide Spots System:

When entering a Hide Spot, the camera will switch to its Hide Spot counterpart. Upon leaving it, it will switch back to the Player's one.
Controls during a Hide Spot are the same as usual, so it may be counter-intuitive.


### Extraction System:

When reaching the end of the labyrinth, a fade to black will occur with a change level to Victory level with a victory theme.


### Imported Assets (sounds are modified with Audacity):

Main Music: https://downloads.khinsider.com/game-soundtracks/album/metal-gear-solid-original-soundtrack/06.%2520Encounter.mp3

Victory Music: https://www.youtube.com/watch?v=PlqKwDznPlU


Alert Sound: https://www.myinstants.com/en/instant/metal-gear-solid-alert/

Suspicious Sound: https://www.myinstants.com/en/instant/huh-ceeday-65118/

Death Sound: https://www.myinstants.com/en/instant/metal-gear-solid-death-78313/

Bottle Break Sound: https://pixabay.com/sound-effects/glass-crack-363162/

Footstep Sound: https://pixabay.com/sound-effects/concrete-footsteps-6752/


Player Mesh and Animations: https://www.fab.com/listings/64c53af0-dcb7-4483-9d65-5cbc84bd9a93

Enemy Mesh and Animations: Unreal TD Class

Bottle Mesh: https://www.fab.com/ja/listings/95c9ce6a-4f49-4d9b-a5d6-2a5bab022d50


MGS Alert Sprite: https://static.wikia.nocookie.net/metalgear/images/2/20/MGS_Exclamation_Mark_Icon.png/revision/latest?cb=20121230232530

Suspicion Sprite: Homemade
