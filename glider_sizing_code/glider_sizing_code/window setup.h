#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <time.h>

using namespace std;

const int x_size = 2400;
const int y_size = 1200;
const int margin = 70;
const int spacing_x = 100;
const int spacing_y = 24;

sf::RenderWindow window(sf::VideoMode(x_size, y_size), "matlab");
sf::VertexArray line(sf::LinesStrip, 2);
sf::RectangleShape pr(sf::Vector2f(4, 4));

sf::Vector2i pixelPos;
sf::Vector2f truePos;
sf::Event event;
bool lock_click_left;
bool lock_click_right;

int counter = 0;
int scale = 1000;

double glide_angle = 0.209439510239;
double drop_height = 60.96;
double drop_speed = 21.336;

double electronics_mass = 0.0907185;
double max_mass = 0.2494758;
double wingspan_limit = 0.3048;
double aspect_ratio_lower_limit = 3;

double cd0 = 0.03;
double epsilon = 0.6;
double pi = 3.1415926535897932;
double g = 9.81;
double rho = 1.225;

const int fineness = 23;
const int rat = 2;

class glider {
public:
	double span, chord;

	void set(double a, double b) {
		span = a;
		chord = b;
	}

	double a() {
		return span / chord;
	}

	double s() {
		return span * chord;
	}

	double cl() {
		//return pow(tan(glide_angle), 2) - (4 * cd0) / (a() * pi * epsilon);
		return (tan(glide_angle) - sqrt(pow(tan(glide_angle), 2) - (4 * cd0) / (a() * pi * epsilon))) * (2 * pi * a() * epsilon);
	}

	double cd() {
		return cl() * tan(glide_angle);
	}

	double weight() {
		return rho * s() * cl() * pow(drop_speed, 2) * cos(glide_angle) / 2;

	}

	double pred_wing_mass() {// predicted wing weight with 1 ply carbon fiber layup on pink foam
		return chord * span * 2.02713 * 0.196653 * 2 + pow(chord, 2) * span * 0.0681797 * 32.4373329902;
	}

	double pred_tail_mass() {// predicted wing weight with 1 ply carbon fiber layup on pink foam
		return chord * span * 2.02713 * 0.196653 * 2 * 0.4 + chord * span * 0.4 * 0.0681797 * 32.4373329902 * sqrt(chord * span * 0.4) / 1.5;
	}

	double pred_mass() {
		return pred_tail_mass() * 1.5 + pred_wing_mass();
	}

	double mass() {
		return weight() / g;
	}

	bool constraint(int case_num) {
		switch (case_num)
		{
		case 1:
			if (a() >= aspect_ratio_lower_limit) {
				return 1;
			}
			return 0;
			break;
		case 2:
			if (span <= wingspan_limit) {
				return 1;
			}
			return 0;
			break;
		case 3:
			if (mass() < max_mass) {
				return 1;
			}
			return 0;
			break;
		case 4:
			if (electronics_mass + pred_mass() < mass()) {
				return 1;
			}
			return 0;
		default:
			if (drop_height / sin(glide_angle) / drop_speed < 30) {
				return 1;
			}
			return 0;
			break;
		}
	}

	bool check_all() {
		for (int i = 0; i <= 5; i++) {
			if (!constraint(i)) {
				//cout << i << endl;
				return 0;
			}
		}
		return 1;
	}

	void paste() {
		for (int i = 1; i < 5; i++) {
			cout << constraint(i) << ", ";
		}
		cout << constraint(5) << endl;
		cout << "Dimensions: " << span << " x " << chord << " (m x m), Aspect ratio: " << a() << ", Surface area: " << s() << " (m\^2)" << endl;
		cout << "Cl: " << cl() << ", Cd: " << cd() << endl;
		cout << "Weight: " << weight() << " (N), Mass: " << mass() << " (kg)" << endl;
		cout << "Electronics fraction: " << electronics_mass / mass() << endl;
		cout << "Predicted (unloaded) min weight: " << pred_mass() * 9.81 << " (N), predicted (unloaded) min mass: " << pred_mass() * 1000 << " (g)" << endl << endl;
		cout << "Predicted (loaded) min weight: " << (pred_mass() + electronics_mass) * 9.81 << " (N), predicted (loaded) min mass: " << (pred_mass() + electronics_mass) * 1000 << " (g)" << endl << endl;
	}
};

glider g_array[fineness][fineness * rat];

void check_input() {
	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left && lock_click_left != true)
		{
			cout << endl << max(0, min(fineness - 1, ((pixelPos.x - margin) / spacing_x))) << ", " << max(0, min(rat * fineness - 1, ((pixelPos.y - margin) / spacing_y))) << ": " << endl;
			lock_click_left = true;
			g_array[max(0, min(fineness - 1, ((pixelPos.x - margin) / spacing_x)))][max(0, min(rat * fineness - 1, ((pixelPos.y - margin) / spacing_y)))].paste();
		}
		if (event.mouseButton.button == sf::Mouse::Right && lock_click_right != true)
		{
			lock_click_right = true;
		}
	}
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			lock_click_left = false;
		}
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			lock_click_right = false;
		}
	}
	if (event.type == sf::Event::Closed) {
		window.close();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		counter++;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (counter > 0) {
			counter--;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
	}
	if (lock_click_left) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		}
		else {
		}
	}
	if (lock_click_right) {
	}
}
