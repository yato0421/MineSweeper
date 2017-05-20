#include "Game.h"
#include <Siv3D.hpp>

Game::Game() {
	start();
}
void Game::start() {
	Window::Resize(408, 480);
	state = State::START;
	deploy_bomb();
}
void Game::update() {
	switch (state) {
	case State::START:
		if (Input::KeySpace.clicked) {
			state = State::GAME;
		}
		break;
	case State::GAME:
		if (Input::KeySpace.clicked) {
			state = State::CLEAR;
		}
		break;
	case State::CLEAR:
		if (Input::KeySpace.clicked) {
			state = State::START;
		}
		break;
	}
}
void Game::draw() {
	static Font fontS(30);

	switch (state) {
	case State::START:
		fontS(L"マインスイーパー").drawCenter(100 - fontS.ascent);
		fontS(L"すたーと").drawCenter(300,Palette::Yellow);
		break;
	case State::GAME:
		map_draw();
		break;
	case State::CLEAR:
		fontS(L"げーむくりあー").drawCenter(200,Palette::Yellow);
		break;
	}
}
void Game::game_clear() {

}
void Game::game_over(){

}
void Game::input() {

}
void Game::check(int n, int j){
	//ループで表示した正方形のあたり判定
	const Rect rect(8 + rect_x, 80 + rect_y, 42, 42);
	const bool r = rect.leftPressed;
	if (r == 1){
		switch (col[n][j]) {
		case 0:
			col[n][j] = 1;
			break;
		case 3:
			col[n][j] = 2;
			break;
		}
	}
}
void Game::map_draw() {
	static Font fontS(30);
	static Image image(L"Example/Bomb.jpeg");
	static Texture texture(image);
	int Line_x = 4;
	int Line_y = 76;
	rect_x = 0;
	rect_y = 0;
	//ゲーム画面上部
	Rect(0, 0, 408, 72).draw(Palette::Black);
	fontS(L"Reset").draw(250, 0, Palette::Skyblue);
	//ゲーム画面
	for (int n = 0; n < 8;n++) {
		for (int j = 0; j < 8; j++) {
			//Rect(8 + rect_x, 80 + rect_y, 42, 42).draw(Palette::Blue);
			check(n,j);
			switch (col[n][j]) {
			case 0:
				Rect(8 + rect_x, 80 + rect_y, 42, 42).draw(Palette::Blue);
				break;
			case 1:
				Rect(8 + rect_x, 80 + rect_y, 42, 42).draw(Palette::White);
				break;
			case 2:
				texture.draw(8 + rect_x, 80 + rect_y);
				break;
			case 3:
				Rect(8 + rect_x, 80 + rect_y, 42, 42).draw(Palette::Blue);
				break;
			}
			rect_x += 50;
		}
		rect_x = 0;
		rect_y += 50;
	}
	for (int i = 1; i <= 9; i++) {
		Line(0, Line_y, 520, Line_y).draw(8, Palette::Skyblue);
		Line_y += 50;
		Line(Line_x, 80, Line_x, 480).draw(8, Palette::Skyblue);
		Line_x += 50;
	}

}
void Game::deploy_bomb() {
	int before, after;
		for (int j = 0; j < 8;j++) {
			before = (Random(0, 7));
			after = (Random(0, 7));
			col[before][after] = 3;
		}
}