
#include "Sprite2D.hpp"
#include "UIRenderer.hpp"
#include <cmath>

//Animateable texture class

//Constructor with tilesheet arguments
Sprite2D::Sprite2D(const char* path, const float tileWidth, const float tileHeight, const int frames, const int animations){
	//Set sprite animation variables
	m_textureHandle = loadTexture(path);	
	m_currentTile=0.0f;
	m_currentAnimation=0;
	m_isPlaying=true;
	m_tileWidth =tileWidth;
	m_tileHeight = tileHeight;
	m_frames=frames;
	m_animations=animations;
}
Sprite2D::~Sprite2D(){

}
//Advance the current frame based on time
void Sprite2D::Tick(float time){
	m_currentTile += time;
	if(m_currentTile>m_frames){
		m_currentTile-=m_frames;
	}
}
//Set the animation frame
void Sprite2D::SetAnimation(const int index){
	m_currentAnimation=index;
	//Check animation out of bounds
	if(m_currentAnimation >= m_animations || m_currentAnimation < 0){
		m_currentAnimation = 0;
	}	
}

//Render the current frame at a position
void Sprite2D::Render(const int x, const int y, const int w, const int h){
	// enable texturing
  	glEnable(GL_TEXTURE_2D); 
	// select which texure to render
 	glBindTexture(GL_TEXTURE_2D, m_textureHandle); 
	// specify texture coordinates
	/*(floor(m_currentTile/m_frames),m_animations/(1.0f*m_frames) )
		 ______
		|      |
		|      |
		|      |
		|______|

	*/
	float texX = floor(m_currentTile)/m_frames;
	float texY = (1.0f*m_animations)/m_animations;
	//Render sprite in immediate mode
  	glBegin (GL_QUADS);
  		glTexCoord2f (texX,1.0f-texY); // lower left corner
  		glVertex2i(x, y);
  		glTexCoord2f (texX+m_tileWidth, 1.0f-texY); // lower right corner
  		glVertex2i(x+w, y);
  		glTexCoord2f (texX+m_tileWidth, 1.0f-(texY+m_tileHeight)); // upper right corner
 		glVertex2i(x+w, y+h);
  		glTexCoord2f (texX, 1.0f-(texY+m_tileHeight)); // upper left corner
  		glVertex2i(x, y+h);
  	glEnd ();

  	glDisable(GL_TEXTURE_2D);			
}
//Start the animation from frame 1
void Sprite2D::Play(){
	m_isPlaying=true;
	m_currentTile = 0.0f;
}
//Stop the animation on frame 1
void Sprite2D::Stop(){
	m_isPlaying=false;
	m_currentTile=0.0f;
}
//Stop the animation at current frame
void Sprite2D::Pause(){
	m_isPlaying=false;
}
//Resume the animation at current frame
void Sprite2D::Resume(){
	m_isPlaying=true;
}

