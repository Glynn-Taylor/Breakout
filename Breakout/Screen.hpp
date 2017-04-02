#define STATE_MENU 0
#define STATE_ATARI2D 1
#define STATE_ATARI3D 2
#define STATE_GAMEOVER 3
#define STATE_VICTORY 4
#define STATE_CONTROLS 5

//Current screen width
extern int ScreenWidth;
//Current screen height
extern int ScreenHeight;
//Mouse coords
extern float MouseX;
extern float MouseY;
//Whether or not mouse buttons are pressed
extern bool LMB;
extern bool RMB;
//Which keys are currently pressed (special keys are offset by 256)
extern bool Keys[360];
//Id of the window
extern int WINID;
//Which state the game is currently running
extern int ScreenState;

