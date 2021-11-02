### Ball Fighter

## Game Design Document

# Introduction 

Ball Fighter is the first summative project of my second year at SAE Institute in games programming for the module GPR5100.
It was developed by me, Paul Breuza with a significant basecode by Elias Farhan, our teacher.
The game is a C++ online multiplayer fighting game that works on a server-client architecture.

# The Game 

![image](https://user-images.githubusercontent.com/71375990/139921752-85673601-50da-478f-9cf4-3951279d3f2c.png)

You are a red or blue ball with a 2D side view. Your goal is simple, jump on the upper part of the other player to kill him and win.
For that, your possible actions are moving right, left and jumping. You cannot jump in the upper part of the arena so that you are always killable.
You and your opponent are stuck in a square 2D arena, where roof and walls give you an impulsion that you can use to try to surprise your opponent.

# Developpement

Like I said before, we started with a provided codebase. This codebase was a kind of Asteroid (the game) but in duel. The server-client architecture was already there.
The firt step was to understand this code and plan what I was going to do during the next 3 weeks to advance at a regular pace.
It was the first time that we did that so I learned a lot about how to spend time planning, to acually save time programming. Going step by step was also necessary not to get lost. 
The first step of my plan was to delete all that I didn't need in the code like bullets and shooting for example. This step took way longer than I thought it would, because of the fact that everything in the code was linked. 
My next step was making the game physical engine and player movements. We had already done a physical engine in the last sommative last year but it wasn't that easy because I had to implement it using the already existing code so that the rollback would still work. The client-server relation being already there, all we had to do is to understand it and being able to use it as we wanted. For the player movements, I forgot my second law of Newton and didn't get my gravity right until some help.

![image](https://user-images.githubusercontent.com/71375990/139919762-0d67d474-8680-444e-8f02-bf649c50c917.png))

Here we can see how I set the player velocity and movement using the delta time. We can also see how I delimited the game space using the window size(1000), the radius of the 2 players, and the pixel to meter which I had some problem with, and my game view overall.

The teacher being away for some time, we also had to anticipate where we were going to need help and made us do the best of limited help time.
I finished the collision without to much trouble and was left with the winning condition.

![image](https://user-images.githubusercontent.com/71375990/139920792-6973b4aa-201a-4a67-9b3f-c6f0249647d6.png)

This code is called only when there is a collision between and based on the radius of the circle we can determine if the contact was on the upper part of the circle only with their y axis position to know the looser.

When the game was over I checked and deleted things I didn't use and tried to clean up my code.

# Conclusion 

We had already made a game around an algorythm we needed to undertand but never a game using an entire codebase that we had to understand which was interesting, rewarding but sometimes frustrating.
