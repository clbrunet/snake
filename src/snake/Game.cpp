#include <curses.h>
#include <unistd.h>
#include <cstdlib>
#include <ctime>


#include "snake/Game.hpp"

const int Game::height = 15;
const int Game::width = 17;

Game::Game() :
	window_(newwin(height + 2, width + 2,
				LINES / 2 - (height + 2) / 2, COLS / 2 - (width + 2) / 2)),
	snake_(Snake()),
	fruit_position_(Vector2Int(10, 7))
{
	srand((unsigned) time(0));
	nodelay(window_, true);
	keypad(window_, true);

	draw();
}

Game::Game(const Game& src) :
	window_(dupwin(src.window_)),
	snake_(src.snake_),
	fruit_position_(src.fruit_position_)
{
	wrefresh(window_);
}

Game& Game::operator=(const Game& rhs)
{
	window_ = dupwin(rhs.window_);
	snake_ = rhs.snake_;
	fruit_position_ = rhs.fruit_position_;
	return *this;
}

Game::~Game()
{
	delwin(window_);
}

const WINDOW* Game::getWindow() const
{
	return window_;
}

void Game::play()
{
	while (snake_.getIsDead() == false) {
		draw();
		usleep(300000);
		int ch = wgetch(window_);
		flushinp();
		snake_.move(ch, fruit_position_);
		if (snake_.getParts().front().position == fruit_position_) {
			newFruit();
		}
	}
}

void Game::newFruit()
{
	Vector2Int pos(rand() % 17 + 1, rand() % 15 + 1);
	for (const SnakePart& part : snake_.getParts()) {
		if (pos == part.position) {
			return newFruit();
		}
	}
	fruit_position_ = pos;
}

void Game::draw() const
{
	werase(window_);

	box(window_, 0, 0);

	std::deque<SnakePart>::const_iterator cit = snake_.getParts().cbegin();
	switch (snake_.getDirection()) {
		case Direction::Up:
			mvwaddch(window_, cit->position.y, cit->position.x, ACS_UARROW);
			break;
		case Direction::Down:
			mvwaddch(window_, cit->position.y, cit->position.x, ACS_DARROW);
			break;
		case Direction::Right:
			mvwaddch(window_, cit->position.y, cit->position.x, ACS_RARROW);
			break;
		case Direction::Left:
			mvwaddch(window_, cit->position.y, cit->position.x, ACS_LARROW);
			break;
	}
	cit++;
	while (cit != snake_.getParts().cend()) {
		mvwaddch(window_, cit->position.y, cit->position.x, cit->ch);
		cit++;
	}
	mvwaddch(window_, fruit_position_.y, fruit_position_.x, 'f');
	wrefresh(window_);
}
