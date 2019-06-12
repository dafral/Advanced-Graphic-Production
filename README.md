# Advenced Graphics Programming:
# Project 2 - OpenGL  
### Team: Pau Olivé & David Franco  
  
## User Guide:  
### Loading Models:  
the Windows inspector is opened, select the file you want to display in the visualizer.    
    
The visualizer supports “.FBX” and “.OBJ” files.    
  
### Enabling / Desabling:  
On the right side of the visualizer you can find all the options to enable and disable the different implementation layers in the application. In order to activate or deactivate them, just click the checkbox of the technique you want to change. If the checkbox it’s marked, the technique will be activated.  
  
In order to see the changes in the visualizer, resize the window or move the camera around so the window will update.  
  
### Camera Controls:  
* **Navigation:** [MouseRight] + [W/A/S/D]
* **Rotation:** [MouseRight] + Move Mouse
* **Reset Position:** [F]
  
### Model Transform Controls:  
* **Translation:** [T] + [W/A/S/D/Q/E] (X Axis: W/S - Y Axis A/D - Z Axis Q/E)  
* **Rotation:** [R] + [W/A/S/D/Q/E] (X Axis: W/S - Y Axis A/D - Z Axis Q/E)  
* **Scaling:** [G] + [W/A/S/D/Q/E] (X Axis: W/S - Y Axis A/D - Z Axis Q/E)  
* **Reset Transform:** [U]  
  
### Light Controls:  
* **Rotation:** [L] + [W/A/S/D/Q/E] (X Axis: W/S - Y Axis A/D - Z Axis Q/E)  

## Techniques Implemented:
### Normal Map:   
The normal map is applied when loading the model (in this project is always StoneFloorNormals.png).  
With the deferred technique it is computed in the geometry shader and truly applied on the lighting shader.  

### Specularity:    
The specular is computed automatically with the normals of the model.   
With the deferred technique it is computed in the geometry shader and truly applied on the lighting shader.  
  
### Deferred Shading:  
The deferred shading is a techinque where the shading process is divided into Geometry Pass and Lighting Pass. On the Geometry Pass you have to create one texture for Positions, Normals, Albedos and, optionally, Speculars. You attach them together into a buffer called GBuffer and make the lighting pass, where you use these textures to manage all lights at once.
**GPosition:**  

  
**GAlbedo:**  
  
**GNormals:**  
  
**GSpecular:**  

  
**Extra:**  
The GBuffer is redone each time the screen is resized since, if you maintain the GBuffer as it is, the image appears to be streched and with visible pixels.  
