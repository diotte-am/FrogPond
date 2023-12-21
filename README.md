## "Midnight Frog Pond"
### Simple Object and Texture Loader


## Presentation
(Same video, just different uploads):

<iframe width="420" height="315"
src="https://www.youtube.com/watch?v=H7zUugNJhbQ
">
</iframe>

**YouTube**

**Dropbox**
https://www.dropbox.com/scl/fi/18mtaatonjpu3tgm90tt5/FinalProject.mov?rlkey=9xerygracs96t06pxtb6jvtcc&dl=0

## Screenshots:

<caption>Initial view</caption>
<img src="common/images/InitialViewScreenshot.png">

<caption>View from right side</caption>
<img src="common/images/SideViewScreenshot.png">

<caption>Eclipse - partial </caption>
<img src="common/images/EclipseBeginScreenshot.png">

<caption>Eclipse - full </caption>
<img src="common/images/EclipseScreenshot.png">

## Compilation notes

if you are on a Mac and have compilation issues, replace line 25 in the build.py file with:

```

LIBRARIES="-F/Library/Frameworks -framework SDL2"

```
<br>

Also, any objects that use SDL.h probably need this heading added back in:
```
  #if defined(LINUX) || defined(MINGW)

  #include <SDL2/SDL.h>
      
  #else // This works for Mac

  #include <SDL.h>
      
  #endif
```
<br>

**Link to presentation slides:**

https://docs.google.com/presentation/d/1OHy2vmyjO4PRNmW5abiy40k0O-cTpNV9b4hBV8KIlXc/edit?usp=sharing

<br>

*Not the full video, just a quick clip of the program running:*

https://www.youtube.com/watch?v=uvwcN2KyraA


### Citations:
This program is based on source code created by <a href="https://www.mshah.io/"> Mike Shah</a> for <a href="https://www.mshah.io/comp/Fall23/Graphics/public/index.php"> CS5310 Computer Graphics </a> at Northeastern. More information about his source code can be found <a href="https://www.youtube.com/embed/videoseries?list=PLvv0ScY6vfd_GH4r13ylnbxF-IXKP7VuL">here</a>.


Raw images used for scene obtained from:
- https://upload.wikimedia.org/wikipedia/commons/3/37/Aerial_view_of_Lagoa_do_Can%C3%A1rio%2C_S%C3%A3o_Miguel_Island%2C_Azores%2C_Portugal_%28PPL1-Corrected%29.jpg
- https://wallpapers.com/wallpapers/starry-sky-night-dark-sky-stars-zeyj6p1s41agbk57.html
- https://upload.wikimedia.org/wikipedia/commons/2/2d/Full_Moon_%2815984763045%29.jpg


Tutorials used for "fog" effect:
- https://www.youtube.com/watch?v=oQksg57qsRA&t=19s
- https://www.youtube.com/watch?v=qslBNLeSPUc




  