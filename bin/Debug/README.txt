Conway's Game of Life

Implemented by Nic Kristiansson 6/2018

Instructions:
	Use the mouse buttons to alter the cells and acces the settings.
		Left click to make a cell alive, right click to make one dead.

	Use the spacebar to pause the simulation.

Life:
	Cells are either "alive" (yellow) or "dead".
	Each step of the simulation checks the adjcent cells and 
	 determines if it will be alive or dead the next step.
	The default settings for life and death are:
		If a cell is alive, and has 2 or 3 live cells next to it, it lives.
		If a cell has less or more than that, it dies.
		If a dead cell has 3 cells next to it, it becomes alive.