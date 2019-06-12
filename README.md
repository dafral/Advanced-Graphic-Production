# Advenced Graphics Programming:
# Project 2 - OpenGL  
### Team: Pau Olivé & David Franco  
  ![intro](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/patrickintro.png)  
  
## User Guide:  
### Loading Models:  
the Windows inspector is opened, select the file you want to display in the visualizer.    
    
The visualizer supports “.FBX” and “.OBJ” files.    
![load](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/loadmodel.png)  
![load2](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/resources.png)  
  
### Enabling / Desabling:  
On the right side of the visualizer you can find all the options to enable and disable the different implementation layers in the application. In order to activate or deactivate them, just click the checkbox of the technique you want to change. If the checkbox it’s marked, the technique will be activated.  
  
In order to see the changes in the visualizer, resize the window or move the camera around so the window will update.  
![checkers](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/checkers.png)  
  
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
![l1](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/ligh2.png)  
![l2](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/ligh1.png)  
  
## Techniques Implemented:
### Diffuse:  
![diff](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/diffuse.png)  
  
### Normal Map:   
The normal map is applied when loading the model (in this project is always StoneFloorNormals.png).  
With the deferred technique it is computed in the geometry shader and truly applied on the lighting shader.  
![normals](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/normals.png)  
  
### Specularity:    
The specular is computed automatically with the normals of the model.   
With the deferred technique it is computed in the geometry shader and truly applied on the lighting shader.  
![Spec](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/specular.png)  
  
### Deferred Shading:  
The deferred shading is a techinque where the shading process is divided into Geometry Pass and Lighting Pass. On the Geometry Pass you have to create one texture for Positions, Normals, Albedos and, optionally, Speculars. You attach them together into a buffer called GBuffer and make the lighting pass, where you use these textures to manage all lights at once.
![codegbuff](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/codegbuffer.png)    
  
**GPosition:**  
![gpos](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/gpos.png)  
  
**GAlbedo:**  
![galb](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/gdiff.png)  
_Note: The original Albedo is really bright without applying lights, is not an artifact._
  
**GNormals:**  
![gnorm](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/gnorm.png)  
  
**GSpecular:**  
![gspec](https://github.com/dafral/Advanced-Graphic-Production/blob/Pau_DeferredLight/Images/gspec.png)  
    
**Extra:**  
The GBuffer is redone each time the screen is resized since, if you maintain the GBuffer as it is, the image appears to be streched and with visible pixels.  
