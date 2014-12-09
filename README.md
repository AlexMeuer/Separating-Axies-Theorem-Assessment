SAT Assessment
==============

###### The results are in!
![Result: 93%](https://github.com/Not0nFire/Graphics-Lab-1/blob/master/SAT_result.png "SAT Result: 93%")


Program uses multi-threading to showcase a side-by-side comparison of the __SAT Collision Detection__
both with and without optimization. (The windows start in the same place so drag one to reveal the other.)

Known Issues
==============

Collision Detection
--------------
+ _Sometimes_ (it seems to be mostly when BouncingThings hit nearly perfectly point on or edge on)
the collision detection between BouncingThings calculates the MTV incorrectly, and put the object on opposite sides
to each other.

+ When the __Pair Redundancy__ optimization is enabled,
some objects will completely pass through each other.

+ The collision detection is most stable when no optimization is carried out.
However, _Visual Studio Performance Analysis_ shows that the collision detection takes just over two times the processing power.

Derived Classes _(Required by brief)_
--------------
+ _TL;DR_ Triangle and Square are redundant. Base class OP.
+ Although _Triangle_ and _Square_ objects have their own classes, the _BouncingThing_ class (the base class)
will happily take any number of points (and a radius) and give you a convex shape based on that, which __will__ work with
the collision detection.

About those QuadTree files...
==============
I did not have time to implement a quadtree and try to fix the glitchy-ness of my SAT algorithms.
(The files aren't implemented)
