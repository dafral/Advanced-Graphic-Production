NAMES: 
	- Pau Olivé
	- David Franco

FEATURES:
	- Main Menu Toolbar:
		* Save Button:
		* Load Button:
	- Inspector:
		Shows the current values of the selected Entity. Those values can be modified interacting with the different UI elements on the widget.
	- Hyerarchy:
		Will show the Entities hyerarchy on the current scene. Double Clicking them will select the current entity and show its values in the Inspector Window.
		* Add Entity Button:
			Will Add a new Entity to the scene. The Entities values will be setted to default values and names have a 10% probability to be 'special names' (can be changed after).
		* Delete Entity Button:
			Deletes the current selected Entity from the scene.
	- Central Widget:
		Renders the current scene on screen, inside its boundaries. It uses the different Entitites inside the Hyerarchy to know wich Shape, Fill Color, Fill Style, Stroke Color, etc. variables to use when Printing them to screen.


Qt FEATURES & USES:
For this project, we have used:
	- Signals / Slots:
		To perform sepcific methods when a UI element is being interacted with (p.e. Hyerarchy, Transform, ...). 
	- Widget Promotion:
		Used on the CenterWidget to be able to apply its functionality entirely with C++.
	- Style Sheet:
		For this project we used the default style sheet provided by Qt.