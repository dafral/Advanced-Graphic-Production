##NAMES: ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	* **Pau Olivé**  
	* **David Franco**  

##FEATURES: //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
	### MAIN MENU TOOLBAR ///////////////////////////////         
		* **Exit Application Button**     
			- You can press this button in order to quit the application. Will ask if you want to save before leaving.      
		* **Save Button:**    
			- When pressing the button will save the current scene into a QSetting generated file (.sce).   
		* **Load Button:**    
			- When pressing the button will open the folder containing the project and, upon selecting a .sce file, will load the selected scene into the current.  
		* **Save Render:**  
			- When pressing the button will save the current scene as a .png file.  
	### INSPECTOR ////////////////////////////////////////     
		- Shows the current values of the selected Entity. Those values can be modified interacting with the different UI elements on the widget.     
	### HYERARCHY ////////////////////////////////////////      
		- Will show the Entities hyerarchy on the current scene. Double Clicking them will select the current entity and show its values in the Inspector Window.    
		* **Add Entity Button:**    
			- Will Add a new Entity to the scene. The Entities values will be setted to default values.  
		* **Delete Entity Button:**     
			- Deletes the current selected Entity from the scene.     
	### CENTRAL WIDGET //////////////////////////////////         
		- Renders the current scene on screen, inside its boundaries. It uses the different Entitites inside the Hyerarchy to know wich Shape, Fill Color, Fill Style, Stroke Color, etc. variables to use when Printing them to screen.      
     

##Qt FEATURES & USES: /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            
- For this project, we have used:       
	* **Signals / Slots:**     
		- To perform sepcific methods when a UI element is being interacted with (p.e. Hyerarchy, Transform, ...).      
	* **Widget Promotion:**    
		- Used on the CenterWidget to be able to apply its functionality entirely with C++.  
	* **Style Sheet:**     
		- For this project we used the default style sheet provided by Qt.     
	* **QSettings:**      
		- Used in order to perform     
	* **QPainter:**         
		- QPainter class has been used in order to print the different shapes and styles into the Center Widget.      
		