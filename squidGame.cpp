#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include <time.h> 
#include <string>

using namespace sf;
using namespace std;

struct point
{ int x, y;};

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(600, 600), "Squid Game!");
    app.setFramerateLimit(60);

    Texture bg, platformImg, doodle;
    bg.loadFromFile("images/background.png");
    platformImg.loadFromFile("images/platform.png");
    doodle.loadFromFile("images/doodle.png");

    Sprite sBg(bg), sPlatform(platformImg), sDoodle(doodle);

    point plat[20];
 
 	// Backgroung for the gameover screen
	RectangleShape goBg(Vector2f(600, 600));
	goBg.setFillColor(Color::Black);

	// Font for the game
	Font font;
	font.loadFromFile("font/arial.ttf");
	
	// Score Text
	Text scoreTxt;
	scoreTxt.setFont(font);
	scoreTxt.setCharacterSize(30);
	scoreTxt.setFillColor(Color::Green);
	
	// Gameover Text
	Text goTxt;
	goTxt.setFont(font);
	goTxt.setString("GAME OVER!");
	goTxt.setCharacterSize(60);
	goTxt.setFillColor(Color::Red);

	// Jump sound
	SoundBuffer buffer;
	buffer.loadFromFile("sound/jump.wav");
	Sound sound;
	sound.setBuffer(buffer);

	// Game over sound
	SoundBuffer buffery;
	buffery.loadFromFile("sound/gameover.wav");
	Sound gameko;
	gameko.setBuffer(buffery);
	
    for (int i=0; i < 10; i++)
    {
       	plat[i].x = rand() % 600;
       	plat[i].y = rand() % 600;
    }

    int x = 300, y = 200, h = 200, score = 0;
    float dx = 0, dy = 0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed) app.close();
        }

    	if (Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
    	if (Keyboard::isKeyPressed(Keyboard::Left)) x-=3;

		if (x > 600) x = 0;
		if (x < -40) x = app.getSize().x - doodle.getSize().x;


		if (y == h && dy < (-1.62))
		{
			score += 1;
			scoreTxt.setString("Score: " + to_string(score));
		}
	
		// player's jump mechanism
    	dy += 0.2;
    	y += dy; 
 
    	if (y < h)
		{
    		for (int i = 0; i < 10; ++i)
			{
				y = h;
      			plat[i].y -= dy * 2; // vertical translation
      			if (plat[i].y > 600)  // set new platform on the top
		  		{
		  			plat[i].y = 0; 
		 	 		plat[i].x = rand() % 600;
		  		}
    		}
		}
    
	
		// detect jump on the platform
    	for (int i = 0; i < 10; i++)
		{
    	 	if ((x + 30 > plat[i].x) && (x + 10 < plat[i].x + platformImg.getSize().x)
      			&& (y + 70 > plat[i].y) && (y + 70 < plat[i].y + platformImg.getSize().y) && (dy > 0))  
	  		{
	  			sound.play();
	  			dy = -10;
	  		}

		}
    
    	sDoodle.setPosition(x, y);

    	app.draw(sBg);
    	app.draw(sDoodle);
    
    	// set and draw platforms
    	for (int i = 0; i < 10; i++)
    	{
    		sPlatform.setPosition(plat[i].x, plat[i].y);
    		app.draw(sPlatform);
    	}
	
		// game over
		if (y > 600)
		{
			goTxt.setPosition(120,200);
			scoreTxt.setPosition(220, 300);
			gameko.play();
			goto gameover;
		}
	
		app.draw(scoreTxt);
    	app.display();
	}

	// Game Over
	gameover:
		while (app.isOpen())
		{
			Event e;
			while (app.pollEvent(e))
			{
				if (e.type == Event::Closed)
				app.close();
			}
			app.draw(goBg);
			app.draw(goTxt); 
			app.draw(scoreTxt);
			app.display();
		}

    return 0;
}

