# Lab 2 - Animation

## Student Name(s)

Enter your name(s) here (All team members):

| Name | Email | GitHub User Name |
| - | - | - |
| (insert name) | (insert email) | (insert github username) |

## Instructions for Teacher

(insert, if needed, instructions for teacher here)

## Introduction 
The goal of this assignment is to have data-driven animations. 
This is achieved by having one file that defines each individual frame of an animation in a ​sprite atlas. 
A sprite atlas is an image that contains multiple smaller images. 
The other file defines 
 1. What sprite atlas to use. 
 2. and the playback of the animation, i.e which frame is played in what order and with what type of behaviour.
 
### Examples of files

Sprite atlas:
```
// File: assets/player-sprite-atlas.txt 
assets/image/player-idle.png 
0 0 16 16 
16 0 16 16 
32 0 16 16 
48 0 16 16 
```

Animation:
```
// File: assets/player-animation.txt
assets/player-sprite-atlas.txt 
looping
0 1 2 3 4 5 6 7 8
```
 
### Reading

- [SDL2](https://www.libsdl.org/)
- [SDL2 Tutorial](https://lazyfoo.net/tutorials/SDL/index.php)
- [git - the simple guide](https://rogerdudler.github.io/git-guide/)
- [Markdown Cheat Sheet](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
- [Sprite Sheet Wikipedia](https://en.wikipedia.org/wiki/Texture_atlas)
 
## Pass

The ​Pass requirement for this assignment are: 
 - Three different types of animations 
   - A looping animation 
   - A ping pong animation 
   - Animation that only plays once.
 - One or more files with sprite atlas definitions.
 - Three or more files with animation definitions.
 
## Pass with Distinction

For a Pass with Distinction on this assignment you have to implement, in addition to the requirements in the Pass section, 
 - Skeletal animation.
 
[Skeletal Animation -  Wikipedia](https://en.wikipedia.org/wiki/Skeletal_animation)
 
Skeletal animation is a hierarchical set of interconnected bones and a surface representation of an object e.g a running character or a tree that is affected by wind.

The requirements are:
 - At least 10 bones in an hierarchy
 - In the hierarchy two bones must have two or more children
 
External applications like Spine and DragonBones are allowed for creating and exporting skeletal animation data but not required.

## Instructions

### Get started

Every student has to do the following steps:

 1. Make sure you have a [GitHub](https:://github.com) account.
 2. Accept the assignment by following the following link: <https://classroom.github.com/g/osVy1eoJ>.
 3. Select yourself in the list of identifiers. *Make sure you select the correct one*
 4. Create a new Team *OR* Select your team from the list. *Make sure you select the correct one*
 5. If this is your first time. You will receive an email with an invitation to the organisation `gameprogrammingii`. Accept this invitation.

### The assignment
 
 1. Clone the repository
 2. Edit the README.md (this file) and enter the name, email and username of all students in your team.
 3. Complete the assignment (read the rest of this document).
 
### Hand-in

 1. Commit and Push all your changes
 2. Create a new Issue in your GitHub project indicating that you are done with assignment and tag JohanNorberg

### Deadline

2020-03-27

## Grading

This assignment has Pass , Pass with Distinction or Fail .
For a Pass , all the required features in the Pass section of this document must be implemented
correctly. For a Pass with Distinction all the features for Pass must be implemented correctly in
addition to all required features for Pass with Distinction . Failing the steps defined in the
Requirements section and Hand-in section will lead to a Fail .

## Requirements

This is a individual or group assignment. Original code written by the student(s) with C/C++. Example code
and provided external code by course responsible can and should be used as a starting point
for the laboratory.

## Plagiarism

At university, we are continuously engaged with other people's ideas - we read about them, we
discuss them in class and we write about them in our assignments. It is therefore important that
we acknowledge these people in our assignments/projects/papers that we submit for marks. If
we do not adhere to these basic requirements, we are making ourselves guilty of a gross
violation of the academic standard.
Academic dishonesty in any form including, but not limited to plagiarism and collusion, cheating
in tests, examinations and assignments, theses and research papers, is regarded as a serious
offence and will be dealt with in terms of the provisions of the University’s Disciplinary Rules for
Students.
