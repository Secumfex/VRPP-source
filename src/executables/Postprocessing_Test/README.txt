//////////----------FEATURE DESCRIPTION----------//////////

So my feature was to implement SSAO or glow as postprocessing. While glow is implemented SSAO doesn't work at all. 
What SSAO is missing in its current state:
- proper texture management (uniform upload to the shader);
- shader doesn't compile as it is;
- shader requires at least one more texture and the shade needs to be added in the end on that texture value;
- i don't know what else, but i'd guess there is more;

About glow:

Glow is actually working, however at the moment there are issues with the architecture. After using the gbuffer style including
usage of openGL commands I switched the whole thing to the latest architecture of our engine. For some reason there are issues with the VOFactory being used by one of the RenderPass subclasses (not present on a different machine), so at the moment glow doesn't work in the main. Or it does, but 
only on some machines, weirdly enough. 

If the main.cpp crashes or no glow is visible do the following:

1) rename the main()-method of main.cpp to whatever other name.
2) rename the mainTemp()-method of temp.cpp to main().
3) recompile.

What will happen is that you will see the glow postprocessing, however using the old architecture.

Now after we messed with the engine a *lot* this old architecture may not work either in the current commit.

If all fails and you see weird textures or just white background and switching to temp.cpp didn't help feel free
to do a rollback to the commit "Fixed glow performance issues". That commit has the last 100% confirmed postprocess glow working with
the older architecture. 

Now the difference between this glow and gbuffer is just how it was implemented. What happens now, is that a postprocess pass is added
instead of doing effects in the compositing pass. So now it is gbuffer --> compositing --> glow, adding a pass after the compositing to do so.
Otherwise the glow code is basically unchanged, however now the whole scene is rendered into an FBO before applying glow to it and rendering
the postprocessing effects on the sceen.

Alright. So remember:

If main.cpp doesn't work properly use temp.cpp. If neither work properly roll back to "Fixed glow performance issues".
