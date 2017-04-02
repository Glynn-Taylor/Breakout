#ifndef SPRITE_2D
#define SPRITE_2D

//Animateable texture class
class Sprite2D{

	public:
		//Constructor with tilesheet arguments
		Sprite2D(const char* path, const float tileWidth, const float tileHeight, const int frames, const int animations);
		~Sprite2D();
		//Advance the current frame based on time
		void Tick(float time);
		//Set the animation frame
		void SetAnimation(const int index);
		//Render the current frame at a position
		void Render(const int x, const int y, const int w, const int h);
		//Start the animation from frame 1
		void Play();
		//Stop the animation on frame 1
		void Stop();
		//Stop the animation at current frame
		void Pause();
		//Resume the animation at current frame
		void Resume();

	private:
		//Tilesheet
		unsigned int m_textureHandle;
		//Width of each frame
		float m_tileWidth;
		//Height of each frame
		float m_tileHeight;
		//Current frame
		float m_currentTile;
		//Current row
		int m_currentAnimation;
		//Whether or not the animation is playing
		bool m_isPlaying;
		//Animation columns
		int m_frames;
		//Animation rows
		int m_animations;
};
#endif
