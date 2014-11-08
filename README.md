SAT Assessment
==============

Known Issues
==============

Collision Detection
--------------
+ Sometimes (it seems to be mostly when BouncingThings hit nearly perfectly point on or edge on)
the collision detection between BouncingThings calculates the MTV incorrectly, and put the object on opposite sides
to each other.

Derived Classes (not an actual issue)
--------------
+ TL;DR Triangle and Square are redundant. Base class OP.
+ Also, although Triangle and Square objects have their own classes, the BouncingThing class (the base class)
will happily take any number of points (and a radius) and give you a convex shape based on that, which will work with
the collision detection.
