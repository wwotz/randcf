#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#define LINEARLIB_IMPLEMENTATION
#define FTGL_IMPLEMENTATION
#include "font.h"

#define WINDOW_NAME "RAND CodeForces"
#define WINDOW_W 800
#define WINDOW_H 600

static SDL_Window *window;
static SDL_GLContext *context;
static SDL_Event event;
static int running;

enum gl_buffers {
	BUFFER_VBO,
	BUFFER_EBO,
	BUFFER_VAO,
	BUFFER_COUNT,
};
static GLuint buffers[BUFFER_COUNT];

static GLuint texture_shader;
static GLuint lever_texture;

int
main(int argc, char **argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow(WINDOW_NAME,
				  SDL_WINDOWPOS_UNDEFINED,
				  SDL_WINDOWPOS_UNDEFINED,
				  WINDOW_W, WINDOW_H,
				  SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);
	glewInit();

	ll_matrix_mode(LL_MATRIX_MODEL);
	ll_matrix_identity();
	ll_matrix_mode(LL_MATRIX_PROJECTION);
	ll_matrix_orthographic(0.0, WINDOW_W, WINDOW_H, 0.0,
			       10.0, -10.0);

	glViewport(0.0, 0.0, WINDOW_W, WINDOW_H);

	glGenTextures(1, &lever_texture);
	glBindTexture(GL_TEXTURE_2D, lever_texture);
	
	SDL_Surface *surface = IMG_Load("lever.png");
	if (!surface) {
		fprintf(stderr, "IMG: %s\n", IMG_GetError());
		exit(EXIT_FAILURE);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h,
		     0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	SDL_FreeSurface(surface);
	
	

	running = 1;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = 0;
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window);
	}

	SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	IMG_Quit();
	return 0;
}




