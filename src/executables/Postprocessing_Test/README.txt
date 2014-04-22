//////////----------FEATURE DESCRIPTION----------//////////

So my feature was to implement SSAO or glow as postprocessing. While glow is implemented SSAO doesn't work at all. 
What SSAO is missing in its current state:
- proper texture management (uniform upload to the shader);
- shader doesn't compile as it is;
- shader requires at least one more texture and the shade needs to be added in the end on that texture value;
- i don't know what else, but i'd guess there is more;

About glow:

Glow is actually working, however at the moment there are issues with the architecture. After using the gbuffer style including
usage of openGL commands I switched the whole thing to the architecture of our engine. For some reason there issues with the VOFactory being used by 
one of the RenderPass subclasses (not present on a different machine), so at the moment glow doesn't work in the main.

If the main.cpp crashes or no glow is visible do the following:

1) rename the main()-method of main.cpp to whatever other name.
2) rename the mainTemp()-method of temp.cpp to main().
3) recompile.

What will happen is that you will see the glow postprocessing, however using the old architecture.
