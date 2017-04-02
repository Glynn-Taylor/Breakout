LIBDIRS= -L/usr/X11R6/lib
LDLIBS = -lglut -lGL -lGLU -lX11 -lm -lpng

CPPFLAGS= -O3 -g
LDFLAGS= $(CPPFLAGS) $(LIBDIRS)

TARGET = breakout

SRCS = 324-breakout.cpp BoxCollider.cpp TextRenderer.cpp png_load.cpp UIRenderer.cpp Chunk.cpp Scene.cpp MenuState.cpp Atari2DState.cpp Ball.cpp Starfield.cpp Wall.cpp Sprite2D.cpp Paddle.cpp BrickWall.cpp Brick.cpp RigidBody.cpp GameOverState.cpp VictoryState.cpp Atari3DState.cpp SpriteRenderer.cpp GeometryCreator.cpp CuboidRenderer.cpp ControlsState.cpp
OBJS =  $(SRCS:.cpp=.o)
CXX = g++

%.0: %.cpp
	$(CXX) -c $(CPPFLAGS) -o $@ $<
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDLIBS) -o $(TARGET)

324-breakout.o: 324-breakout.cpp
MenuState.o: MenuState.hpp TickableObject.hpp UIRenderer.hpp
Atari2DState.o: Atari2DState.hpp TickableObject.hpp UIRenderer.hpp
Atari3DState.o: Atari3DState.hpp TickableObject.hpp UIRenderer.hpp
UIRenderer.o: TextRenderer.hpp png_load.hpp
TextRenderer.o: TextRenderer.hpp
png_load.o: png_load.hpp
Chunk.o: Chunk.hpp
Scene.o: Scene.hpp
Ball.o: Ball.hpp
BoxCollider.o: BoxCollider.hpp
Wall.o: Wall.hpp
Starfield.o: Starfield.hpp
Sprite2D.o: Sprite2D.hpp
Paddle.o: Paddle.hpp
BrickWall.o: BrickWall.hpp
Brick.o: Brick.hpp
RigidBody.o: RigidBody.hpp
GameOverState.o: GameOverState.hpp
VictoryState.o: VictoryState.hpp
SpriteRenderer.o: SpriteRenderer.hpp
CuboidRenderer.o: CuboidRenderer.hpp
GeometryCreator.o: GeometryCreator.hpp
ControlsState.o: ControlsState.hpp TickableObject.hpp UIRenderer.hpp
