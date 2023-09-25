# anthes1s-converter

So, this should be a video converter using QT+ffmpeg, it's currently in a very poor condition (but at least it does it's job, i just need to polish it a little bit);

TODO:
1. Make a better/user friendly interface;   [kinda done]
2. Find a way to be able to choose the rendering codec and video format; [done]
3. Fix the UI freezing [done]
4. Find a way to be able to render multiple files at the same time; 
5. Find a way to limit the CPU usage when the process is run in the background (ffmpeg can cause a huge cpu load when rendering multiple files);
6. Find a way to create a progress bar to let the user know how fast render is going or when it's going to end (check QProcess timers or whatever the fuck it's using when it waits for the process.start to end);
7. Create a SETUP where the user will install the ffmpeg and the software itself
8. CHECK IF FFMPEG IS INSTALLED ON THE SYSTEM FOR THE WHOLE SHIT TO WORK
9. ERROR HANDLE WRONG INPUTS FROM TEXT EDIT
10. ??????
11. PROFIT
