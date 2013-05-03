/*
 * Program that demonstrates use and understanding of semaphores
 * by Ryan Morris
 * Created on 05/01/13 
 */

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <unistd.h>

#define BLOCK_SIZE 30
#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 50
#define SCREEN_BPP 32
#define THREADS 2

using namespace std;

struct workblock
{
	string text;
	sem_t* sem;
	SDL_Surface* screen;
	SDL_Rect rect;
	TTF_Font* font;
};

using namespace std;

void* thread1(void* arg)
{
	workblock* wb = (workblock*)arg;
	unsigned int index = 0;
	
	char ch = wb->text[index];
	SDL_Color c = {255, 0, 0};
	SDL_Surface* s;
	
	cout << "Text: " << wb->text << endl;
	
	while(index < wb->text.length())
	{
		sem_wait(wb->sem); //wait until other process is done w/ screen buffer
		//cout << "Rendering " << ch << endl;
		s = TTF_RenderText_Blended(wb->font, &ch, c);
		
		wb->rect.x = BLOCK_SIZE * index;
		wb->rect.y = 0;
		wb->rect.w = s->w;
		wb->rect.h = s->h;

		SDL_BlitSurface(s, NULL, wb->screen, &wb->rect);

		SDL_Flip(wb->screen);
		
		sem_post(wb->sem);
		
		index += 2;
		if(index < wb->text.length()) ch = wb->text[index]; //Prevent array access violation
		SDL_Delay(100);
	}
	return 0;
}

void* thread2(void* arg)
{
	workblock* wb = (workblock*)arg;
	int index = 1;
	
	char ch = wb->text[index];
	SDL_Color c = {0, 0, 0};
	SDL_Surface* s;
	
	while(index < wb -> text.length())
	{
		sem_wait(wb->sem); //wait until other process is done w/ screen buffer
		
		s = TTF_RenderText_Blended(wb->font, &ch, c);
		
		wb->rect.x = BLOCK_SIZE * index;
		wb->rect.y = 0;
		wb->rect.w = s->w;
		wb->rect.h = s->h;

		SDL_BlitSurface(s, NULL, wb->screen, &wb->rect);

		SDL_Flip(wb->screen);
		
		sem_post(wb->sem);
		
		index += 2;
		if(index < wb->text.length()) ch = wb->text[index]; //Prevent array access violation
		SDL_Delay(100);
	}
	return 0;
}
 
void populate_workblock(workblock &wb, SDL_Surface* screen,  sem_t* sem, string message)
{
	wb.screen = screen;
	wb.sem = sem;
	wb.font = TTF_OpenFont("fonts/diager.ttf", BLOCK_SIZE); 
	wb.text = message;
}

int main(int argc, char*argv[])
{
	SDL_Surface* screen;
	sem_t mutex;
	sem_init(&mutex, 0/*shared across multiple*/, 1);
	//cout << &mutex << endl;
	pthread_attr_t t1_attr;
	pthread_t t1_id;
	pthread_attr_t t2_attr;
	pthread_t t2_id;
	
	workblock w;
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != -1)	//init SDL
	{
		TTF_Init();
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE ); //Init screen
		SDL_FillRect(screen, &screen->clip_rect, 0xFFFFFF);
		SDL_Flip(screen); //draw the screen
		
		populate_workblock(w, screen, &mutex, "Hi Dr. MacEvoy");
		//create threads
		pthread_attr_init(&t1_attr);
		pthread_attr_init(&t2_attr);
		pthread_create(&t1_id,&t1_attr,thread1,&w);
		pthread_create(&t2_id,&t2_attr,thread2,&w);
		//join threads
		pthread_join(t1_id,NULL);
		pthread_join(t2_id,NULL);
		sleep(5);
		TTF_Quit();
		SDL_Quit();
	}
	else
	{
		cerr << "Error initializing SDL\n";
	}
	sem_destroy(&mutex);
	
	return 0;
}