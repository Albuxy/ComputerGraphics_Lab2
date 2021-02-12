#include "application.h"
#include "utils.h"
#include "image.h"

Color c;
int estado = 2; //Variable que servira para volver al menu

int E = 0;
int distancia_radio = 0;

Vector2 punto_1;
Vector2 punto_2;

int contador = 0;//Para controlar los click del mouse



Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);

	framebuffer.resize(w, h);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;
	framebuffer.loadTGA("Menu Interfaz.tga");
	//MenuAuxiliar.loadTGA("Menu Interfaz.tga");


	//here add your init stuff
}

//render one frame
void Application::render( Image& framebuffer )
{
	//clear framebuffer if we want to start from scratch
	//framebuffer.fill(Color::BLACK);
	//here you can add your code to fill the framebuffer

	//fill every pixel of the image with some random data
	/*for (unsigned int x = 0; x < framebuffer.width; x++)
	{
		for (unsigned int y = 0; y < framebuffer.height; y++)
		{
			framebuffer.setPixel(x, y, Color(randomValue() * 255, randomValue() * 255, randomValue() * 255)); //random color
		}
	}*/

}

//called after render
void Application::update(double seconds_elapsed)
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode

	//Volver al menu presionando M
	if (keystate[SDL_SCANCODE_M]) {
		estado = 0;
	}
	if (estado == 0){
		framebuffer.loadTGA("Menu Interfaz.tga");
		estado = 2;
	}

	//Linea DDA
	if (keystate[SDL_SCANCODE_A]){
		framebuffer.fill(Color::GRAY);
		E = 1;
	}
	//Linea Bresenham
	if (keystate[SDL_SCANCODE_B]){
		framebuffer.fill(Color::BLACK);
		E = 1;
	}
	//Circulo Vacio
	if (keystate[SDL_SCANCODE_C]){
		framebuffer.fill(Color::WHITE);
		E = 3;
	}
	//Circulo relleno
	if (keystate[SDL_SCANCODE_F]){
		framebuffer.fill(Color::WHITE);
		E = 4;
	}


	//to read mouse position use mouse_position
}

//keyboard press event 
void Application::onKeyDown( SDL_KeyboardEvent event )
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
	switch(event.keysym.scancode)
	{
		case SDL_SCANCODE_ESCAPE:
			exit(0); 
			break; //ESC key, kill the app
	}
}

//keyboard key up event 
void Application::onKeyUp(SDL_KeyboardEvent event)
{
	//...
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse pressed
	{
		punto_1.x = mouse_position.x;;
		punto_1.y = mouse_position.y;

	}
}

void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
	{
		//Calculamos el radio para los circulos
		int d = abs(mouse_position.x - punto_1.x);
		int b = abs(mouse_position.y - punto_1.y);
		distancia_radio = sqrt(pow(b, 2) + pow(d, 2));

		//Linea DDA
		if (E == 1) {
			framebuffer.drawLineDDA(punto_1.x, punto_1.y, mouse_position.x, mouse_position.y, c);
		}
		//Linea Bresenham
		if (E == 2) {
			framebuffer.drawLineBresenham(punto_1.x, punto_1.y, mouse_position.x, mouse_position.y, c);
		}
		//Circulo sin relleno
		if (E == 3) {
			framebuffer.drawCircle(punto_1.x, punto_1.y, distancia_radio, c , false);
		}
		//Circulo con relleno
		if (E == 4) {
			framebuffer.drawCircle(punto_1.x, punto_1.y, distancia_radio, c, true);
		}
		
	}
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
