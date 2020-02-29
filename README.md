# KARD_realworld_only
Realworld and Screen Skeleton data extracted from Kinect Activity Recognition Dataset

No Depth Map, and no RGB data making it much lighter to download for those who only need skeleton data.

## KARD contains 18 Activities. Each activity is performed 3 times by 10 different subjects.
-	1 Horizontal arm wave
-	2 High arm wave
-	3 Two hand wave
-	4 Catch Cap
-	5 High throw
-	6 Draw X
-	7 Draw Tick
-	8 Toss Paper
-	9 Forward Kick
-	10 Side Kick
-	11 Take Umbrella
-	12 Bend
-	13 Hand Clap
-	14 Walk
-	15 Phone Call
-	16 Drink
-	17 Sit down
-	18 Stand up

#### Activity description is given in the file name.
  
  aAA_sSS_eEE_realworld.txt

  aAA_sSS_eEE_screen.txt

AA = number of the activity: 01 to 18.

SS = the subject performing the activity: 01 to 10.

EE = the repetition performed by the subject: 01 to 03.

Totalling 30 instance for each activity.


real world coordinates (x, y, z) for .*_realworld.txt

screen coordinates and depth value (u, v, depth) for .*_screen.txt.


##### Files contain 15 skeleton joints:

- line 1 Head
- line 2 Neck
- line 3 Right Shoulder
- line 4 Right Elbow
- line 5 Right Hand
- line 6 Left Shoulder
- line 7 Left Elbow
- line 8 Left Hand
- line 9 Torso
- line 10 Right Hip
- line 11 Right Knee
- line 12 Right Foot
- line 13 Left Hip
- line 14 Left Knee
- line 15 Left Foot

Visit this page for the full description [KARD - Kinect Activity Recognition Dataset](https://data.mendeley.com/datasets/k28dtm7tr6/1)

### Contributor(s):  [Marco Morana](https://www.mendeley.com/profiles/marco-morana/), [Giuseppe Lo Re](https://data.mendeley.com/datasets/k28dtm7tr6/1), [Salvatore Gaglio](https://data.mendeley.com/datasets/k28dtm7tr6/1)


### Paper: 
Human Activity Recognition Process Using 3-D Posture Data. S. Gaglio, G. Lo Re, M. Morana. In IEEE Transactions on Human-Machine Systems. 2014 doi: 10.1109/THMS.2014.2377111
