//Helper methods for rendering text
extern void renderText(const int x, const int y, const char* text, bool centered = false);
extern void renderText(const int x, const int y, const int w, const int h, const char* text, bool centered = false);
//Render a number with preceding 0's
void renderScore(const int x, const int y, const int w, const int h, const int score, const int length);
//Render a number
void renderNumber(const int x, const int y, const int w, const int h, const int num);
//Render a number with some preceding text
void renderScoreNumber(const int x, const int y, const int w, const int h, const int num);
