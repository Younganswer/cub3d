# cub3d
### My first RayCaster with miniLibX
<br/><br/><br/>

## Summary
#### This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.
<br/><br/><br/>

## Install
	$ make [-jN] (all)
<br/><br/><br/>

## Usage
	$ ./cub3d /path_to_map/mapfile.cub
* File must end with `.cub` extension
* map.cub is a file that contains all the information needed to create the map
	* path to xpm textures
		* NO, SO, WE, EA
	* color of floor and ceiling
		* F, C
	* map
		* 0, 1, N, S, E, W
		* map must be closed by walls
<br/><br/><br/>

## Result
https://user-images.githubusercontent.com/55086725/221144165-8af36543-7d65-41eb-9f08-72174f04adbd.mp4
