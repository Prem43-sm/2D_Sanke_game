#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    const int GRID_SIZE = 20;
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const int CELL_SIZE = 20;
    const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
    const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fast 2D Snake - BLACKBOXAI");
    window.setFramerateLimit(60);

    // Snake: fixed array for speed, max length 400 (20x20 grid)
    struct SnakeSegment {
        int x, y;
    };
    SnakeSegment snake[400];
    int snakeLength = 1;
    int dx = 1, dy = 0; // Initial direction: right

    // Food position
    int foodX, foodY;

    // Score
    int score = 0;

    // Game state
    bool gameOver = false;
    bool spacePressed = false;

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Spawn initial snake and food
    snake[0].x = GRID_WIDTH / 2;
    snake[0].y = GRID_HEIGHT / 2;
    foodX = rand() % GRID_WIDTH;
    foodY = rand() % GRID_HEIGHT;

    sf::Font font;
    const bool fontLoaded = font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    if (!fontLoaded) {
        std::cerr << "Font not found" << std::endl;
    }

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (!gameOver) {
                    // Direction change (prevent reverse)
                    if (event.key.code == sf::Keyboard::Left && dx != 1) { dx = -1; dy = 0; }
                    if (event.key.code == sf::Keyboard::Right && dx != -1) { dx = 1; dy = 0; }
                    if (event.key.code == sf::Keyboard::Up && dy != 1) { dx = 0; dy = -1; }
                    if (event.key.code == sf::Keyboard::Down && dy != -1) { dx = 0; dy = 1; }
                } else if (event.key.code == sf::Keyboard::Space && !spacePressed) {
                    // Restart
                    snakeLength = 1;
                    snake[0].x = GRID_WIDTH / 2;
                    snake[0].y = GRID_HEIGHT / 2;
                    dx = 1; dy = 0;
                    score = 0;
                    foodX = rand() % GRID_WIDTH;
                    foodY = rand() % GRID_HEIGHT;
                    gameOver = false;
                    spacePressed = true;
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) spacePressed = false;
            }
        }

        if (!gameOver && clock.getElapsedTime().asMilliseconds() > 100) { // Update every 100ms for speed
            // Move snake
            for (int i = snakeLength - 1; i > 0; --i) {
                snake[i] = snake[i-1];
            }
            snake[0].x += dx;
            snake[0].y += dy;

            // Wall collision
            if (snake[0].x < 0 || snake[0].x >= GRID_WIDTH || snake[0].y < 0 || snake[0].y >= GRID_HEIGHT) {
                gameOver = true;
            }

            // Self collision
            for (int i = 1; i < snakeLength; ++i) {
                if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                    gameOver = true;
                    break;
                }
            }

            // Food collision
            if (snake[0].x == foodX && snake[0].y == foodY) {
                ++snakeLength;
                ++score;
                foodX = rand() % GRID_WIDTH;
                foodY = rand() % GRID_HEIGHT;
                // Ensure food not on snake
                bool onSnake;
                do {
                    onSnake = false;
                    foodX = rand() % GRID_WIDTH;
                    foodY = rand() % GRID_HEIGHT;
                    for (int i = 0; i < snakeLength; ++i) {
                        if (foodX == snake[i].x && foodY == snake[i].y) {
                            onSnake = true;
                            break;
                        }
                    }
                } while (onSnake);
            }

            clock.restart();
        }

        window.clear(sf::Color::Black);

        // Draw snake (green)
        for (int i = 0; i < snakeLength; ++i) {
            sf::RectangleShape segment(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            segment.setPosition(snake[i].x * CELL_SIZE, snake[i].y * CELL_SIZE);
            segment.setFillColor(sf::Color::Green);
            window.draw(segment);
        }

        // Draw food (red)
        sf::RectangleShape food(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
        food.setPosition(foodX * CELL_SIZE, foodY * CELL_SIZE);
        food.setFillColor(sf::Color::Red);
        window.draw(food);

        // Draw grid (optional, light)
        sf::Vertex lines[] = {
            sf::Vertex(sf::Vector2f(0, 0), sf::Color::White), sf::Vertex(sf::Vector2f(WINDOW_WIDTH, 0), sf::Color::White),
            sf::Vertex(sf::Vector2f(0, 0), sf::Color::White), sf::Vertex(sf::Vector2f(0, WINDOW_HEIGHT), sf::Color::White),
            sf::Vertex(sf::Vector2f(WINDOW_WIDTH, 0), sf::Color::White), sf::Vertex(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT), sf::Color::White),
            sf::Vertex(sf::Vector2f(0, WINDOW_HEIGHT), sf::Color::White), sf::Vertex(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT), sf::Color::White)
        };
        window.draw(lines, 8, sf::Lines);

        // Draw score
        if (fontLoaded) {
            sf::Text scoreText("Score: " + std::to_string(score), font, 24);
            scoreText.setPosition(10, 10);
            scoreText.setFillColor(sf::Color::White);
            window.draw(scoreText);
        }

        // Game over text
        if (gameOver && fontLoaded) {
            sf::Text gameOverText("Game Over! Score: " + std::to_string(score) + "\\nPress SPACE to restart", font, 30);
            gameOverText.setPosition(WINDOW_WIDTH/2 - 200, WINDOW_HEIGHT/2);
            gameOverText.setFillColor(sf::Color::Yellow);
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}

