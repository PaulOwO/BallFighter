### Ball Fighter

## Game Design Document

# Introduction 

Ball Fighter is the first summative project of my second year at SAE Instiitute in games programming for the module GPR5100.
It was made by me, Paul Breuza with a huge basecode by Elias Fahran, our teacher.
The game is a C++ online multiplayer fighting game that work on a server-client architecture.

# The Game 

![image](https://user-images.githubusercontent.com/71375990/139921752-85673601-50da-478f-9cf4-3951279d3f2c.png)

You incarnate a red or blue ball with a 2d side view, your goal is simple, jump on the upper part of the other player to kill him.
For that your possible action are moving right, left and jumping. You cannot jump in the upper part of the screen so that you are always killable.
You and your enemy are stuck in a square arena, and be carful the roof and wall will give you an impulsion to try to surpise your enemy.

# Developpement

Like I said before we started with a huge codebase, this codebase was a sort of asteroid (the game) but in duel. The server-client architecture was already there.
The firts step was to understand this code and plan what I was going to do during the next 3 weeks to advance at a regular pace.
It was the first time that we did that so I learned a lot about how to spend time planning to acually save time programming. Going step by step was also neascesary not to get lost. 
The first step of my plan was to delete all that i didn't need in the code like bullet and shooting for exemple, this step took way longer that I thought it would because of the fact that everyting in the code was linked. 
My next step was making the game physical engine and player movement, we had already done a physical engine in the last formative last year but it wasn't that easy because I I had to implement it using the already existing code so that the roolback would still work. The client-server relation being already there all we had to do is understand it and being able to use it like we wanted, for the player movement. I forgot my second law of Newton and didn't get my gravity right until some help.

![image](https://user-images.githubusercontent.com/71375990/139919762-0d67d474-8680-444e-8f02-bf649c50c917.png))

Here we can see how I set the player velocity and movement using the delta time, we can also see how I delimited the game space using the window size(1000) the radius of the 2 players and the pixel to meter that I had some problem with and my game view overall.

The teacher being away for some time made us also predict where we were going to need help and made us do the best of limited help time.
I finished the collision without to much trouble and was left was the win condition.

![image](https://user-images.githubusercontent.com/71375990/139920792-6973b4aa-201a-4a67-9b3f-c6f0249647d6.png)

This code is called only when there is a collision and based on the radius of the circle we can determine if the contact was on the upper part of the circle only with their y axis position to know the looser.

When coding was over I checed and deleted things I didn't use and tried to clean up my code.


You can use the [editor on GitHub](https://github.com/PaulOwO/BallFighter/edit/gh-pages/index.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/PaulOwO/BallFighter/settings/pages). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://docs.github.com/categories/github-pages-basics/) or [contact support](https://support.github.com/contact) and we’ll help you sort it out.
