#include <SFML/Graphics.hpp> // PONG PORT FROM RAYLIB. Copyright 2021 George Lynntone.
#include <time.h> // Uses time to seed RNG.
int main() {
	srand(time(0)); 
	// Window init stuff.
	sf::RenderWindow window(sf::VideoMode(1280, 720), "PONG"); // Init window.
	window.setVerticalSyncEnabled(true); // Enable V-SYNC.
	sf::Clock deltaClock; // Delta time stuff.
	// Player Paddle.
	sf::RectangleShape pl_pad(sf::Vector2f(10, 150));
	pl_pad.setPosition(10.f, 285.f);
	// Enemy paddle.
	sf::RectangleShape en_pad(sf::Vector2f(10, 150));
	en_pad.setPosition(1260.f, 285.f);
	// Ball.
	sf::RectangleShape ball(sf::Vector2f(8, 8));
	ball.setPosition(22.f, 356.f);
	short ballSpeed = 800;
	short ballEleva = 0.f;
	// >MAIN GAME LOOP<
	while (window.isOpen()) {
	    // -RENDER-
        window.clear(sf::Color::Black); // Draw black background.
        window.draw(pl_pad); // Draw Paddles.
        window.draw(en_pad);
        window.draw(ball); // Draw the ball.
        window.display(); // Display to Window.
		// -EVENTS-
		sf::Event event;
		while (window.pollEvent(event)) { // Poll events.
			switch (event.type) {
				case sf::Event::Closed: window.close(); break; // If Window should close (X button -top right- presed, etc) then call function window.close().
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) window.close(); break; // If esc button pressed, call function window.close()
					break;
				default: break;
			}
		}
		// -GAME LOGIC-
		sf::Time dt = deltaClock.restart(); // Get DeltaTime.
		// Player Paddle Movement.
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { 
			 pl_pad.move(0.f, -500.f*dt.asSeconds()); }
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			pl_pad.move(0.f, +500.f*dt.asSeconds()); }
		if (pl_pad.getPosition().y < 10.f) pl_pad.setPosition(10.f, 10.f);
		else if (pl_pad.getPosition().y + 150 > 710.f) pl_pad.setPosition(10.f, 710.f - 150);

		// Enemy paddle movement.
		en_pad.setPosition(1260.f, ball.getPosition().y - 75.f);
		if (en_pad.getPosition().y < 10.f) en_pad.setPosition(1260.f, 10.f);
		else if (en_pad.getPosition().y + 150 > 710.f) en_pad.setPosition(1260.f, 710.f - 150);
		// Paddle - Ball collision.
		if (ball.getPosition().x < 50) {
			if ((ball.getPosition().x <= pl_pad.getPosition().x + 10) && (ball.getPosition().y >= pl_pad.getPosition().y) && (ball.getPosition().y <= pl_pad.getPosition().y + 150)) {
				ballSpeed = -ballSpeed; }
		}
		// Enemy - Ball collision.
		else if (ball.getPosition().x > 123) {
			if ((ball.getPosition().x >= en_pad.getPosition().x - 10) && (ball.getPosition().y >= en_pad.getPosition().y) && (ball.getPosition().y <= en_pad.getPosition().y + 150)) {
				ballSpeed = -ballSpeed;
				ballEleva = rand() % -300 + 300; }
		}
		// Edge - Ball collision.
		if (ball.getPosition().y < 5) ballEleva = -ballEleva;
		else if (ball.getPosition().y + 8 > 715) ballEleva = -ballEleva;
		// Ball movement and Game Over logic.
		if ((ball.getPosition().x > 10.f) && (ball.getPosition().x < 1270.f)) {
			ball.move(ballSpeed * dt.asSeconds(), ballEleva * dt.asSeconds());
		} else { break; } ;
	}
}
